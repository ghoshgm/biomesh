#include "biomesh_seed_plane.hpp"

#include <vtkPolyDataWriter.h>

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
  BIOMESH_LINFO ("Triangle count = "
                 + std::to_string (cut->GetNumberOfCells ()));

#ifdef BIOMESH_ENABLE_DEBUG
  std::string file_path
      = std::string (BIOMESH_BUILD_DIR) + "/results/" + "seed_plane.vtk";
  vtkSmartPointer<vtkPolyDataWriter> writer
      = vtkSmartPointer<vtkPolyDataWriter>::New ();
  writer->SetFileName (file_path.c_str ());
  writer->SetInputData (cut);
  writer->Write ();
#endif

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

      if (cidx < 0)
        {
          continue;
        }

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

  m_striangulation->SetPoints (subset_points);
  m_striangulation->SetPolys (subset_polys);

  BIOMESH_LINFO ("Finding triangles for seeding end.");
  BIOMESH_LINFO ("Triangle count = "
                 + std::to_string (m_striangulation->GetNumberOfCells ()));
}

vtkCell *
seed_plane::operator[] (size_t index)
{
  BIOMESH_ASSERT ((index >= 0)
                  and (index < m_striangulation->GetNumberOfCells ()));
  return m_striangulation->GetCell (index);
}

size_t
seed_plane::triangle_count () const
{
  return m_striangulation->GetNumberOfCells ();
}

} // namespace biomesh
