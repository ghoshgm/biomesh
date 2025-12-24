
#ifndef BIOMESH_FIBER3D_HPP
#define BIOMESH_FIBER3D_HPP

#include <biomesh_fiber_base.hpp>
#include <biomesh_vertex3d.hpp>

namespace biomesh
{
/**
 * @brief Class for modelling a 3D fiber.
 *
 * Muscle fiber is represented as a 1D grid.
 * A fiber is modelled as an ordered set of cartesian coordiantes.
 * The input is a single vertex. This initial vertex will be used
 * to sequentially compute the next fiber vertex.
 * The output is a set of vertices which define the fiber geometry.
 */
class fiber3D : public fiber
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
  fiber3D (size_t gpoint_count, double width);

  /**
   * Constructor.
   *
   * @param[in] seed The initial vertex of the fiber.
   * @param[in] gpoint_count The number of grid points on fiber.
   * Let's say you want 4 grid points then the first point will be the seed.
   */
  fiber3D (const vertex3D &seed, size_t gpoint_count, double width);

  /**
   * Copy constructor.
   */
  fiber3D (const fiber3D &other);

  /**
   * Move constructor.
   */
  fiber3D (fiber3D &&other);

  /**
   * Destructor.
   */
  ~fiber3D ();

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
  vertex3D operator[] (size_t idx) const;

  /**
   * Function to modify the vertex coordiantes.
   *
   * @param[in] idx The index at which fiber vertex needs to be updated.
   * @param[in] x_new  The updated x coordinate.
   * @param[in] y_new  The updated y coordinate.
   * @param[in] z_new  The updated z coordinate.
   */
  void update_vertex (int idx, double x_new, double y_new, double z_new);

  /**
   * Function to generate fiber coordinates.
   *
   * @return Success if the fiber is valid otherwise Error is returned.
   */
  void generate_fiber (const vector_field &vfield);

  /**
   * Test equality of two fibers.
   *
   * @return True if equal otherwise false.
   */
  bool operator== (const fiber3D &other) const;

private:
  vertex3D m_seed;
  size_t m_gpoint_count;
  double m_width;
  std::vector<vertex3D> m_fiber_vertices;
};

} // namespace biomesh

#endif