
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
  BIOMESH_ASSERT (ret == true);
  auto data = m_jparser.get_json_string ();
  m_fiber_count = data["seed_points"].size ();
  BIOMESH_ASSERT (this->m_fiber_count > 0);
  BIOMESH_ASSERT (width > 0.0);
  m_fiber_set.reserve(this->m_fiber_count);

  /* Loop over the fibers. */
  for (size_t fcount = 0; fcount < this->m_fiber_count; ++fcount)
    {
      /* Obtain the seed point. */
      double x = (data["seed_points"][(unsigned)fcount]["x"]).asDouble ();
      double y = (data["seed_points"][(unsigned)fcount]["y"]).asDouble ();
      vertex seed (x, y);

      /* Initialize the fiber. */
      fiber f (seed, fpoint_count, width);

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