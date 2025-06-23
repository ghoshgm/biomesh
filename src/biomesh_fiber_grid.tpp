#include "biomesh_fiber_grid.hpp"

template <class fiber, class vertex>
inline fiber_grid<fiber, vertex>::fiber_grid (const std::string &file_name)
    : m_jparser{ file_name }
{
  m_fiber_count = 0;
}

template <class fiber, class vertex>
inline int
fiber_grid<fiber, vertex>::generate_fiber_grid (const vector_field &vfield,
                                                size_t fpoint_count,
                                                double width)
{
  int ret = m_jparser.read ();
  BIOMESH_ASSERT ((ret == true));
  auto data = m_jparser.get_json_string ();
  m_fiber_count = data["seed_points"].size ();
  BIOMESH_ASSERT ((this->m_fiber_count > 0));
  BIOMESH_ASSERT ((width > 0.0));
  m_fiber_set.reserve ((this->m_fiber_count));

  /* Loop over the fibers. */
  for (size_t fcount = 0; fcount < this->m_fiber_count; ++fcount)
    {
      /* Obtain the seed point. */
      double x = (data["seed_points"][(unsigned)fcount]["x"]).asDouble ();
      double y = (data["seed_points"][(unsigned)fcount]["y"]).asDouble ();
      double z = (data["seed_points"][(unsigned)fcount]["z"]).asDouble ();
      vertex seed (x, y, z);

      /* Initialize the fiber. */
      fiber f (seed, fpoint_count, width);

      /* Generate fiber. */
      BIOMESH_LINFO ("Fiber" + std::to_string (fcount) + " begin.");
      f.generate_fiber (vfield);
      BIOMESH_LINFO ("Fiber" + std::to_string (fcount) + " end.");

      /* Push fiber to fiber grid. */
      m_fiber_set.emplace_back (f);
    }

  return BIOMESH_SUCCESS;
}

template <class fiber, class vertex>
inline fiber
fiber_grid<fiber, vertex>::operator[] (int idx) const
{
  return m_fiber_set[idx];
}

template <class fiber, class vertex>
inline size_t
fiber_grid<fiber, vertex>::size () const
{
  return m_fiber_set.size ();
}

template <class fiber, class vertex>
template <typename... Args>
void
biomesh::fiber_grid<fiber, vertex>::transformation (
    std::function<void (std::vector<fiber> &, Args...)> transform_function,
    Args... args)
{
  transform_function (this->m_fiber_set, args...);
}

namespace affine_transform
{

template <class fiber>
void
translation (std::vector<fiber> &fiber_set, double x, double y, double z)
{
  for (fiber &f : fiber_set)
    {
      for (size_t ii = 0; ii < f.size (); ++ii)
        {
          double xx = f[ii]('x') + x;
          double yy = f[ii]('y') + y;
          double zz = f[ii]('z') + z;
          f.update_vertex (ii, xx, yy, zz);
        }
    }
}

template <class fiber>
void
reflection (std::vector<fiber> &fiber_set, int dir)
{
  for (fiber &f : fiber_set)
    {
      for (size_t ii = 0; ii < f.size (); ++ii)
        {
          double xx = f[ii]('x');
          double yy = f[ii]('y');
          double zz = f[ii]('z');

          if (dir == 0)
            {
              xx *= -1.0;
            }
          else if (dir == 1)
            {
              yy *= -1.0;
            }
          else if (dir == 2)
            {
              zz *= -1.0;
            }

          f.update_vertex (ii, xx, yy, zz);
        }
    }
}

}