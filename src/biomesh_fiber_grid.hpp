
#ifndef BIOMESH_FIBER_GRID_HPP
#define BIOMESH_FIBER_GRID_HPP

#include <biomesh_fiber2d.hpp>
#include <biomesh_fiber3d.hpp>
#include <biomesh_interpolation.hpp>
#include <biomesh_json_parser.hpp>
#include <biomesh_vector_field.hpp>
#include <biomesh_vertex2d.hpp>
#include <biomesh_vertex3d.hpp>

#include <vtkCell.h>

#include <string>
#include <vector>

namespace biomesh
{
template<class fiber>
class fiber_grid
{
public:
  fiber_grid (const std::string &file_name);

  int generate_fiber_grid (const vector_field &vfield, size_t fpoint_count);

private:
  size_t m_fiber_count;
  json_parser m_jparser;
  std::vector<fiber> m_fiber_set; /* Set of 1D fiber grids. */
};

} // namespace biomesh

#endif