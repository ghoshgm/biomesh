
#include <biomesh_fiber3d.hpp>

#include <algorithm>

namespace biomesh
{
fiber3D::fiber3D (size_t gpoint_count, double width)
    : m_gpoint_count{ gpoint_count }, m_width{ width }
{
  m_fiber_vertices.reserve (m_gpoint_count);
}

fiber3D::fiber3D (const vertex3D &seed, size_t gpoint_count, double width)
    : m_seed{ seed }, m_gpoint_count{ gpoint_count }, m_width{ width }
{
  m_fiber_vertices.reserve (m_gpoint_count);
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

static void
compute_vector (vtkStructuredGrid *sgrid, const std::vector<double> &svec,
                std::vector<double> &drdt, double t, int &cid)
{
  /**
   * The 'FindCell' function in the VTK lib returns more information
   * than needed. We are only interested in the return value of the
   * function and 'pcoords'. The variables 'subid','weights' are
   * return variables which are not needed for our application
   * but are essential to avoid segfaults.
   */
  int subid;
  double pcoords[3];
  double weights[VTK_CELL_SIZE];

  int arridx = 1;
  vtkDataArray *da = sgrid->GetPointData ()->GetArray ("vectors", arridx);
  // vtkDataArray *da = sgrid->GetPointData ()->GetArray ("flowExt", arridx);
  BIOMESH_ASSERT ((da != nullptr));

  /* The initial seed vertex. */
  double current_vertex[3] = { svec[0], svec[1], svec[2] };
  auto cellid = sgrid->FindCell (current_vertex, nullptr, -1, 0, subid,
                                 pcoords, weights);

  /* Only consider the vertices within the bounds of the structured grid.
   */
  if (cellid >= 0)
    {
      cid = cellid;

      /* Grab the cell. */
      vtkCell *seed_cell = sgrid->GetCell (cellid);
      BIOMESH_ASSERT ((seed_cell != nullptr));
      BIOMESH_ASSERT ((seed_cell->GetCellType () == VTK_HEXAHEDRON));

      /* Grab the point indices. */
      vtkIdList *pids = seed_cell->GetPointIds ();
      BIOMESH_ASSERT ((pids != nullptr));

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
      drdt[0] = interpolation::trilinear (pnext, vx);
      drdt[1] = interpolation::trilinear (pnext, vy);
      drdt[2] = interpolation::trilinear (pnext, vz);
    }
}

static bool
is_inside_grid (vtkStructuredGrid *sgrid, const std::vector<double> &v)
{
  double *bb = sgrid->GetBounds ();
  return ((v[0] >= bb[0] and v[0] <= bb[1])
          and (v[1] >= bb[2] and v[1] <= bb[3])
          and (v[2] >= bb[4] and v[2] <= bb[5]));
}

void
fiber3D::generate_fiber (const vector_field &vfield)
{
  /* Obtain the structured grid. */
  auto sgrid = vfield.get_grid ().GetPointer ();
  BIOMESH_ASSERT ((sgrid != nullptr));

  stopwatch watch;
  watch.start ();

  double t_start = 0.0;
  double t_end = m_gpoint_count * m_width;
  double dt = m_width;
  std::vector<double> vertex{ m_seed ('x'), m_seed ('y'), m_seed ('z') };

  boost::numeric::odeint::runge_kutta4<std::vector<double> > rk4_stepper;

  /* Compute fibers. */
  while (t_start < t_end and is_inside_grid (sgrid, vertex))
    {
      /* Push to fiber. */
      m_fiber_vertices.emplace_back (
          vertex3D (vertex[0], vertex[1], vertex[2]));

      /* Do one step of numeric integration. */
      int cell_id = 0;
      rk4_stepper.do_step (
          [&] (const std::vector<double> &svec, std::vector<double> &drdt,
               double t) { compute_vector (sgrid, svec, drdt, t, cell_id); },
          vertex, t_start, dt);

      /* Set distance between two adjacent vertices. */
      Eigen::Vector3d vv1 (m_fiber_vertices.back () ('x'),
                           m_fiber_vertices.back () ('y'),
                           m_fiber_vertices.back () ('z'));
      Eigen::Vector3d vv2 (vertex[0], vertex[1], vertex[2]);
      Eigen::Vector3d cv = vv2 - vv1;
#if 0
      if(vfield[cell_id] == 0)
      {
        break;
      }
#endif
#if 1
      if (BIOMESH_DCOMP (cv.norm (), 0.0))
        {
          break;
        }
#endif
      Eigen::Vector3d v_new = vv1 + ((cv / cv.norm ()) * dt);
      vertex[0] = v_new (0);
      vertex[1] = v_new (1);
      vertex[2] = v_new (2);

#ifdef BIOMESH_ENABLE_DEBUG
      double x_diff = std::fabs (vertex[0] - m_fiber_vertices.back () ('x'));
      double y_diff = std::fabs (vertex[1] - m_fiber_vertices.back () ('y'));
      double z_diff = std::fabs (vertex[2] - m_fiber_vertices.back () ('z'));
      double distance
          = std::sqrt (std::pow (x_diff, 2.0) + std::pow (y_diff, 2.0)
                       + std::pow (z_diff, 2.0));
      BIOMESH_ASSERT (BIOMESH_DCOMP (distance, m_width));
#endif

      /* Increment step. */
      t_start += dt;
    }

  watch.end ();
  BIOMESH_LINFO ("Fiber vertex count = "
                 + std::to_string (m_fiber_vertices.size ()));
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

void
fiber3D::reverse ()
{
  std::reverse (m_fiber_vertices.begin (), m_fiber_vertices.end ());
}

void
fiber3D::print_vertices () const
{
  for (size_t ii = 0; ii < m_fiber_vertices.size (); ++ii)
    {
      m_fiber_vertices[ii].print ();
    }
}

void
fiber3D::translate (double val)
{
  for (size_t ii = 0; ii < m_fiber_vertices.size (); ++ii)
    {
      double x = m_fiber_vertices[ii]('x');
      double y = m_fiber_vertices[ii]('y');
      double z = m_fiber_vertices[ii]('z') + val;

      m_fiber_vertices[ii].print ();
      m_fiber_vertices[ii](x, y, z);
      m_fiber_vertices[ii].print ();
    }
  for (size_t ii = 0; ii < m_fiber_vertices.size (); ++ii)
    {
      m_fiber_vertices[ii].print ();
    }
#if 0
  for(size_t ii = 0; ii < m_fiber_vertices.size(); ++ii)
  {
    auto v = m_fiber_vertices[ii];
    double x = v('x') + val;
    double y = v('y') + val;
    double z = v('z') + val;

    v(x,y,z);
  }
#endif
}

} // namespace biomesh