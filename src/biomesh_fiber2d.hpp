
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
   *
   * The seed coordinates are set to 0 by default.
   *
   * @param[in] gpoint_count The number of grid points on fiber.
   * Let's say you want 4 grid points then the first point will be the seed.
   */
  fiber2D (size_t gpoint_count, double width);

  /**
   * Constructor.
   *
   * @param[in] seed The initial vertex of the fiber.
   * @param[in] gpoint_count The number of grid points on fiber.
   * Let's say you want 4 grid points then the first point will be the seed.
   */
  fiber2D (const vertex2D &seed, size_t gpoint_count, double width);

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
   * Return the grid point count.
   *
   * @return The grid point count.
   */
  size_t size () const;

  /**
   * Return vertex at the specified index.
   *
   * @param[in] idx The index at which fiber vertex is located.
   *
   * @return The vertex at index 'idx'.
   */
  vertex2D operator[] (size_t idx) const;

  /**
   * Test equality of two fibers.
   *
   * @return True if equal otherwise false.
   */
  bool operator== (const fiber2D &other) const;

  /**
   * Generate fiber.
   *
   * @param[in] vfield The vector field which will be used to interpolate grid
   * point in a fiber.
   */
  void generate_fiber (const vector_field &vfield);

  void pop ();

private:
  vertex2D m_seed;
  size_t m_gpoint_count;
  double m_width;
  std::vector<vertex2D> m_fiber_vertices;
};

} // namespace biomesh

#endif