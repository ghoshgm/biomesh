
#ifndef BIOMESH_VERTEX2D_HPP
#define BIOMESH_VERTEX2D_HPP

#include <biomesh_vertex_base.hpp>

namespace biomesh
{

/**
 * @brief Derived class for 2D vertices/points in the Eucledian space.
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
   * Constructor.
   *
   * This is a helper constructor to avoid complicated templated code.
   * The Z coordinate must be set to 0.
   *
   * @param[in] x The X coordinate
   * @param[in] y The Y coordinate
   * @param[in] z The Z coordinate
   */
  vertex2D (double x, double y, double z);

  /**
   * Destructor.
   */
  ~vertex2D ();
};

} // namespace biomesh

#endif