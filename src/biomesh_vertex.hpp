
#ifndef BIOMESH_VERTEX_HPP
#define BIOMESH_VERTEX_HPP

#include <biomesh_base.hpp>
#include <cmath>

namespace biomesh
{
/**
 * @brief Class for cartesian coordinates.
 */
class vertex
{
public:
  /**
   * Default constructor.
   */
  vertex ();

  /**
   * Custom constructor.
   *
   * @param[in] x The x coordiante.
   * @param[in] y The y coordiante.
   * @param[in] z The z coordiante.
   */
  vertex (double x, double y
#ifdef BIOMESH_ENABLE_3D
          ,
          double z
#endif
  );

  /**
   * Getter for co-ordinate in the X,Y,Z direction.
   *
   * Set dir to 'x' for x coordinate.
   * Set dir to 'y' for y coordinate.
   * Set dir to 'z' for z coordinate.
   *
   * @param[in] dir The coordinate direction.
   */
  double operator() (char dir) const;

  /**
   * Comparator for two vertices.
   *
   * @param[in] other The reference vertex for comparison.
   */
  bool operator== (const vertex &other) const;

private:
  double m_x, m_y, m_z; /* Cartesian coordinates. */
};
} // namespace biomesh
#endif