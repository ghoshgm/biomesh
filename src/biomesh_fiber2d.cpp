
#include <biomesh_fiber2d.hpp>

namespace biomesh
{
fiber2D::fiber2D (size_t gpoint_count) : m_gpoint_count{ gpoint_count }
{
  m_fiber_vertices.reserve (m_gpoint_count);
  m_fiber_vertices.emplace_back (m_seed);
}

fiber2D::fiber2D (const vertex2D &seed, size_t gpoint_count)
    : m_seed{ seed }, m_gpoint_count{ gpoint_count }
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

  /* Loop over the starter cells. */
  for (size_t ii = 0; ii < 1; ++ii)
    {
      /* Grab the cell. */
      vtkCell *cell = sgrid->GetCell (ii);
      BIOMESH_ASSERT (cell != nullptr);

      /* Grab min vertex. */
      vertex2D lmin ((sgrid->GetPoint (0))[0], (sgrid->GetPoint (0))[1]);
      /* Grab max vertex. */
      vertex2D lmax ((sgrid->GetPoint (3))[0], (sgrid->GetPoint (3))[1]);

      /* Grab the vectors. */
      vtkIdList *pids = cell->GetPointIds ();
      BIOMESH_ASSERT (pids != nullptr);
      int arridx = 1;
      vtkDataArray *da = sgrid->GetPointData ()->GetArray ("vectors", arridx);
      BIOMESH_ASSERT (pids != nullptr);
      double v1x = (da->GetTuple3 (pids->GetId (0)))[0];
      double v1y = (da->GetTuple3 (pids->GetId (0)))[1];
      double v2x = (da->GetTuple3 (pids->GetId (1)))[0];
      double v2y = (da->GetTuple3 (pids->GetId (1)))[1];
      double v3x = (da->GetTuple3 (pids->GetId (2)))[0];
      double v3y = (da->GetTuple3 (pids->GetId (2)))[1];
      double v4x = (da->GetTuple3 (pids->GetId (3)))[0];
      double v4y = (da->GetTuple3 (pids->GetId (3)))[1];

      /* Iteratively generate grid point on every fiber. */
      vertex2D m_next = m_seed;
      for (size_t jj = 0; jj < m_gpoint_count - 1; ++jj)
        {
          double x = interpolation::bilinear (lmin, lmax, m_next, v1x, v2x,
                                              v3x, v4x);
          double y = interpolation::bilinear (lmin, lmax, m_next, v1y, v2y,
                                              v3y, v4y);

          vertex2D temp (x, y);
          temp.print ();
          m_fiber_vertices.emplace_back (temp);

          m_next = temp;
        }
    }
}

} // namespace biomesh