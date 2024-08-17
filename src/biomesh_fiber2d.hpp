
#ifndef BIOMESH_FIBER2D_HPP
#define BIOMESH_FIBER2D_HPP

#include <biomesh_fiber_base.hpp>
#include <biomesh_vertex2d.hpp>

namespace biomesh
{
/**
 * @brief Class for modelling a 2D fiber.
 *
 * Muscle fiber is represented as a 1D grid.
 * A fiber is modelled as an ordered set of cartesian coordiantes.
 * The input is a single vertex. This initial vertex will be used
 * to sequentially compute the next fiber vertex.
 * The output is a set of vertices which define the fiber geometry.
 */
class fiber2D : public fiber
{
public:
  /**
   * Default constructor.
   */
  fiber2D ();

  /**
   * Constructor.
   *
   * @param[in] seed The initial vertex of the fiber.
   */
  fiber2D (const vertex2D &seed);

  /**
   * Copy constructor.
   *
   * @param[in] other The reference fiber2D object that needs to be copied.
   */
  fiber2D (const fiber2D &other);

  /**
   * Move constructor.
   *
   * @param[in] other The reference fiber2D object whose data needs to be
   * moved.
   */
  fiber2D (fiber2D &&other);

  /**
   * Destructor.
   */
  ~fiber2D ();

  /**
   * Test equality of two fibers.
   */
  bool operator== (const fiber2D &other) const;

  /**
   * Generate fiber.
   *
   * @param[in] vfield The vector field which will be used to interpolate grid
   * point in a fiber.
   * @param[in] fpoint_count The number of grid points on a single grid.
   */
  void generate_fiber (const vector_field &vfield, size_t fpoint_count);

private:
  vertex2D m_seed;
  std::vector<vertex2D> m_fiber_vertices;
};

} // namespace biomesh

#endif