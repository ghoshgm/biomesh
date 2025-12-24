#include "biomesh_fiber_grid.hpp"

template <class fiber, class vertex>
inline fiber_grid<fiber, vertex>::fiber_grid (const std::string &file_name)
    : m_jparser{ file_name }
{
  m_fiber_count = 0;
}

template <class vertex>
static std::vector<vertex>
compute_seeds (const vector_field &vfield)
{
  /* Obtain the seed cell index. */
  auto sgrid = vfield.get_grid ();
  std::vector<int> v = vfield.get_seed_indices ();
  std::vector<vertex> sp;

  BIOMESH_LINFO ("Compute seed points begin.");
  for (int ii = 0; ii < v.size (); ++ii)
    {
      if (v[ii] == 3)
        {
          vtkCell *cell = sgrid->GetCell (ii);

          double pcenter[3]; // to hold the parametric center
          double xcenter[3]; // to hold the physical center
          double
              weights[8]; // size depends on the maximum number of cell points
          int subId;
          cell->GetParametricCenter (pcenter);
          cell->EvaluateLocation (subId, pcenter, xcenter, weights);
          vertex seed_point (xcenter[0], xcenter[1], xcenter[2]);

          sp.push_back (seed_point);
        }
    }
  BIOMESH_LINFO ("Compute seed points end.");

  return sp;
}

template <class fiber, class vertex>
inline int
fiber_grid<fiber, vertex>::generate_fiber_grid (const vector_field &vfield,
                                                size_t fpoint_count,
                                                double width)
{
#if 0
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
#else

#if 0
  std::vector<vertex> v = compute_seeds<vertex> (vfield);

  int counter = 0;
  for (const vertex &seed : v)
    {
      fiber f (seed, fpoint_count, width);

      /* Generate fiber. */
      BIOMESH_LINFO ("Fiber" + std::to_string (counter) + " begin.");
      f.generate_fiber (vfield);
      BIOMESH_LINFO ("Fiber" + std::to_string (counter) + " end.");

      /* Push fiber to fiber grid. */
      m_fiber_set.emplace_back (f);
      ++counter;
    }
#endif
  auto sgrid = vfield.get_grid ();

  vtkSmartPointer<vtkPlane> plane = vtkSmartPointer<vtkPlane>::New ();
  plane->SetOrigin (sgrid->GetCenter ());
  plane->SetNormal (0.0, 0.0, 1.0);

  vtkSmartPointer<vtkCutter> cutter = vtkSmartPointer<vtkCutter>::New ();
  cutter->SetInputData (sgrid);
  cutter->SetCutFunction (plane);
  cutter->Update ();

  vtkSmartPointer<vtkPolyData> cut = vtkSmartPointer<vtkPolyData>::New ();
  cut = cutter->GetOutput ();

  std::string file_path
      = std::string (BIOMESH_BUILD_DIR) + "/results/" + "cut_surface.vtk";
  vtkSmartPointer<vtkPolyDataWriter> writer
      = vtkSmartPointer<vtkPolyDataWriter>::New ();
  writer->SetFileName (file_path.c_str ());
  writer->SetInputData (cut);
  writer->Write ();

  int counter = 0;

  for (int ii = 0; ii < cut->GetNumberOfCells (); ++ii)
    {
      vtkCell *cell = cut->GetCell (ii);

      double pCenter[3]; // world coordinates of cell center
      double pcoords[3]; // parametric center
      double weights[8]; // interpolation weights (max 8 for hex/quad, safe
                         // buffer)
      int subId = cell->GetParametricCenter (pcoords);
      cell->EvaluateLocation (subId, pcoords, pCenter, weights);

      int sid;
      double paracoords[3];
      double w[VTK_CELL_SIZE];
      auto cid = sgrid->FindCell (pCenter, nullptr, -1, 0, sid, paracoords, w);

      if (vfield[cid] == 2)
        {
          vertex seed (pCenter[0], pCenter[1], pCenter[2]);

          /* Initialize the fiber. */
          fiber f (seed, fpoint_count, width);

          /* Generate fiber. */
          BIOMESH_LINFO ("Fiber" + std::to_string (counter) + " begin.");
          f.generate_fiber (vfield);
          // f.generate_fiber_reverse (vfield);
          BIOMESH_LINFO ("Fiber" + std::to_string (counter) + " end.");

          /* Push fiber to fiber grid. */
          m_fiber_set.emplace_back (f);

          ++counter;
        }
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