
#ifndef BIOMESH_HPP
#define BIOMESH_HPP

#include <biomesh_base.hpp>
#include <biomesh_vertex.hpp>
#include <vector>

namespace biomesh
{
/**
 * @brief Class for modelling muscle fibers.
 *
 * Muscle fiber is represented as a 1D grid.
 * A fiber is modelled as an ordered set of cartesian coordiantes.
 *
 */
class fiber
{
public:
  /**
   * Default constructor.
   */
  fiber ();

  /**
   * Copy constructor.
   */
  fiber (const fiber &other);

  /**
   * Move constructor.
   */
  fiber (fiber &&other);

  /**
   * Get the set of vertices for this fiber.
   */
  std::vector<vertex> get_vertices () const;

  /**
   * Get the vertex at a specified index.
   */
  vertex operator[] (int index) const;

private:
  std::vector<vertex> m_vset; /* Set of vertices. */
};

/* TODO: Implement fiber_grid, mechanics_grid, muscle */

} // namespace biomesh

#endif