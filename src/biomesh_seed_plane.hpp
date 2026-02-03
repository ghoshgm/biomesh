
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
  using surface_triangulation = vtkNew<vtkPolyData>;

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
   *
   * @param[in] index The linear index of the triangle.
   */
  vtkCell *operator[] (size_t index);

  /**
   * Get the total triangle count in the triangulation.
   */
  size_t triangle_count () const;

private:
  plane_point m_ppoint;
  plane_normal m_pnormal;
  surface_triangulation m_striangulation;
};

} // namespace biomesh

#endif