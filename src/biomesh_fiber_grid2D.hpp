
#ifndef BIOMESH_FIBER_GRID2D_HPP
#define BIOMESH_FIBER_GRID2D_HPP

#include <biomesh_fiber_grid_base.hpp>

namespace biomesh
{
class fiber_grid2D : protected fiber_grid
{
public:
  fiber_grid2D (const std::string &file_name);

  int generate_fiber_grid (const vector_field &vfield, size_t fpoint_count);

private:
  json_parser m_jparser;
  std::vector<fiber2D> m_fiber_set; /* Set of 1D fiber grids. */
};
} // namespace biomesh

#endif