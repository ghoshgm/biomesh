
#ifndef BIOMESH_VERTEX_BASE_HPP
#define BIOMESH_VERTEX_BASE_HPP

#include <Eigen/Dense>
#include <cmath>
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

  /**
   * Function to compute the eucledian distance between two vertices.
   */
  double distance (const vertex &other) const;

  /**
   * Print coordinates.
   */
  void print ();

protected:
  Eigen::Vector3d m_position; /* The X,Y,Z coordinates of the vertex. */
};

} // namespace biomesh

#endif