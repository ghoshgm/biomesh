
#ifndef BIOMESH_SEED_PLANE_HPP
#define BIOMESH_SEED_PLANE_HPP

#include <memory>
#include <tuple>
#include <vector>

#include <vtkCell.h>
#include <vtkCutter.h>
#include <vtkPlane.h>
#include <vtkPolyData.h>
#include <vtkTriangle.h>

#include <biomesh_vector_field.hpp>

namespace biomesh
{
/**
 * @brief Class to model the seed plane for seed vertices.
 *
 * The seed plane is modelled using the point-normal formulation.
 * This plane is supposed to intersect the VTK structured grid.
 * The intersection between the plane and the structured grid is a 2D surface.
 * The VTK library models the 2D surface as a surface triangulation.
 *
 * The seed vertices are computed on this surface triangulation.
 * We only consider the triangles within the bounds of the vector field.
 */
class seed_plane
{
public:
  using plane_point = std::tuple<double, double, double>;
  using plane_normal = std::tuple<double, double, double>;
  using surface_triangulation = std::vector<vtkTriangle *>;

  /**
   * Constructor.
   *
   * @param[in] ppoint The point describing the seed plane.
   * @param[in] pnormal The orientation of the seed plane.
   */
  seed_plane (const plane_point &ppoint, const plane_normal &pnormal);

  /**
   * Destructor.
   */
  ~seed_plane ();

  /**
   * Compute the intersection between seed plane and the VTK structured grid.
   *
   * @param[in] vfield The vector field which is embedded onto to the VTK
   * structured grid.
   */
  void intersection (const vector_field &vfield);

  /**
   * Index operator to access the triangle at a specific index;
   */
  vtkTriangle *operator[] (size_t index);

  /**
   * Iterator to traverse the surface triangulation.
   */
  class iterator;

  iterator begin ();

  iterator end ();

private:
  plane_point m_ppoint;
  plane_normal m_pnormal;
  surface_triangulation m_striangulation;

public:
  class iterator
  {
    using category = std::forward_iterator_tag;
    using value_type = vtkTriangle;
    using pointer = vtkTriangle *;
    using reference = vtkTriangle &;

  public:
    /**
     * Constructor.
     */
    explicit iterator (pointer triangle_ptr) : m_triangle{ triangle_ptr } {}

    /**
     * Dereference operator.
     */
    reference
    operator* () const
    {
      return *m_triangle;
    }

    /**
     * Arrow operator.
     */
    pointer
    operator->()
    {
      return m_triangle;
    }

    /**
     * Equality operator.
     */
    friend bool
    operator== (const iterator &itr1, const iterator &itr2)
    {
      return itr1.m_triangle == itr2.m_triangle;
    }

    /**
     * Inequality operator.
     */
    friend bool
    operator!= (const iterator &itr1, const iterator &itr2)
    {
      return itr1.m_triangle != itr2.m_triangle;
    }

    /**
     * Pre-increment operator.
     */
    iterator
    operator++ ()
    {
      ++m_triangle;
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
    pointer m_triangle;
  };
};

} // namespace biomesh

#endif