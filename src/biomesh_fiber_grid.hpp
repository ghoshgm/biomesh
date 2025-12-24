
#ifndef BIOMESH_FIBER_GRID_HPP
#define BIOMESH_FIBER_GRID_HPP

#include <biomesh_fiber2d.hpp>
#include <biomesh_fiber3d.hpp>
#include <biomesh_interpolation.hpp>
#include <biomesh_json_parser.hpp>
#include <biomesh_vector_field.hpp>
#include <biomesh_vertex2d.hpp>
#include <biomesh_vertex3d.hpp>

#include <vtkCell.h>
#include <vtkCellData.h>
#include <vtkCutter.h>
#include <vtkDataArray.h>
#include <vtkExtractGeometry.h>
#include <vtkPlane.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataWriter.h>
#include <vtkSmartPointer.h>
#include <vtkStructuredGrid.h>
#include <vtkStructuredGridWriter.h>
#include <vtkUnstructuredGrid.h>

#include <string>
#include <vector>

namespace biomesh
{
/**
 * @brief Class for modelling the set of fibers.
 *
 * The set of all fibers constitutes a fiber grid.
 */
template <class fiber, class vertex> class fiber_grid
{
public:
  /**
   * Default constructor.
   *
   * @param[in] file_name The path to the JSON file which holds the seed
   * coordinates of the fiber.
   */
  fiber_grid (const std::string &file_name);

  /**
   * Function to generate all fibers from the JSON file.
   *
   * @param[in] vfield The vector field which will be used to interpolate grid
   * point in a fiber.
   * @param[in] fpoint_count The number of grid points on a single grid.
   *
   * @return Success if the fiber grid is valid otherwise Error is returned.
   */
  int generate_fiber_grid (const vector_field &vfield, size_t fpoint_count,
                           double width);

  /**
   * Return the fiber at the specified index.
   *
   * @param[in] idx The index at which fiber needs to retrieved.
   *
   * @return The fiber at index 'idx'.
   */
  fiber operator[] (int idx) const;

  /**
   * Return the fiber count.
   *
   * @return The fiber count in the fiber grid.
   */
  size_t size () const;

  /**
   * Apply geometric transformations to the fiber vertices.
   *
   * @param[in] transform_function The function call-back to apply appropriate
   * transformation function.
   */
  template <typename... Args>
  void transformation (
      std::function<void (std::vector<fiber> &, Args...)> transform_function,
      Args... args);

private:
  size_t m_fiber_count;
  json_parser m_jparser;
  std::vector<fiber> m_fiber_set;
};

#include "biomesh_fiber_grid.tpp"

/**
 * Affine transformation functions.
 */
namespace affine_transform
{

/**
 * Translate the fiber grid by a specified displacement.
 *
 * @param[in] x Displacement in the x-direction.
 * @param[in] y Displacement in the y-direction.
 * @param[in] z Displacement in the z-direction.
 */
template <class fiber>
void translation (std::vector<fiber> &fiber_set, double x, double y, double z);

/**
 * Reflect the fiber grid about an axis.
 *
 * 0 -> x-axis.
 * 1 -> y-axis.
 * 2 -> z-axis.
 *
 * @param[in] dir Specify the required axis.
 */
template <class fiber>
void reflection (std::vector<fiber> &fiber_set, int dir);

}

} // namespace biomesh
#endif