
#ifndef BIOMESH_FIBER_GRID_BASE_HPP
#define BIOMESH_FIBER_GRID_BASE_HPP

#include <biomesh_fiber2d.hpp>
#include <biomesh_fiber3d.hpp>
#include <biomesh_interpolation.hpp>
#include <biomesh_json_parser.hpp>
#include <biomesh_vector_field.hpp>
#include <biomesh_vertex2d.hpp>
#include <biomesh_vertex3d.hpp>

#include <vtkCell.h>
#include <vtkDataArray.h>

#include <string>
#include <vector>

namespace biomesh
{
class fiber_grid
{
protected:
  fiber_grid ();

protected:
  size_t m_fiber_count;
};

} // namespace biomesh

#endif