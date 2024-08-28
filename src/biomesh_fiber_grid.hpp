
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
template <class fiber, class vertex> class fgrid
{
public:
  /**
   * Default constructor.
   *
   * @param[in] file_name The path to the JSON file which holds the seed
   * coordinates of the fiber.
   */
  fgrid (const std::string &file_name);

  /**
   * Function to generate all fibers from the JSON file.
   *
   * @param[in] vfield The vector field which will be used to interpolate grid
   * point in a fiber.
   * @param[in] fpoint_count The number of grid points on a single grid.
   */
  int generate_fiber_grid (const vector_field &vfield, size_t fpoint_count);

  /**
   * Return the fiber at the specified index.
   *
   * @param[in] idx The index at which fiber needs to retrieved.
   */
  fiber operator[] (int idx) const;

  /**
   * Return the fiber count.
   */
  size_t size () const;

private:
  size_t m_fiber_count;
  json_parser m_jparser;
  std::vector<fiber> m_fiber_set;
};

template <class fiber, class vertex>
inline fgrid<fiber, vertex>::fgrid (const std::string &file_name)
    : m_jparser{ file_name }
{
  m_fiber_count = 0;
}

template <class fiber, class vertex>
inline int
fgrid<fiber, vertex>::generate_fiber_grid (const vector_field &vfield,
                                           size_t fpoint_count)
{
  int ret = m_jparser.read ();
  BIOMESH_ASSERT (ret == true);
  auto data = m_jparser.get_json_string ();
  m_fiber_count = data["seed_points"].size ();
  BIOMESH_ASSERT (this->m_fiber_count > 0);

  /* Loop over the fibers. */
  for (size_t fcount = 0; fcount < this->m_fiber_count; ++fcount)
    {
      /* Obtain the seed point. */
      double x = (data["seed_points"][(unsigned)fcount]["x"]).asDouble ();
      double y = (data["seed_points"][(unsigned)fcount]["y"]).asDouble ();
      vertex seed (x, y);

      /* Initialize the fiber. */
      fiber f (seed, fpoint_count);

      /* Generate fiber. */
      f.generate_fiber (vfield);

      /* Push fiber to fiber grid. */
      m_fiber_set.emplace_back (f);
    }

  /** TODO: Add check for testing validity of the fiber grid.
   * Return BIOMESH_SUCCESS iff the fiber grid is valid.
   */
  return BIOMESH_SUCCESS;
}

template <class fiber, class vertex>
inline fiber
fgrid<fiber, vertex>::operator[] (int idx) const
{
  return m_fiber_set[idx];
}

template <class fiber, class vertex>
inline size_t
fgrid<fiber, vertex>::size () const
{
  return m_fiber_set.size ();
}
} // namespace biomesh
#endif