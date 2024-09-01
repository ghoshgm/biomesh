
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
#include <vtkDataArray.h>

#include <string>
#include <vector>

namespace biomesh
{
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

private:
  size_t m_fiber_count;
  json_parser m_jparser;
  std::vector<fiber> m_fiber_set;
};

#include "biomesh_fiber_grid.tpp"

} // namespace biomesh
#endif