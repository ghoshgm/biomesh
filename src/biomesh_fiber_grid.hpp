
#ifndef BIOMESH_FIBER_GRID_HPP
#define BIOMESH_FIBER_GRID_HPP

#include <biomesh_fiber2d.hpp>
#include <biomesh_fiber3d.hpp>
#include <biomesh_vector_field.hpp>

#include <vector>

namespace biomesh
{

template <class fiber> class fiber_grid
{
public:
  fiber_grid ();

  int generate_fiber_grid ();

private:
  std::vector<fiber> m_fiber_set; /* Set of 1D fiber grids. */
};

} // namespace biomesh

#endif