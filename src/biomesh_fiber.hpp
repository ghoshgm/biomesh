
#ifndef BIOMESH_FIBER_HPP
#define BIOMESH_FIBER_HPP

#include <biomesh_base.hpp>
#include <biomesh_vertex.hpp>
#include <utility>
#include <vector>

namespace biomesh
{
/**
 * @brief Class for modelling muscle fibers.
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
   * Default constructor.
   *
   * @param[in] start_point The vertex from which subsequent fiber vertices
   * will be computed.
   */
  fiber (const vertex &start_point);

  /**
   * Copy constructor.
   *
   * @param[in] other The reference fiber whose data needs to be copied.
   */
  fiber (const fiber &other);

  /**
   * Move constructor.
   *
   * @param[in] other The reference fiber whose data needs to be moved.
   */
  fiber (fiber &&other);

  /**
   * Function to generate the fiber coordinates.
   */
  int generate_fiber ();

  /**
   * Get the set of vertices for this fiber.
   */
  std::vector<vertex> get_vertices () const;

  /**
   * Get the vertex at a specified index.
   *
   * @param[in] index The index of the vertex in m_vset.
   */
  vertex operator[] (size_t index) const;

private:
  vertex seed;                /* Starting point of fiber. */
  std::vector<vertex> m_vset; /* Set of vertices. */
};

} // namespace biomesh

#endif