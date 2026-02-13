
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
class fiber3D : public fiber<fiber3D>
{
public:
  /**
   * Default constructor.
   *
   * The seed coordinates are set to 0 by default.
   *
   * @param[in] width The distance between two fiber vertices.
   */
  fiber3D (double width);

  /**
   * Constructor.
   *
   * @param[in] seed The initial vertex of the fiber.
   * @param[in] width The distance between two fiber vertices.
   */
  fiber3D (const vertex3D &seed, double width);

  /**
   * Copy constructor.
   */
  fiber3D (const fiber3D &other);

  /**
   * Copy assignment operator.
   */
  fiber3D &operator= (fiber3D &other);

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
  vertex3D operator[] (int idx) const;

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
   * @param[in] vfield The vector field.
   * @param[in] dir    The direction of fiber in the vector field.
   * @param[in] config The object which holds the configuration data.
   */
  void generate_fiber (const vector_field &vfield, int dir,
                       configuration config);

  /**
   * Test equality of two fibers.
   *
   * @return True if equal otherwise false.
   */
  bool operator== (const fiber3D &other) const;

  /**
   * Function to reverse the order of vertices.
   */
  void reverse ();

  /**
   * Test the validity of the fiber.
   *
   * Currently, we only check for duplicate vertices
   * because the diffusion solver diverges if duplicates exist.
   */
  bool is_valid () const;

private:
  vertex3D m_seed;
  size_t m_gpoint_count;
  double m_width;
  std::vector<vertex3D> m_fiber_vertices;
};

} // namespace biomesh

#endif