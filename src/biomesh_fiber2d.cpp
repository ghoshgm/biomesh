
#include <biomesh_fiber2d.hpp>

namespace biomesh
{
fiber2D::fiber2D (size_t gpoint_count, double width)
    : m_gpoint_count{ gpoint_count }, m_width{ width }
{
  m_fiber_vertices.reserve (m_gpoint_count);
  m_fiber_vertices.emplace_back (m_seed);
}

fiber2D::fiber2D (const vertex2D &seed, size_t gpoint_count, double width)
    : m_seed{ seed }, m_gpoint_count{ gpoint_count }, m_width{ width }
{
  m_fiber_vertices.reserve (m_gpoint_count);
  m_fiber_vertices.emplace_back (m_seed);
}

fiber2D::fiber2D (const fiber2D &other)
{
  this->m_seed = other.m_seed;
  this->m_fiber_vertices = other.m_fiber_vertices;
}

fiber2D::fiber2D (fiber2D &&other)
{
  this->m_seed = other.m_seed;
  this->m_fiber_vertices = std::move (other.m_fiber_vertices);
}

fiber2D::~fiber2D () {}

size_t
fiber2D::size () const
{
  return m_fiber_vertices.size ();
}

vertex2D
fiber2D::operator[] (int idx) const
{
  BIOMESH_ASSERT (idx >= 0 && idx < m_fiber_vertices.size ());
  return m_fiber_vertices[idx];
}

bool
fiber2D::operator== (const fiber2D &other) const
{
  return this->m_seed == other.m_seed;
}

void
fiber2D::generate_fiber (const vector_field &vfield)
{
  /* Obtain the structured grid. */
  auto sgrid = vfield.get_grid ();
  BIOMESH_ASSERT (sgrid != nullptr);

  BIOMESH_LINFO (0, "Fiber begin.");

  stopwatch watch;
  watch.start ();
  /**
   * The 'FindCell' function in the VTK lib returns more information
   * than needed. We are only interested in the return value of the
   * function. The variables 'subid', 'pcoords' and 'weights' are
   * return variables which are not needed
   * but are essential to avoid segfaults.
   */
  int subid;
  double pcoords[3];
  double weights[VTK_CELL_SIZE];

  int arridx = 1;
  vtkDataArray *da = sgrid->GetPointData ()->GetArray ("vectors", arridx);
  BIOMESH_ASSERT (da != nullptr);

  /* The 'point' variable is only required for VTK searching. */
  double point[3] = { m_seed ('x'), m_seed ('y'), 0.0 };

  std::cout << "---- Cartesian coord ----" << std::endl;
  std::cout << point[0] << " " << point[1] << " " << point[2] << std::endl;
  std::cout << "-------------------------" << std::endl;

  vertex2D next = m_seed;
  for (int ii = 0; ii < m_gpoint_count - 1; ++ii)
    {
      /* Search for 'point' in the VTK structured grid. */
      auto cellid
          = sgrid->FindCell (point, nullptr, -1, 0, subid, pcoords, weights);

      /* Ignore 'point' if it lies outside the vector field. */
      if (cellid >= 0)
        {
          /* Grab the cell. */
          vtkCell *seed_cell = sgrid->GetCell (cellid);
          BIOMESH_ASSERT (seed_cell != nullptr);
          BIOMESH_ASSERT (seed_cell->GetCellType () == VTK_QUAD);

          /* Grab the point indices. */
          vtkIdList *pids = seed_cell->GetPointIds ();
          BIOMESH_ASSERT (pids != nullptr);

          /* Grab the vectors. */
          std::array<double, 4> vx{ (da->GetTuple3 (pids->GetId (0)))[0],
                                    (da->GetTuple3 (pids->GetId (1)))[0],
                                    (da->GetTuple3 (pids->GetId (2)))[0],
                                    (da->GetTuple3 (pids->GetId (3)))[0] };

          std::array<double, 4> vy{ (da->GetTuple3 (pids->GetId (0)))[1],
                                    (da->GetTuple3 (pids->GetId (1)))[1],
                                    (da->GetTuple3 (pids->GetId (2)))[1],
                                    (da->GetTuple3 (pids->GetId (3)))[1] };

          /* Compute next grid vertex using bilinear interpolation. */
          vertex2D pnext (pcoords[0], pcoords[1]);
          std::cout << "---- Parametric coords ----" << std::endl;
          pnext.print ();
          std::cout << "---------------------------" << std::endl;

          std::cout << "---- Bounds of the cell ----" << std::endl;
          std::cout << vx[0] << " " << vy[0] << std::endl;
          std::cout << vx[1] << " " << vy[1] << std::endl;
          std::cout << vx[2] << " " << vy[2] << std::endl;
          std::cout << vx[3] << " " << vy[3] << std::endl;
          std::cout << "----------------------------" << std::endl;

          double r = interpolation::bilinear (pnext, vx);
          double s = interpolation::bilinear (pnext, vy);

          /* Mapping parametric to cartesian.*/
          vertex2D ipnext (r, s);
          std::cout << "---- Interpolated coord ----" << std::endl;
          ipnext.print ();
          std::cout << "----------------------------" << std::endl;
          vertex2D v0 (seed_cell->GetPoints ()->GetPoint (0)[0],
                       seed_cell->GetPoints ()->GetPoint (0)[1],
                       seed_cell->GetPoints ()->GetPoint (0)[2]);
          vertex2D v1 (seed_cell->GetPoints ()->GetPoint (1)[0],
                       seed_cell->GetPoints ()->GetPoint (1)[1],
                       seed_cell->GetPoints ()->GetPoint (1)[2]);
          vertex2D v2 (seed_cell->GetPoints ()->GetPoint (2)[0],
                       seed_cell->GetPoints ()->GetPoint (2)[1],
                       seed_cell->GetPoints ()->GetPoint (2)[2]);
          vertex2D v3 (seed_cell->GetPoints ()->GetPoint (3)[0],
                       seed_cell->GetPoints ()->GetPoint (3)[1],
                       seed_cell->GetPoints ()->GetPoint (3)[2]);
          vertex2D v4 (0.0, 0.0, 0.0);
          vertex2D v5 (0.0, 0.0, 0.0);
          vertex2D v6 (0.0, 0.0, 0.0);
          vertex2D v7 (0.0, 0.0, 0.0);

          std::array<vertex2D, 8> hv{ v0, v1, v2, v3, v4, v5, v6, v7 };
          vertex2D temp = mapping::isoparametric<vertex2D> (ipnext, hv);

          /**
           *  Peform scaling to adjust for grid width.
           *
           *  scaling factor = grid width - eucledian distance between 'temp'
           * and 'next'.
           *
           *  Check if the vector formed using 'temp' and 'next'
           *  is parallel to one of the coordiante axes. If yes then
           *  we scale only one coordinate otherwise we perform
           *  scaling on all three coordinates.
           *
           *   If 'y' and 'z' are equal then scale the 'x' coordinate.
           *   If 'x' and 'z' are equal then scale the 'y' coordinate.
           *   If 'x' and 'y' are equal then scale the 'z' coordinate.
           */
          // vertex2D temp (x, y);
          double offset = m_width - next.distance (temp);
          if (next ('y') == temp ('y') && next ('z') == temp ('z'))
            {
              BIOMESH_ASSERT (next ('y') == temp ('y')
                              && next ('z') == temp ('z'));
              temp.scale ('x', offset);
            }
          else if (next ('x') == temp ('x') && next ('z') == temp ('z'))
            {
              BIOMESH_ASSERT (next ('x') == temp ('x')
                              && next ('z') == temp ('z'));
              temp.scale ('y', offset);
            }
          else if (next ('x') == temp ('x') && next ('y') == temp ('y'))
            {
              BIOMESH_ASSERT (next ('x') == temp ('x')
                              && next ('y') == temp ('y'));
              temp.scale ('z', offset);
            }
          else
            {
              temp.scale (offset);
            }

          /* Push to fiber grid data structure. */
          m_fiber_vertices.emplace_back (temp);

          /* Update grid point for next computation. */
          next = temp;

          /* Update 'point' for possible searching. */
          point[0] = next ('x');
          point[1] = next ('y');
          point[2] = next ('z');
        }
    }

  watch.end ();
  BIOMESH_LINFO (0, "Fiber vertex count = "
                        + std::to_string (m_fiber_vertices.size ()));
  BIOMESH_LINFO (0, "Fiber end.");
}

} // namespace biomesh