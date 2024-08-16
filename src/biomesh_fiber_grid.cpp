
#include <biomesh_fiber_grid.hpp>

namespace biomesh
{
template<class fiber>
fiber_grid<fiber>::fiber_grid (const std::string &file_name)
    : m_fiber_count{ 0 }, m_jparser{ file_name }
{
}

template<class fiber>
int
fiber_grid<fiber>::generate_fiber_grid (const vector_field &vfield,
                                 size_t fpoint_count)
{
  m_jparser.read ();
  auto data = m_jparser.get_json_string ();
  m_fiber_count = data["seed_points"].size ();
  BIOMESH_ASSERT (m_fiber_count > 0);

  for (size_t ii = 0; ii < m_fiber_count; ++ii)
    {
      double x = (data["seed_points"][(unsigned)ii]["x"]).asDouble ();
      double y = (data["seed_points"][(unsigned)ii]["y"]).asDouble ();
      double z = (data["seed_points"][(unsigned)ii]["z"]).asDouble ();

#if 1
      std::cout << "x : " << x << std::endl;
      std::cout << "y : " << y << std::endl;
      std::cout << "z : " << z << std::endl;
#endif

#if 0
      /* Obtain the structured grid. */
      auto sgrid = vfield.get_grid();

      for(int cidx = 0; cidx < 1; ++cidx)
      {
        vtkCell* cell = sgrid->GetCell(0);

        vtkIdList* pids = cell->GetPointIds();
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

  return BIOMESH_SUCCESS;
}

template class fiber_grid<fiber2D>;
template class fiber_grid<fiber3D>;

}