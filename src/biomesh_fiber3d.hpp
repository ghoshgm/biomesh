
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
   */
  fiber3D ();

  /**
   * Constructor.
   *
   * @param[in] seed The initial vertex of the fiber.
   */
  fiber3D (const vertex3D &seed);

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
   * Function to generate fiber coordinates.
   */
  int generate_fiber ();

  /**
   * Test equality of two fibers.
   */
  bool operator== (const fiber3D &other) const;

private:
  vertex3D m_seed;
  std::vector<vertex3D> m_fiber_vertices;
};

} // namespace biomesh

#endif