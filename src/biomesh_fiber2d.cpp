
#include <biomesh_fiber2d.hpp>

namespace biomesh
{
fiber2D::fiber2D () {}

fiber2D::fiber2D (const vertex2D &seed) : m_seed{ seed } {}

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

int
fiber2D::generate_fiber (const vector_field &vfield, size_t fpoint_count)
{
#if 0
      /* Obtain the structured grid. */
      auto sgrid = vfield.get_grid ();

      /* Loop over the starter cells. */
      for (size_t ii = 0; ii < 1; ++ii)
        {
          /* Grab the cell. */
          vtkCell *cell = sgrid->GetCell (ii);

          /* Grab the locations of the vectors. */
          double* l1 = sgrid->GetPoint(0);
          //vertex v1(l1[0],l1[1]);
          double* l2 = sgrid->GetPoint(1);
          double* l3 = sgrid->GetPoint(3);
          double* l4 = sgrid->GetPoint(2);

          vtkIdList *pids = cell->GetPointIds ();

          

          /* Generate grid point on the fiber. */
          for (size_t jj = 0; jj < fpoint_count; ++jj)
            {
            }
        }
#endif

#if 0
      for(int cidx = 0; cidx < 1; ++cidx)
      {
        
      }

      /* TODO: Move this for-loop into fiber class.
         Otherwise it would be difficult to test for 2D and 3D.
         For now this only works for 2D.      
       */
      for(size_t jj = 0; jj < fpoint_count; ++jj)
      {
        /* seed point. */
        vertex seed (x, y, z);

        /* Next computed vertex. */
        vertex next;

        /* Initialize fiber. */
        m_fiber_set[ii](seed);

        /* Bilinear interpolation. */
        //double x = interpolation::bilinear();
        //double y = interpolation::bilinear();
      }
#endif
}

} // namespace biomesh