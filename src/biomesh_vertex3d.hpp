
#ifndef BIOMESH_VERTEX3D_HPP
#define BIOMESH_VERTEX3D_HPP

#include <biomesh_vertex_base.hpp>

namespace biomesh
{

/**
 * Derived class for 3D vertices/points in the Eucledian space.
 */
class vertex3D : public vertex
{
public:
  /**
   * Default constructor.
   */
  vertex3D ();

  /**
   * Constructor.
   *
   * @param[in] x The X coordinate
   * @param[in] y The Y coordinate
   * @param[in] z The Z coordinate
   */
  vertex3D (double x, double y, double z);

  /**
   * Destructor.
   */
  ~vertex3D ();
};

} // namespace biomesh

#endif