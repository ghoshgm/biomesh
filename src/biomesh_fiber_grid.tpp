#include "biomesh_fiber_grid.hpp"

template <class fiber, class vertex>
inline fiber_grid<fiber, vertex>::fiber_grid (const std::string &file_name)
    : m_config{ file_name }
{
  m_fiber_count = 0;
}

template <class fiber, class vertex>
void
fiber_grid<fiber, vertex>::compute_seeds (const vector_field &vfield,
                                          std::vector<vertex> &seed_points)
{
  auto sgrid = vfield.get_grid ();
  m_config.read_config_file ();

  BIOMESH_LINFO ("Compute seed points begin.");
  vtkSmartPointer<vtkPlane> plane = vtkSmartPointer<vtkPlane>::New ();
  auto p = m_config.get_value<std::tuple<double, double, double> > (
      "plane_point");
  auto n = m_config.get_value<std::tuple<double, double, double> > (
      "plane_normal");
  plane->SetOrigin (std::get<0> (p), std::get<1> (p), std::get<2> (p));
  plane->SetNormal (std::get<0> (n), std::get<1> (n), std::get<2> (n));

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

  vtkIdType numCells = cut->GetNumberOfCells ();

  std::cout << cut->GetNumberOfCells () << std::endl;

  std::vector<vtkSmartPointer<vtkTriangle> > triangleArray;

  for (vtkIdType cellId = 0; cellId < numCells; ++cellId)
    {
      vtkCell *cell = cut->GetCell (cellId);

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
          vtkSmartPointer<vtkTriangle> tri
              = vtkSmartPointer<vtkTriangle>::New ();

          for (int i = 0; i < 3; ++i)
            {
              double p[3];
              cut->GetPoint (cell->GetPointId (i), p);
              tri->GetPoints ()->SetPoint (i, p);
            }

          triangleArray.push_back (tri);
        }
    }

  vtkNew<vtkPoints> subsetPoints;
  vtkNew<vtkCellArray> subsetPolys;

  for (auto &tri : triangleArray)
    {
      vtkIdType ptIds[3];
      for (int i = 0; i < 3; ++i)
        {
          double p[3];
          tri->GetPoints ()->GetPoint (i, p);
          ptIds[i] = subsetPoints->InsertNextPoint (p);
        }
      subsetPolys->InsertNextCell (3, ptIds);
    }

  vtkNew<vtkPolyData> subsetMesh;
  subsetMesh->SetPoints (subsetPoints);
  subsetMesh->SetPolys (subsetPolys);

  std::cout << subsetMesh->GetNumberOfCells () << std::endl;

  std::string sm_path
      = std::string (BIOMESH_BUILD_DIR) + "/results/" + "subset.vtk";
  vtkSmartPointer<vtkPolyDataWriter> wr
      = vtkSmartPointer<vtkPolyDataWriter>::New ();
  wr->SetFileName (sm_path.c_str ());
  wr->SetInputData (subsetMesh);
  wr->Write ();

#if 1
  std::vector<double> cumulativeAreas (subsetMesh->GetNumberOfCells ());
  double totalArea = 0.0;

  for (vtkIdType cellId = 0; cellId < subsetMesh->GetNumberOfCells ();
       ++cellId)
    {
      vtkCell *cell = subsetMesh->GetCell (cellId);

      // Ensure it is a triangle
      if (cell->GetCellType () != VTK_TRIANGLE)
        {
          cumulativeAreas[cellId] = totalArea;
          continue;
        }

      double p0[3], p1[3], p2[3];
      cell->GetPoints ()->GetPoint (0, p0);
      cell->GetPoints ()->GetPoint (1, p1);
      cell->GetPoints ()->GetPoint (2, p2);

      double area = vtkTriangle::TriangleArea (p0, p1, p2);
      totalArea += area;

      cumulativeAreas[cellId] = totalArea;
    }
#endif

  int N = 100;

  vtkNew<vtkPoints> sampledPoints;
  sampledPoints->SetNumberOfPoints (N);

  vtkNew<vtkMinimalStandardRandomSequence> rng;
  rng->SetSeed (1);

  for (vtkIdType i = 0; i < N; ++i)
    {
      rng->Next ();
      double r = rng->GetValue () * totalArea;

      vtkIdType triId = std::lower_bound (cumulativeAreas.begin (),
                                          cumulativeAreas.end (), r)
                        - cumulativeAreas.begin ();

      vtkCell *cell = subsetMesh->GetCell (triId);

      double p0[3], p1[3], p2[3];
      cell->GetPoints ()->GetPoint (0, p0);
      cell->GetPoints ()->GetPoint (1, p1);
      cell->GetPoints ()->GetPoint (2, p2);

      rng->Next ();
      double u = rng->GetValue ();
      rng->Next ();
      double v = rng->GetValue ();

      if (u + v > 1.0)
        {
          u = 1.0 - u;
          v = 1.0 - v;
        }

      double w = 1.0 - u - v;

      double x[3] = { w * p0[0] + u * p1[0] + v * p2[0],
                      w * p0[1] + u * p1[1] + v * p2[1],
                      w * p0[2] + u * p1[2] + v * p2[2] };

      vertex seed (x[0], x[1], x[2]);
      seed_points.push_back (seed);

      sampledPoints->SetPoint (i, x);
    }

  vtkNew<vtkPolyData> output;
  output->SetPoints (sampledPoints);

  std::cout << output->GetNumberOfPoints () << std::endl;

  std::string s_path
      = std::string (BIOMESH_BUILD_DIR) + "/results/" + "sampled_points.vtk";
  vtkNew<vtkPolyDataWriter> w;
  w->SetFileName (s_path.c_str ());
  w->SetInputData (output);
  w->Write ();

#if 0
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
          seed_points.push_back (seed);
        }

    }
#endif

  BIOMESH_LINFO ("Compute seed points end.");
}

template <class fiber, class vertex>
inline int
fiber_grid<fiber, vertex>::generate_fiber_grid (const vector_field &vfield)
{
  /**
   * Compute the seed points for the fibers.
   */
  std::vector<vertex> seeds;
  compute_seeds (vfield, seeds);

  int fiber_index = 0;

  size_t fpoint_count = (size_t)m_config.get_value<int> ("vertex_count");
  double width = m_config.get_value<double> ("vertex_width");

  for (const vertex &seed : seeds)
    {
      /* Initialize the fiber. */
      fiber f (seed, fpoint_count, width);

      /* Generate fiber in forward direction. */
      BIOMESH_LINFO ("Fiber" + std::to_string (fiber_index)
                     + " in forward direction begin.");
      f.generate_fiber (vfield, 1, m_config);
      BIOMESH_LINFO ("Fiber" + std::to_string (fiber_index)
                     + " in forward direction end.");
      f.reverse ();
      BIOMESH_LINFO ("Fiber" + std::to_string (fiber_index)
                     + " in reverse direction begin.");
      f.generate_fiber (vfield, 0, m_config);
      BIOMESH_LINFO ("Fiber" + std::to_string (fiber_index)
                     + " in reverse direction end.");

      /* Push fiber to fiber grid. */
      m_fiber_set.emplace_back (f);

      ++fiber_index;
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