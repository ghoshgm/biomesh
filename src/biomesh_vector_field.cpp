
#include <biomesh_vector_field.hpp>

#include <biomesh_visualization.hpp>

#include <vtkDataArray.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkSmartPointer.h>
#include <vtkStructuredGrid.h>
#include <vtkStructuredGridReader.h>
#include <vtkStructuredGridWriter.h>

namespace biomesh
{
vector_field::vector_field (const std::string &file_path,
                            const std::string &vfield_tag)
    : m_vfield_tag{ vfield_tag }, m_file_path{ file_path }, m_sgrid{
        vtkSmartPointer<vtkStructuredGrid>::New ()
      }
{
}

vector_field::vector_field (const vector_field &other)
{
  this->m_file_path = other.m_file_path;
  this->m_sgrid->DeepCopy (other.m_sgrid);
}

vector_field::vector_field (vector_field &&other)
{
  this->m_file_path = other.m_file_path;
  other.m_file_path.clear ();
  this->m_sgrid->ShallowCopy (other.m_sgrid);
}

vector_field::~vector_field () {}

int
vector_field::load_vtk_grid ()
{
  BIOMESH_ASSERT (!m_file_path.empty ());
  BIOMESH_LINFO ("File: " + m_file_path);

  /* Initialize serial reader. */
  vtkSmartPointer<vtkStructuredGridReader> reader
      = vtkSmartPointer<vtkStructuredGridReader>::New ();
  BIOMESH_ASSERT (reader != nullptr);

  /* Read the file. */
  BIOMESH_LINFO ("Read vtk file start.");
  reader->SetFileName (this->m_file_path.c_str ());
  reader->Update ();
  BIOMESH_ASSERT (reader->IsFileValid ("structured"));
  BIOMESH_LINFO ("Read vtk file finish.");

  /* Obtain the structured grid data. */
  m_sgrid = reader->GetOutput ();
  BIOMESH_ASSERT (this->m_sgrid != nullptr);
#ifdef BIOMESH_ENABLE_DEBUG
  m_sgrid->Print (std::cout);
#endif

  return (m_sgrid != nullptr) ? BIOMESH_SUCCESS : BIOMESH_ERROR;
}

vtkSmartPointer<vtkStructuredGrid>
addBothXLayers (vtkStructuredGrid *sgrid, int numLayers,
                const std::string &vectorName)
{
  int dims[3];
  sgrid->GetDimensions (dims);
  int nx = dims[0], ny = dims[1], nz = dims[2];

  vtkDataArray *origVectors
      = sgrid->GetPointData ()->GetArray (vectorName.c_str ());
  if (!origVectors)
    throw std::runtime_error ("Vector field '" + vectorName
                              + "' not found in the input grid.");
  int numComponents = origVectors->GetNumberOfComponents ();
  std::vector<double> defaultVector (numComponents, 0.0);

  int new_nx = nx + 2 * numLayers;
  int newDims[3] = { new_nx, ny, nz };

  vtkSmartPointer<vtkPoints> newPoints = vtkSmartPointer<vtkPoints>::New ();
  vtkSmartPointer<vtkDoubleArray> newVectors
      = vtkSmartPointer<vtkDoubleArray>::New ();
  newVectors->SetName (vectorName.c_str ());
  newVectors->SetNumberOfComponents (numComponents);

  for (int k = 0; k < nz; k++)
    {
      for (int j = 0; j < ny; j++)
        {
          std::vector<std::array<double, 3> > rowPoints;
          std::vector<std::vector<double> > rowVectors;
          for (int i = 0; i < nx; i++)
            {
              int idx = i + j * nx + k * nx * ny;
              double pt[3];
              sgrid->GetPoint (idx, pt);
              rowPoints.push_back ({ pt[0], pt[1], pt[2] });
              std::vector<double> vec (numComponents, 0.0);
              origVectors->GetTuple (idx, vec.data ());
              rowVectors.push_back (vec);
            }
          if (rowPoints.size () < 2)
            throw std::runtime_error (
                "Not enough points in row for x extension.");

          std::array<double, 3> p0 = rowPoints[0];
          std::array<double, 3> p1 = rowPoints[1];
          std::array<double, 3> negOffset;
          for (int d = 0; d < 3; d++)
            negOffset[d] = p1[d] - p0[d];
          std::vector<std::array<double, 3> > negPoints;
          for (int layer = numLayers; layer >= 1; layer--)
            {
              std::array<double, 3> newPt;
              for (int d = 0; d < 3; d++)
                newPt[d] = p0[d] - layer * negOffset[d];
              negPoints.push_back (newPt);
            }

          std::array<double, 3> pLast = rowPoints[nx - 1];
          std::array<double, 3> pSecondLast = rowPoints[nx - 2];
          std::array<double, 3> posOffset;
          for (int d = 0; d < 3; d++)
            posOffset[d] = pLast[d] - pSecondLast[d];
          std::vector<std::array<double, 3> > posPoints;
          for (int layer = 1; layer <= numLayers; layer++)
            {
              std::array<double, 3> newPt;
              for (int d = 0; d < 3; d++)
                newPt[d] = pLast[d] + layer * posOffset[d];
              posPoints.push_back (newPt);
            }

          std::vector<std::array<double, 3> > fullRowPoints;
          fullRowPoints.insert (fullRowPoints.end (), negPoints.begin (),
                                negPoints.end ());
          fullRowPoints.insert (fullRowPoints.end (), rowPoints.begin (),
                                rowPoints.end ());
          fullRowPoints.insert (fullRowPoints.end (), posPoints.begin (),
                                posPoints.end ());

          std::vector<std::vector<double> > fullRowVectors;
          for (int i = 0; i < numLayers; i++)
            fullRowVectors.push_back (defaultVector);
          fullRowVectors.insert (fullRowVectors.end (), rowVectors.begin (),
                                 rowVectors.end ());
          for (int i = 0; i < numLayers; i++)
            fullRowVectors.push_back (defaultVector);

          for (size_t i = 0; i < fullRowPoints.size (); i++)
            {
              newPoints->InsertNextPoint (fullRowPoints[i].data ());
              newVectors->InsertNextTuple (fullRowVectors[i].data ());
            }
        }
    }

  vtkSmartPointer<vtkStructuredGrid> newSGrid
      = vtkSmartPointer<vtkStructuredGrid>::New ();
  newSGrid->SetDimensions (newDims);
  newSGrid->SetPoints (newPoints);
  newSGrid->GetPointData ()->AddArray (newVectors);
  return newSGrid;
}

vtkSmartPointer<vtkStructuredGrid>
addBothYLayers (vtkStructuredGrid *sgrid, int numLayers,
                const std::string &vectorName)
{
  int dims[3];
  sgrid->GetDimensions (dims);
  int nx = dims[0], ny = dims[1], nz = dims[2];

  vtkDataArray *origVectors
      = sgrid->GetPointData ()->GetArray (vectorName.c_str ());
  if (!origVectors)
    throw std::runtime_error ("Vector field '" + vectorName
                              + "' not found in the grid.");
  int numComponents = origVectors->GetNumberOfComponents ();
  std::vector<double> defaultVector (numComponents, 0.0);

  int new_ny = ny + 2 * numLayers;
  int newDims[3] = { nx, new_ny, nz };

  // For each fixed (i,k) pair, build an extended column along y.
  std::vector<std::pair<std::vector<std::array<double, 3> >,
                        std::vector<std::vector<double> > > >
      columns (nx * nz);
  for (int k = 0; k < nz; k++)
    {
      for (int i = 0; i < nx; i++)
        {
          std::vector<std::array<double, 3> > colPoints;
          std::vector<std::vector<double> > colVectors;
          for (int j = 0; j < ny; j++)
            {
              int idx = i + j * nx + k * nx * ny;
              double pt[3];
              sgrid->GetPoint (idx, pt);
              colPoints.push_back ({ pt[0], pt[1], pt[2] });
              std::vector<double> vec (numComponents, 0.0);
              origVectors->GetTuple (idx, vec.data ());
              colVectors.push_back (vec);
            }
          if (colPoints.size () < 2)
            throw std::runtime_error (
                "Not enough points in column for y extension.");
          std::array<double, 3> p0 = colPoints[0];
          std::array<double, 3> p1 = colPoints[1];
          std::array<double, 3> negOffset;
          for (int d = 0; d < 3; d++)
            negOffset[d] = p1[d] - p0[d];
          std::vector<std::array<double, 3> > negPoints;
          for (int layer = numLayers; layer >= 1; layer--)
            {
              std::array<double, 3> newPt;
              for (int d = 0; d < 3; d++)
                newPt[d] = p0[d] - layer * negOffset[d];
              negPoints.push_back (newPt);
            }
          std::array<double, 3> pLast = colPoints[ny - 1];
          std::array<double, 3> pSecondLast = colPoints[ny - 2];
          std::array<double, 3> posOffset;
          for (int d = 0; d < 3; d++)
            posOffset[d] = pLast[d] - pSecondLast[d];
          std::vector<std::array<double, 3> > posPoints;
          for (int layer = 1; layer <= numLayers; layer++)
            {
              std::array<double, 3> newPt;
              for (int d = 0; d < 3; d++)
                newPt[d] = pLast[d] + layer * posOffset[d];
              posPoints.push_back (newPt);
            }
          std::vector<std::array<double, 3> > fullColPoints;
          fullColPoints.insert (fullColPoints.end (), negPoints.begin (),
                                negPoints.end ());
          fullColPoints.insert (fullColPoints.end (), colPoints.begin (),
                                colPoints.end ());
          fullColPoints.insert (fullColPoints.end (), posPoints.begin (),
                                posPoints.end ());

          std::vector<std::vector<double> > fullColVectors;
          for (int j = 0; j < numLayers; j++)
            fullColVectors.push_back (defaultVector);
          fullColVectors.insert (fullColVectors.end (), colVectors.begin (),
                                 colVectors.end ());
          for (int j = 0; j < numLayers; j++)
            fullColVectors.push_back (defaultVector);

          columns[i + k * nx] = std::make_pair (fullColPoints, fullColVectors);
        }
    }

  vtkSmartPointer<vtkPoints> newPoints = vtkSmartPointer<vtkPoints>::New ();
  vtkSmartPointer<vtkDoubleArray> newVectors
      = vtkSmartPointer<vtkDoubleArray>::New ();
  newVectors->SetName (vectorName.c_str ());
  newVectors->SetNumberOfComponents (numComponents);

  // New grid ordering: i (x) fastest, then j (y), then k (z).
  for (int k = 0; k < nz; k++)
    {
      for (int j = 0; j < new_ny; j++)
        {
          for (int i = 0; i < nx; i++)
            {
              const auto &colPoints = columns[i + k * nx].first;
              const auto &colVecs = columns[i + k * nx].second;
              newPoints->InsertNextPoint (colPoints[j].data ());
              newVectors->InsertNextTuple (colVecs[j].data ());
            }
        }
    }

  vtkSmartPointer<vtkStructuredGrid> newSGrid
      = vtkSmartPointer<vtkStructuredGrid>::New ();
  newSGrid->SetDimensions (newDims);
  newSGrid->SetPoints (newPoints);
  newSGrid->GetPointData ()->AddArray (newVectors);
  return newSGrid;
}

vtkSmartPointer<vtkStructuredGrid>
addBothZLayers (vtkStructuredGrid *sgrid, int numLayers,
                const std::string &vectorName)
{
  int dims[3];
  sgrid->GetDimensions (dims);
  int nx = dims[0], ny = dims[1], nz = dims[2];

  vtkDataArray *origVectors
      = sgrid->GetPointData ()->GetArray (vectorName.c_str ());
  if (!origVectors)
    throw std::runtime_error ("Vector field '" + vectorName
                              + "' not found in the grid.");
  int numComponents = origVectors->GetNumberOfComponents ();
  std::vector<double> defaultVector (numComponents, 0.0);

  int new_nz = nz + 2 * numLayers;
  int newDims[3] = { nx, ny, new_nz };

  // For each fixed (i,j) pair, build an extended column along z.
  // We store the extended column (points and vectors) in a container indexed
  // by (i + j*nx).
  std::vector<std::pair<std::vector<std::array<double, 3> >,
                        std::vector<std::vector<double> > > >
      columns (nx * ny);
  for (int j = 0; j < ny; j++)
    {
      for (int i = 0; i < nx; i++)
        {
          std::vector<std::array<double, 3> > colPoints;
          std::vector<std::vector<double> > colVectors;
          for (int k = 0; k < nz; k++)
            {
              int idx = i + j * nx + k * nx * ny;
              double pt[3];
              sgrid->GetPoint (idx, pt);
              colPoints.push_back ({ pt[0], pt[1], pt[2] });
              std::vector<double> vec (numComponents, 0.0);
              origVectors->GetTuple (idx, vec.data ());
              colVectors.push_back (vec);
            }
          if (colPoints.size () < 2)
            throw std::runtime_error (
                "Not enough points in column for z extension.");
          std::array<double, 3> p0 = colPoints[0];
          std::array<double, 3> p1 = colPoints[1];
          std::array<double, 3> negOffset;
          for (int d = 0; d < 3; d++)
            negOffset[d] = p1[d] - p0[d];
          std::vector<std::array<double, 3> > negPoints;
          for (int layer = numLayers; layer >= 1; layer--)
            {
              std::array<double, 3> newPt;
              for (int d = 0; d < 3; d++)
                newPt[d] = p0[d] - layer * negOffset[d];
              negPoints.push_back (newPt);
            }
          std::array<double, 3> pLast = colPoints[nz - 1];
          std::array<double, 3> pSecondLast = colPoints[nz - 2];
          std::array<double, 3> posOffset;
          for (int d = 0; d < 3; d++)
            posOffset[d] = pLast[d] - pSecondLast[d];
          std::vector<std::array<double, 3> > posPoints;
          for (int layer = 1; layer <= numLayers; layer++)
            {
              std::array<double, 3> newPt;
              for (int d = 0; d < 3; d++)
                newPt[d] = pLast[d] + layer * posOffset[d];
              posPoints.push_back (newPt);
            }

          std::vector<std::array<double, 3> > fullColPoints;
          fullColPoints.insert (fullColPoints.end (), negPoints.begin (),
                                negPoints.end ());
          fullColPoints.insert (fullColPoints.end (), colPoints.begin (),
                                colPoints.end ());
          fullColPoints.insert (fullColPoints.end (), posPoints.begin (),
                                posPoints.end ());

          std::vector<std::vector<double> > fullColVectors;
          for (int k = 0; k < numLayers; k++)
            fullColVectors.push_back (defaultVector);
          fullColVectors.insert (fullColVectors.end (), colVectors.begin (),
                                 colVectors.end ());
          for (int k = 0; k < numLayers; k++)
            fullColVectors.push_back (defaultVector);

          columns[i + j * nx] = std::make_pair (fullColPoints, fullColVectors);
        }
    }

  vtkSmartPointer<vtkPoints> newPoints = vtkSmartPointer<vtkPoints>::New ();
  vtkSmartPointer<vtkDoubleArray> newVectors
      = vtkSmartPointer<vtkDoubleArray>::New ();
  newVectors->SetName (vectorName.c_str ());
  newVectors->SetNumberOfComponents (numComponents);

  // IMPORTANT: Correct ordering for VTK structured grid is:
  // for (int k = 0; k < new_nz; k++)
  //   for (int j = 0; j < ny; j++)
  //     for (int i = 0; i < nx; i++) { ... }
  for (int k = 0; k < new_nz; k++)
    {
      for (int j = 0; j < ny; j++)
        {
          for (int i = 0; i < nx; i++)
            {
              const auto &colPoints = columns[i + j * nx].first;
              const auto &colVecs = columns[i + j * nx].second;
              newPoints->InsertNextPoint (colPoints[k].data ());
              newVectors->InsertNextTuple (colVecs[k].data ());
            }
        }
    }

  vtkSmartPointer<vtkStructuredGrid> newSGrid
      = vtkSmartPointer<vtkStructuredGrid>::New ();
  newSGrid->SetDimensions (newDims);
  newSGrid->SetPoints (newPoints);
  newSGrid->GetPointData ()->AddArray (newVectors);
  return newSGrid;
}

void
vector_field::preprocess ()
{
  BIOMESH_LINFO ("Preprocessing vector field begin.");
  BIOMESH_LINFO ("Structured grid expansion begin.");
  vtkSmartPointer<vtkStructuredGrid> extendedX
      = addBothXLayers (m_sgrid, 5, m_vfield_tag);
  vtkSmartPointer<vtkStructuredGrid> extendedXY
      = addBothYLayers (extendedX, 5, m_vfield_tag);
  vtkSmartPointer<vtkStructuredGrid> extendedXYZ
      = addBothZLayers (extendedXY, 5, m_vfield_tag);
  m_sgrid->DeepCopy (extendedXYZ);
#ifdef BIOMESH_ENABLE_DEBUG
  std::string file_path = std::string (BIOMESH_BUILD_DIR) + "/results/"
                          + "expanded_structured_grid.vtk";
  vtkSmartPointer<vtkStructuredGridWriter> writer
      = vtkSmartPointer<vtkStructuredGridWriter>::New ();
  writer->SetFileName (file_path.c_str ());
  writer->SetInputData (m_sgrid);
  writer->Write ();
  BIOMESH_LINFO ("The expanded structured grid is written to: " + file_path);
#endif
  BIOMESH_LINFO ("Structured grid expansion end.");

  m_ct.classify_cells (m_sgrid, m_vfield_tag);
  BIOMESH_LINFO ("Preprocessing vector field end.");
}

int
vector_field::operator[] (size_t cell_index) const
{
  return m_ct[cell_index];
}

vtkSmartPointer<vtkStructuredGrid>
vector_field::get_grid () const
{
  return m_sgrid;
}

std::string
vector_field::get_tag () const
{
  return m_vfield_tag;
}

} // namespace biomesh