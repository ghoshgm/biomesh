
#include <biomesh_fiber3d.hpp>

namespace biomesh
{
fiber3D::fiber3D (size_t gpoint_count, double width)
    : m_gpoint_count{ gpoint_count }, m_width{ width }
{
  m_fiber_vertices.reserve (m_gpoint_count);
  m_fiber_vertices.emplace_back (m_seed);
}

fiber3D::fiber3D (const vertex3D &seed, size_t gpoint_count, double width)
    : m_seed{ seed }, m_gpoint_count{ gpoint_count }, m_width{ width }
{
  m_fiber_vertices.reserve (m_gpoint_count);
  m_fiber_vertices.emplace_back (m_seed);
}

fiber3D::fiber3D (const fiber3D &other)
{
  this->m_seed = other.m_seed;
  this->m_fiber_vertices = other.m_fiber_vertices;
}

fiber3D::fiber3D (fiber3D &&other)
{
  this->m_seed = other.m_seed;
  this->m_fiber_vertices = std::move (other.m_fiber_vertices);
}

fiber3D::~fiber3D () {}

void
fiber3D::generate_fiber (const vector_field &vfield)
{
  /* Obtain the structured grid. */
  auto sgrid = vfield.get_grid ();
  BIOMESH_ASSERT (sgrid != nullptr);

  BIOMESH_LINFO (0, "Fiber begin.");

  stopwatch watch;
  watch.start ();

  int subid;
  double pcoords[3];
  double weights[VTK_CELL_SIZE];

  int arridx = 1;
  vtkDataArray *da = sgrid->GetPointData ()->GetArray ("vectors", arridx);
  BIOMESH_ASSERT (da != nullptr);

  double point[3] = { m_seed ('x'), m_seed ('y'), m_seed ('z') };

  std::cout << "---- Cartesian coord ----" << std::endl;
  std::cout << point[0] << " " << point[1] << " " << point[2] << std::endl;
  std::cout << "-------------------------" << std::endl;

  vertex3D next = m_seed;
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
          BIOMESH_ASSERT (seed_cell->GetCellType () == VTK_HEXAHEDRON);

          /* Grab the point indices. */
          vtkIdList *pids = seed_cell->GetPointIds ();
          BIOMESH_ASSERT (pids != nullptr);

          /* Grab the vectors. */
          std::array<double, 8> vx{ (da->GetTuple3 (pids->GetId (0)))[0],
                                    (da->GetTuple3 (pids->GetId (1)))[0],
                                    (da->GetTuple3 (pids->GetId (2)))[0],
                                    (da->GetTuple3 (pids->GetId (3)))[0],
                                    (da->GetTuple3 (pids->GetId (4)))[0],
                                    (da->GetTuple3 (pids->GetId (5)))[0],
                                    (da->GetTuple3 (pids->GetId (6)))[0],
                                    (da->GetTuple3 (pids->GetId (7)))[0] };

          std::array<double, 8> vy{ (da->GetTuple3 (pids->GetId (0)))[1],
                                    (da->GetTuple3 (pids->GetId (1)))[1],
                                    (da->GetTuple3 (pids->GetId (2)))[1],
                                    (da->GetTuple3 (pids->GetId (3)))[1],
                                    (da->GetTuple3 (pids->GetId (4)))[1],
                                    (da->GetTuple3 (pids->GetId (5)))[1],
                                    (da->GetTuple3 (pids->GetId (6)))[1],
                                    (da->GetTuple3 (pids->GetId (7)))[1] };

          std::array<double, 8> vz{ (da->GetTuple3 (pids->GetId (0)))[2],
                                    (da->GetTuple3 (pids->GetId (1)))[2],
                                    (da->GetTuple3 (pids->GetId (2)))[2],
                                    (da->GetTuple3 (pids->GetId (3)))[2],
                                    (da->GetTuple3 (pids->GetId (4)))[2],
                                    (da->GetTuple3 (pids->GetId (5)))[2],
                                    (da->GetTuple3 (pids->GetId (6)))[2],
                                    (da->GetTuple3 (pids->GetId (7)))[2] };

          /* Trilinear interpolation in parametric coordinates. */
          vertex3D pnext (pcoords[0], pcoords[1], pcoords[2]);
          std::cout << "---- Parametric coords ----" << std::endl;
          pnext.print ();
          std::cout << "---------------------------" << std::endl;
          double r = interpolation::trilinear (pnext, vx);
          double s = interpolation::trilinear (pnext, vy);
          double t = interpolation::trilinear (pnext, vz);

          /* Map parametric coordinates back to cartesian coords. */
          vertex3D ipnext (r, s, t);
          std::cout << "---- Interpolated coord ----" << std::endl;
          ipnext.print ();
          std::cout << "----------------------------" << std::endl;
          vertex3D v0 (seed_cell->GetPoints ()->GetPoint (0)[0],
                       seed_cell->GetPoints ()->GetPoint (0)[1],
                       seed_cell->GetPoints ()->GetPoint (0)[2]);
          vertex3D v1 (seed_cell->GetPoints ()->GetPoint (1)[0],
                       seed_cell->GetPoints ()->GetPoint (1)[1],
                       seed_cell->GetPoints ()->GetPoint (1)[2]);
          vertex3D v2 (seed_cell->GetPoints ()->GetPoint (2)[0],
                       seed_cell->GetPoints ()->GetPoint (2)[1],
                       seed_cell->GetPoints ()->GetPoint (2)[2]);
          vertex3D v3 (seed_cell->GetPoints ()->GetPoint (3)[0],
                       seed_cell->GetPoints ()->GetPoint (3)[1],
                       seed_cell->GetPoints ()->GetPoint (3)[2]);
          vertex3D v4 (seed_cell->GetPoints ()->GetPoint (4)[0],
                       seed_cell->GetPoints ()->GetPoint (4)[1],
                       seed_cell->GetPoints ()->GetPoint (4)[2]);
          vertex3D v5 (seed_cell->GetPoints ()->GetPoint (5)[0],
                       seed_cell->GetPoints ()->GetPoint (5)[1],
                       seed_cell->GetPoints ()->GetPoint (5)[2]);
          vertex3D v6 (seed_cell->GetPoints ()->GetPoint (6)[0],
                       seed_cell->GetPoints ()->GetPoint (6)[1],
                       seed_cell->GetPoints ()->GetPoint (6)[2]);
          vertex3D v7 (seed_cell->GetPoints ()->GetPoint (7)[0],
                       seed_cell->GetPoints ()->GetPoint (7)[1],
                       seed_cell->GetPoints ()->GetPoint (7)[2]);

          std::array<vertex3D, 8> hv{ v0, v1, v2, v3, v4, v5, v6, v7 };
          vertex3D temp = mapping::isoparametric<vertex3D> (ipnext, hv);

#if 0
          double offset = m_width - next.distance (temp);
          if (next ('y') == temp ('y') && next ('z') == temp ('z'))
            {
              temp.scale ('x', offset);
            }
          else if (next ('x') == temp ('x') && next ('z') == temp ('z'))
            {
              temp.scale ('y', offset);
            }
          else if (next ('x') == temp ('x') && next ('y') == temp ('y'))
            {
              temp.scale ('z', offset);
            }
          else
            {
              temp.scale (offset);
            }
#endif

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

size_t
fiber3D::size () const
{
  return m_fiber_vertices.size ();
}

vertex3D
fiber3D::operator[] (int idx) const
{
  BIOMESH_ASSERT (idx >= 0 && idx < m_fiber_vertices.size ());
  return m_fiber_vertices[idx];
}

bool
fiber3D::operator== (const fiber3D &other) const
{
  return this->m_seed == other.m_seed;
}

} // namespace biomesh