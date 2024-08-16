
#ifndef BIOMESH_FIBER_HPP
#define BIOMESH_FIBER_HPP

#include <biomesh_base.hpp>
#include <biomesh_vector_field.hpp>
#include <biomesh_vertex2d.hpp>
#include <biomesh_vertex3d.hpp>

#include <utility>
#include <vector>

namespace biomesh
{
/**
 * @brief Base class for modelling muscle fibers.
 *
 * Muscle fiber is represented as a 1D grid.
 * A fiber is modelled as an ordered set of cartesian coordiantes.
 * The input is a single vertex. This initial vertex will be used
 * to sequentially compute the next fiber vertex.
 * The output is a set of vertices which define the fiber geometry.
 */
class fiber
{
public:
  /**
   * Function to generate the fiber coordinates.
   */
  virtual int generate_fiber (const vector_field &vfield, size_t fpoint_count)
      = 0;
};

} // namespace biomesh

#endif