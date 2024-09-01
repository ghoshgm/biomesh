
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

  /**
   * Function for scaling all coordinates of a vertex.
   *
   * This performs component wise addition/subtraction with a scalar value.
   *
   * This function is to be used when adjusting the distance between two
   * consecutive fiber vertices as per the 'width' parameter provided
   * by the user.
   *
   * @param[in] scaling_factor The factor by which the coordinates need to be
   * scaled.
   * scaling_factor = width - distance between two consecutive fiber vertices.
   * If the scaling factor is positive then the vertex is scaled up
   * else if the scaling factor is negative then the vertex is scaled down.
   */
  void scale (double scaling_factor);

  /**
   * Function for scaling a single coordinate of a vertex.
   *
   * This performs addition/subtraction with a scalar value.
   *
   * This function is to be used when adjusting the distance between two
   * consecutive fiber vertices as per the 'width' parameter provided
   * by the user.
   *
   * @param[in] dir The coordinate direction that needs to be scaled.
   * Set to 'x' to scale the x-coordinate.
   * Set to 'y' to scale the y-coordinate.
   * Set to 'z' to scale the z-coordinate.
   *
   * @param[in] scaling_factor The factor by which the coordinates need to be
   * scaled.
   * scaling_factor = width - distance between two consecutive fiber vertices.
   * If the scaling factor is positive then the vertex is scaled up
   * else if the scaling factor is negative then the vertex is scaled down.
   */
  void scale (char dir, double scaling_factor);
};

} // namespace biomesh

#endif