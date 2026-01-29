
#ifndef BIOMESH_SEEDER_HPP
#define BIOMESH_SEEDER_HPP

#include <algorithm>
#include <vector>

#include <biomesh_vector_field.hpp>
#include <biomesh_vertex3d.hpp>

namespace biomesh
{

/**
 * @brief Class for generating seed vertices for the fibers.
 *
 * A seed vertex is simply a vertex in the cartesian space.
 * It is the initial condition for numeric integration routines.
 * The seed vertices are located on the seed plane.
 */

class seeder
{
public:
  /**
   * Default constructor.
   *
   * @param[in] seed_count The number of seeds required to generate fibers.
   */
  explicit seeder (size_t seed_count);

  /**
   * Destructor.
   */
  ~seeder ();

  /**
   * Operator to access the seed vertex at a specified index.
   *
   * @param[in] index Index to access individual seed vertices.
   */
  vertex3D operator[] (size_t index) const;

  /**
   * Routine to compute the seed vertices.
   *
   * @param[in] vfield The vector field embedded onto a VTK structured grid.
   * @param[in] splane The plane which intersects the VTK structured grid.
   */
  void generate_seeds (const vector_field &vfield);

  /**
   * Iterator for traversing seed points.
   */
  class iterator;

  iterator begin ();

  iterator end ();

private:
  size_t m_seed_count;
  std::vector<vertex3D> m_seeds;

public:
  class iterator
  {
    using category = std::forward_iterator_tag;
    using value_type = vertex3D;
    using pointer = vertex3D *;
    using reference = vertex3D &;

  public:
    /**
     * Constructor.
     */
    explicit iterator (pointer vertex_ptr) : m_vertex_ptr{ vertex_ptr } {}

    /**
     * Dereference operator.
     */
    reference
    operator* () const
    {
      return *m_vertex_ptr;
    }

    /**
     * Arrow operator.
     */
    pointer
    operator->()
    {
      return m_vertex_ptr;
    }

    /**
     * Equality operator.
     */
    friend bool
    operator== (const iterator &itr1, const iterator &itr2)
    {
      return itr1.m_vertex_ptr == itr2.m_vertex_ptr;
    }

    /**
     * Inequality operator.
     */
    friend bool
    operator!= (const iterator &itr1, const iterator &itr2)
    {
      return itr1.m_vertex_ptr != itr2.m_vertex_ptr;
    }

    /**
     * Pre-increment operator.
     */
    iterator
    operator++ ()
    {
      ++m_vertex_ptr;
      return *this;
    }

    /**
     * Post-increment operator.
     */
    iterator
    operator++ ([[maybe_unused]] int)
    {
      iterator tmp = *this;
      ++(*this);
      return tmp;
    }

  private:
    pointer m_vertex_ptr;
  };
};

} // namespace biomesh

#endif