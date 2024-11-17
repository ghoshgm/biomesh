
#include <biomesh_fiber2d.hpp>

namespace biomesh
{
fiber2D::fiber2D (size_t gpoint_count, double width)
    : m_gpoint_count{ gpoint_count }, m_width{ width }
{
  m_fiber_vertices.reserve (m_gpoint_count);
}

fiber2D::fiber2D (const vertex2D &seed, size_t gpoint_count, double width)
    : m_seed{ seed }, m_gpoint_count{ gpoint_count }, m_width{ width }
{
  m_fiber_vertices.reserve (m_gpoint_count);
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

  double t_start = 0.0;
  double t_end = m_gpoint_count;
  double step_size = m_width;
  std::vector<double> state_vector{ m_seed ('x'), m_seed ('y') };

  boost::numeric::odeint::runge_kutta4<std::vector<double>> time_stepper;
  boost::numeric::odeint::integrate_const (
      time_stepper,
      [&] (const std::vector<double> &svec, std::vector<double> &drdt,
           double t) {
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

        /* Grab the vectors in the VTK structured grid. */
        int arridx = 1;
        vtkDataArray *da
            = sgrid->GetPointData ()->GetArray ("vectors", arridx);
        BIOMESH_ASSERT (da != nullptr);

        /* The initial seed vertex. */
        double current_vertex[3] = { svec[0], svec[1], 0.0 };
        auto cellid = sgrid->FindCell (current_vertex, nullptr, -1, 0, subid,
                                       pcoords, weights);

        /* Only consider the vertices within the bounds of the structured grid.
         */
        if (cellid >= 0)
          {
            /* Grab the cell. */
            vtkCell *seed_cell = sgrid->GetCell (cellid);
            BIOMESH_ASSERT (seed_cell != nullptr);
            BIOMESH_ASSERT (seed_cell->GetCellType () == VTK_QUAD);

            /* Grab the point indices. */
            vtkIdList *pids = seed_cell->GetPointIds ();
            BIOMESH_ASSERT (pids != nullptr);

            /* The x-component of the 4 vectors within the seed_cell. */
            std::array<double, 4> vx{ (da->GetTuple3 (pids->GetId (0)))[0],
                                      (da->GetTuple3 (pids->GetId (1)))[0],
                                      (da->GetTuple3 (pids->GetId (2)))[0],
                                      (da->GetTuple3 (pids->GetId (3)))[0] };

            /* The y-component of the 4 vectors within the seed_cell. */
            std::array<double, 4> vy{ (da->GetTuple3 (pids->GetId (0)))[1],
                                      (da->GetTuple3 (pids->GetId (1)))[1],
                                      (da->GetTuple3 (pids->GetId (2)))[1],
                                      (da->GetTuple3 (pids->GetId (3)))[1] };

            /* Compute next grid vertex using bilinear interpolation. */
            vertex2D pnext (pcoords[0], pcoords[1]);
            drdt[0] = interpolation::bilinear (pnext, vx);
            drdt[1] = interpolation::bilinear (pnext, vy);
          }
      },
      state_vector, t_start, t_end, step_size,
      [&, this] (const std::vector<double> &sv, double t) {
        int subid;
        double pcoords[3];
        double weights[VTK_CELL_SIZE];
        double next[3] = { sv[0], sv[1], 0.0 };
        auto cellid
            = sgrid->FindCell (next, nullptr, -1, 0, subid, pcoords, weights);
        if (cellid >= 0)
          {
            vertex2D next (sv[0], sv[1]);
            m_fiber_vertices.emplace_back (next);
          }
      });

  watch.end ();
  BIOMESH_LINFO (0, "Fiber vertex count = "
                        + std::to_string (m_fiber_vertices.size ()));
  BIOMESH_LINFO (0, "Fiber end.");
}

} // namespace biomesh