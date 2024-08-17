
#ifndef BIOMESH_FIBER_GRID2D_HPP
#define BIOMESH_FIBER_GRID2D_HPP

#include <biomesh_fiber_grid_base.hpp>

namespace biomesh
{
/**
 * @brief Derived class for 2D fiber grid.
 * This class is the collections of 2D fibers in
 * a muscle geometry.
 */
class fiber_grid2D : protected fiber_grid
{
public:
  /**
   * Default constructor.
   *
   * @param[in] file_name The path to the JSON file which holds the seed
   * coordinates of the fiber.
   */
  fiber_grid2D (const std::string &file_name);

  /**
   * Function to generate all fibers from the JSON file.
   *
   * @param[in] vfield The vector field which will be used to interpolate grid
   * point in a fiber.
   * @param[in] fpoint_count The number of grid points on a single grid.
   */
  int generate_fiber_grid (const vector_field &vfield, size_t fpoint_count);

private:
  json_parser m_jparser;
  std::vector<fiber2D> m_fiber_set; /* Set of 1D fiber grids. */
};
} // namespace biomesh

#endif