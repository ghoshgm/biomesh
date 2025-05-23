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

#if 1
  std::vector<double> z_coords;
  for (size_t fcount = 0; fcount < this->m_fiber_count; ++fcount)
    {
      auto f = m_fiber_set[fcount];
      for (size_t ii = 0; ii < f.size (); ++ii)
        {
          auto v = f[ii];
          z_coords.push_back (v ('z'));
        }
    }

  double max = *(std::max_element (z_coords.begin (), z_coords.end ()));
  std::cout << "##########################" << max << std::endl;

  for (size_t fcount = 0; fcount < this->m_fiber_count; ++fcount)
    {
      auto f = m_fiber_set[fcount];
      for (size_t ii = 0; ii < f.size (); ++ii)
        {
          auto v = f[ii];
          if (BIOMESH_DCOMP (max, v ('z')))
            {
              (m_fiber_set[fcount]).pop ();
            }
        }
      std::cout << "------------------" << (m_fiber_set[fcount]).size ()
                << std::endl;
    }
#endif

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
void
biomesh::fiber_grid<fiber, vertex>::reverse ()
{
  for (auto &f : m_fiber_set)
    {
      f.reverse ();
    }
}

template <class fiber, class vertex>
void
biomesh::fiber_grid<fiber, vertex>::translate (double val)
{
#if 1
  for (size_t ii = 0; ii < m_fiber_set.size (); ++ii)
    {
      // auto f = m_fiber_set[ii];
      // f.translate(val);
      m_fiber_set[ii].translate (val);
    }
#endif
}

template <class fiber, class vertex>
void
biomesh::fiber_grid<fiber, vertex>::reflection (int dir)
{
  for (size_t ii = 0; ii < m_fiber_set.size (); ++ii)
    {
      m_fiber_set[ii].reflection (dir);
    }
}

template <class fiber, class vertex>
void
biomesh::fiber_grid<fiber, vertex>::print_vertices () const
{
  for (size_t ii = 0; ii < m_fiber_set.size (); ++ii)
    {
      std::cout << "---------------" << std::endl;
      auto f = m_fiber_set[ii];
      f.print_vertices ();
    }
}