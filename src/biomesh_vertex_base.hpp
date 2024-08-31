
#ifndef BIOMESH_VERTEX_BASE_HPP
#define BIOMESH_VERTEX_BASE_HPP

#include <Eigen/Dense>
#include <limits>

#include <biomesh_base.hpp>

namespace biomesh
{

/**
 * Base class for vertices/points in the Euclidean space.
 * This class defines all basic functions and members.
 */
class vertex
{
public:
  /**
   * Default constructor.
   */
  vertex ();

  /**
   * Default destructor.
   */
  ~vertex ();

  /**
   * Function to retrieve the value of coordiante.
   * Set dir to 'x' to get the X coordiante.
   * Set dir to 'y' to get the Y coordiante.
   * Set dir to 'z' to get the Z coordinate.
   *
   * If this function is called via vertex2D then
   * the Z coordinate will always be 0.
   *
   * If dir does not match 'x' or 'y' or 'z' then
   * DOUBLE_MAX will be returned.
   *
   * @param[in] dir The required coordinates value.
   *
   * @return The magnitude of the desired coordinate.
   */
  double operator() (char dir) const;

  /**
   * Function to test the equality of two vertices.
   *
   * @param[in] other The reference vertex object for comparison.
   *
   * @return True/False depending on the result.
   */
  bool operator== (const vertex &other) const;

  /**
   * Copy assignment operator.
   */
  void operator= (const vertex &other);

  /**
   * Function for scaling vertex location.
   *
   * This performs component wise multplication/division with a scalar value.
   *
   * @param[in] scaling_factor The factor by which the coordinates need to be
   * scaled.
   * @param[in] scale_up 1 = scale up and 0 = scale down.
   */
  void scale (double scaling_factor, int scale_up);

  /**
   * Print coordinates.
   */
  void print ();

protected:
  Eigen::Vector3d m_position; /* The X,Y,Z coordinates of the vertex. */
};

} // namespace biomesh

#endif