#include "biomesh_seed_plane.hpp"

namespace biomesh
{

seed_plane::seed_plane (const plane_point &ppoint, const plane_normal &pnormal)
    : m_ppoint{ ppoint }, m_pnormal{ pnormal }
{
}

seed_plane::~seed_plane () {}

void
seed_plane::intersection (const vector_field &vfield)
{
  auto sgrid = vfield.get_grid ();

  BIOMESH_LINFO ("Plane intersection begin.");
  vtkSmartPointer<vtkPlane> plane = vtkSmartPointer<vtkPlane>::New ();
  plane->SetOrigin (std::get<0> (m_ppoint), std::get<1> (m_ppoint),
                    std::get<2> (m_ppoint));
  plane->SetNormal (std::get<0> (m_pnormal), std::get<1> (m_pnormal),
                    std::get<2> (m_pnormal));

  vtkSmartPointer<vtkCutter> cutter = vtkSmartPointer<vtkCutter>::New ();
  cutter->SetInputData (sgrid);
  cutter->SetCutFunction (plane);
  cutter->Update ();
  BIOMESH_LINFO ("Plane intersection end.");

  vtkSmartPointer<vtkPolyData> cut = vtkSmartPointer<vtkPolyData>::New ();
  cut = cutter->GetOutput ();
  BIOMESH_ASSERT ((cut->CheckAttributes () == 0));
  BIOMESH_LINFO ("Surface triangulation created successfuly.");

  BIOMESH_LINFO ("Finding triangles for seeding begin.");
  std::vector<vtkSmartPointer<vtkTriangle> > tarray;

  for (vtkIdType cid = 0; cid < cut->GetNumberOfCells (); ++cid)
    {
      vtkCell *cell = cut->GetCell (cid);

      double pCenter[3]; // world coordinates of cell center
      double pcoords[3]; // parametric center
      double weights[8]; // interpolation weights (max 8 for hex/quad, safe
                         // buffer)
      int subId = cell->GetParametricCenter (pcoords);
      cell->EvaluateLocation (subId, pcoords, pCenter, weights);

      int sid;
      double paracoords[3];
      double w[VTK_CELL_SIZE];
      auto cidx
          = sgrid->FindCell (pCenter, nullptr, -1, 0, sid, paracoords, w);

      if (vfield[cidx] == 2)
        {
          vtkSmartPointer<vtkTriangle> tri
              = vtkSmartPointer<vtkTriangle>::New ();

          for (int i = 0; i < 3; ++i)
            {
              double p[3];
              cut->GetPoint (cell->GetPointId (i), p);
              tri->GetPoints ()->SetPoint (i, p);
            }

          tarray.push_back (tri);
        }
    }

  vtkNew<vtkPoints> subset_points;
  vtkNew<vtkCellArray> subset_polys;

  for (auto &tri : tarray)
    {
      vtkIdType ptIds[3];
      for (int i = 0; i < 3; ++i)
        {
          double p[3];
          tri->GetPoints ()->GetPoint (i, p);
          ptIds[i] = subset_points->InsertNextPoint (p);
        }
      subset_polys->InsertNextCell (3, ptIds);
    }

  vtkNew<vtkPolyData> subset_mesh;
  subset_mesh->SetPoints (subset_points);
  subset_mesh->SetPolys (subset_polys);

  for (vtkIdType cell_id = 0; cell_id < subset_mesh->GetNumberOfCells ();
       ++cell_id)
    {
      vtkCell *cell = subset_mesh->GetCell (cell_id);
      BIOMESH_ASSERT ((cell != nullptr));
      BIOMESH_ASSERT ((cell->GetCellType () == VTK_TRIANGLE));

      vtkTriangle *t = vtkTriangle::SafeDownCast (cell);
      m_striangulation.push_back (t);
    }
  BIOMESH_LINFO ("Finding triangles for seeding end.");
}

vtkTriangle *
seed_plane::operator[] (size_t index)
{
  BIOMESH_ASSERT ((index >= 0));
  return (m_striangulation[index]);
}

seed_plane::iterator
seed_plane::begin ()
{
  return iterator (m_striangulation[0]);
}

seed_plane::iterator
seed_plane::end ()
{
  const size_t size = m_striangulation.size ();
  return iterator (m_striangulation[size]);
}

} // namespace biomesh
