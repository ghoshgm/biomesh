
#ifndef BIOMESH_VERTEX2D_HPP
#define BIOMESH_VERTEX2D_HPP

#include <biomesh_vertex_base.hpp>

namespace biomesh
{

/**
 * Derived class for 2D vertices/points in the Eucledian space.
 */
class vertex2D : public vertex
{
public:
  /**
   * Default constructor.
   *
   * Sets the coordinates to 0.
   */
  vertex2D ();

  /**
   * Constructor.
   *
   * @param[in] x The X coordinate
   * @param[in] y The Y coordinate
   */
  vertex2D (double x, double y);

  /**
   * Destructor.
   */
  ~vertex2D ();
};

} // namespace biomesh

#endif