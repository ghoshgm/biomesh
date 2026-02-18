
#include <biomesh_fiber3d.hpp>

#include <algorithm>
#include <unordered_set>

namespace biomesh
{
fiber3D::fiber3D (double width) : m_width{ width } {}

fiber3D::fiber3D (const vertex3D &seed, double width)
    : m_seed{ seed }, m_width{ width }
{
  m_fiber_vertices.push_back (m_seed);
}

fiber3D::fiber3D (const fiber3D &other)
{
  this->m_gpoint_count = other.m_gpoint_count;
  this->m_width = other.m_width;
  this->m_seed = other.m_seed;
  this->m_fiber_vertices = other.m_fiber_vertices;
}

fiber3D &
fiber3D::operator= (fiber3D &other)
{
  std::swap (m_seed, other.m_seed);
  std::swap (m_gpoint_count, other.m_gpoint_count);
  std::swap (m_width, other.m_width);
  std::swap (m_fiber_vertices, other.m_fiber_vertices);
  return *this;
}

fiber3D::fiber3D (fiber3D &&other)
{
  this->m_seed = other.m_seed;
  this->m_width = other.m_width;
  this->m_gpoint_count = other.m_gpoint_count;
  this->m_fiber_vertices = std::move (other.m_fiber_vertices);
}

fiber3D::~fiber3D () {}

static void
compute_vector (vtkStructuredGrid *sgrid, const std::vector<double> &svec,
                std::vector<double> &drdt, double t, int &cid,
                const std::string &vfield_tag)
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
  vtkDataArray *da
      = sgrid->GetPointData ()->GetArray (vfield_tag.c_str (), arridx);
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

#if 0
static bool
is_inside_grid (vtkStructuredGrid *sgrid, const std::vector<double> &v)
{
  double *bb = sgrid->GetBounds ();
  return ((v[0] >= bb[0] and v[0] <= bb[1])
          and (v[1] >= bb[2] and v[1] <= bb[3])
          and (v[2] >= bb[4] and v[2] <= bb[5]));
}
#endif

void
fiber3D::generate_fiber (const vector_field &vfield, int dir,
                         configuration config)
{
  /* Obtain the structured grid. */
  auto sgrid = vfield.get_grid ().GetPointer ();
  BIOMESH_ASSERT ((sgrid != nullptr));

  double t_start = 0.0;
  double dt = m_width;
  std::vector<double> vertex{ m_seed ('x'), m_seed ('y'), m_seed ('z') };

  boost::numeric::odeint::runge_kutta4<std::vector<double> > rk4_stepper;

  bool adaptive;
  if (config.get_value<std::string> ("strategy") == "static")
    {
      adaptive = false;
    }
  else if (config.get_value<std::string> ("strategy") == "adaptive")
    {
      adaptive = true;
    }

  int adaptive_count = 0;
  int adaptive_tol = config.get_value<int> ("adaptive_steps_max");

  int subid;
  double pcoords[3];
  double weights[VTK_CELL_SIZE];

  /* The initial seed vertex. */
  auto cell_id = -1;
  cell_id = sgrid->FindCell (vertex.data (), nullptr, -1, 0, subid, pcoords,
                             weights);
  BIOMESH_ASSERT ((cell_id > 0));

  int t = 0;
  int t_max = config.get_value<int> ("time_step_max");

  /* Compute fibers. */
  while ((vfield[cell_id] == 2 or vfield[cell_id] == 1) and t < t_max)
    {
      if (!adaptive or (adaptive and adaptive_count == adaptive_tol))
        {
          vertex3D next (vertex[0], vertex[1], vertex[2]);

          if (!(m_fiber_vertices.back () == next))
            {
              /* Push to fiber. */
              m_fiber_vertices.emplace_back (
                  vertex3D (vertex[0], vertex[1], vertex[2]));
            }
#if 0
          /* Push to fiber. */
          m_fiber_vertices.emplace_back (
              vertex3D (vertex[0], vertex[1], vertex[2]));
#endif
        }

      /* Do one step of numeric integration. */
      rk4_stepper.do_step (
          [&] (const std::vector<double> &svec, std::vector<double> &drdt,
               double t) {
            compute_vector (sgrid, svec, drdt, t, cell_id, vfield.get_tag ());
          },
          vertex, t_start, dt);

      /* Set distance between two adjacent vertices. */
      Eigen::Vector3d vv1 (m_fiber_vertices.back () ('x'),
                           m_fiber_vertices.back () ('y'),
                           m_fiber_vertices.back () ('z'));
      Eigen::Vector3d vv2 (vertex[0], vertex[1], vertex[2]);
      Eigen::Vector3d cv;

      if (vv2 != vv1)
        {
          cv = vv2 - vv1;
          if (dir == 1)
            {
              cv = -cv;
            }
        }

      /*Terminating condition. */
      if (vfield[cell_id] == 0)
        {
          if (adaptive and adaptive_count <= adaptive_tol)
            {
              if (adaptive_count == adaptive_tol)
                {
                  break;
                }

              dt = dt / 2.0;

              ++adaptive_count;
            }
          else if (!adaptive)
            {
              break;
            }
        }

      /* Update current vertex. */
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
      BIOMESH_ASSERT (BIOMESH_DCOMP (distance, dt));
#endif

      /* Increment step. */
      t_start += dt;
      ++t;
    }
}

size_t
fiber3D::size () const
{
  return m_fiber_vertices.size ();
}

vertex3D
fiber3D::operator[] (int idx) const
{
  BIOMESH_ASSERT ((idx >= 0 && idx < m_fiber_vertices.size ()));
  return m_fiber_vertices[idx];
}

void
fiber3D::update_vertex (int idx, double x_new, double y_new, double z_new)
{
  BIOMESH_ASSERT ((idx >= 0 && idx < m_fiber_vertices.size ()));
  m_fiber_vertices[idx](x_new, y_new, z_new);
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

bool
fiber3D::is_valid () const
{
  /**
   * TODO: Move this functor into the vertex base class.
   */
  struct vertex3DHash
  {
    std::size_t
    operator() (const vertex3D &v) const
    {
      // Use std::hash to hash individual components
      std::size_t h1 = std::hash<double>{}(v ('x'));
      std::size_t h2 = std::hash<double>{}(v ('y'));
      std::size_t h3 = std::hash<double>{}(v ('z'));

      // Combine hashes using bit shifting and XOR to reduce collisions
      // A common hash-combining technique
      return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
  };

  std::unordered_set<vertex3D, vertex3DHash> s;

  for (const auto &v : m_fiber_vertices)
    {
      if (!s.insert (v).second)
        {
          return false; // duplicate found
        }
    }
  return true;
}

} // namespace biomesh
