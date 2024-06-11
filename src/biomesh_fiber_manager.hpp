
#ifndef BIOMESH_FIBER_MANAGER_HPP
#define BIOMESH_FIBER_MANAGER_HPP

#include <biomesh_fiber2d.hpp>
#include <biomesh_fiber3d.hpp>

#include <vector>

namespace biomesh
{

template <class fiber> class fiber_manager
{
public:
  fiber_manager ();

  int generate_fiber_grid ();

private:
  std::vector<fiber> m_fset; /* Set of 1D fiber grids. */
};

} // namespace biomesh

#endif