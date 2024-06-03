
#ifndef BIOMESH_FIBER_MANAGER_HPP
#define BIOMESH_FIBER_MANAGER_HPP

#include <biomesh_fiber.hpp>

#include <vector>
#ifdef BIOMESH_ENABLE_MPI
#include <mpi.h>
#endif

namespace biomesh
{

class fiber_manager
{
public:
  fiber_manager ();

#ifdef BIOMESH_ENABLE_MPI
  fiber_manager (MPI_Comm comm);
#endif

  int generate ();

private:
#ifdef BIOMESH_ENABLE_MPI
  MPI_Comm comm;
  size_t partition_start;
  size_t partition_end;
#endif

  std::vector<fiber> m_fset; /* Set of 1D fiber grids. */
};

} // namespace biomesh

#endif