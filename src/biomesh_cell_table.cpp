#include "biomesh_cell_table.hpp"

#include <biomesh_interpolation.hpp>
#include <biomesh_vertex3d.hpp>
#include <boost/numeric/odeint.hpp>
#include <map>
#include <vtkHexahedron.h>

biomesh::cell_table::cell_table () {}

#if 0
biomesh::cell_table::cell_table(vtkSmartPointer<vtkStructuredGrid> sgrid)
    : sgrid{sgrid.GetPointer()}
{
  m_cell_type.reserve (sgrid->GetNumberOfCells ());
}
#endif

static std::array<int, 8>
compute_corner_neighbor_id (vtkStructuredGrid *structuredGrid, int cellId)
{
  int dims[3];
  structuredGrid->GetDimensions (dims);
  int nx = dims[0] - 1;
  int ny = dims[1] - 1;
  int nz = dims[2] - 1;

  std::vector<int> cneighbors;

  int ijk[3];
  vtkStructuredData::ComputeCellStructuredCoords (cellId, dims, ijk);
  int i = ijk[0];
  int j = ijk[1];
  int k = ijk[2];
  std::cout << i << " " << j << " " << k << std::endl;

  for (int dz = -1; dz <= 0; ++dz)
    {
      for (int dy = -1; dy <= 0; ++dy)
        {
          for (int dx = -1; dx <= 0; ++dx)
            {
              int ni = i + dx;
              int nj = j + dy;
              int nk = k + dz;

              // Check bounds
              if (ni >= 0 && ni < nx && nj >= 0 && nj < ny && nk >= 0
                  && nk < nz)
                {
                  int temp[3];
                  temp[0] = ni;
                  temp[1] = nj;
                  temp[2] = nk;
                  std::cout << "temp: " << temp[0] << " " << temp[1] << " "
                            << temp[2] << std::endl;
                  int neighborId
                      = vtkStructuredData::ComputeCellId (dims, temp);
                  cneighbors.push_back (neighborId);
                }
            }
        }
    }

  std::array<int, 8> corner_neighbors;

  std::copy (cneighbors.begin (), cneighbors.end (),
             corner_neighbors.begin ());

  return corner_neighbors;
}

static std::array<int, 12>
compute_edge_neighbor_id (vtkStructuredGrid *structuredGrid, int cellId,
                          int eid)
{
  int dims[3];
  structuredGrid->GetDimensions (dims);
  int nx = dims[0] - 1;
  int ny = dims[1] - 1;
  int nz = dims[2] - 1;

  std::array<int, 12> edge_neighbors;
  edge_neighbors.fill (-1);

  int ijk[3];
  vtkStructuredData::ComputeCellStructuredCoords (cellId, dims, ijk);
  int i = ijk[0];
  int j = ijk[1];
  int k = ijk[2];

  // List of 12 edge offset directions
  const int edgeOffsets[12][3]
      = { { +1, +1, 0 }, { +1, -1, 0 }, { -1, +1, 0 }, { -1, -1, 0 },
          { +1, 0, +1 }, { +1, 0, -1 }, { -1, 0, +1 }, { -1, 0, -1 },
          { 0, +1, +1 }, { 0, +1, -1 }, { 0, -1, +1 }, { 0, -1, -1 } };

  for (int n = 0; n < 12; ++n)
    {
      if (n == eid)
        {
          int ni = i + edgeOffsets[n][0];
          int nj = j + edgeOffsets[n][1];
          int nk = k + edgeOffsets[n][2];

          // Check bounds
          if (ni >= 0 && ni < nx && nj >= 0 && nj < ny && nk >= 0 && nk < nz)
            {
              int temp[3];
              temp[0] = ni;
              temp[1] = nj;
              temp[2] = nk;
              int neighborId = vtkStructuredData::ComputeCellId (dims, temp);
              edge_neighbors[n] = neighborId;
            }
        }
    }

  return edge_neighbors;
}

static std::array<int, 2 * BIOMESH_DIM>
compute_face_neighbor_id (vtkStructuredGrid *structuredGrid, int cellId,
                          int fid)
{
  int dims[3];
  structuredGrid->GetDimensions (dims);
  int nx = dims[0] - 1;
  int ny = dims[1] - 1;
  int nz = dims[2] - 1;

  std::array<int, 2 * BIOMESH_DIM> neighbors;
  neighbors.fill (-1);

  int ijk[3];
  vtkStructuredData::ComputeCellStructuredCoords (cellId, dims, ijk);
  int i = ijk[0];
  int j = ijk[1];
  int k = ijk[2];

#ifndef BIOMESH_ENABLE_2D
  int offsets[6][3] = { { -1, 0, 0 }, { 1, 0, 0 },  { 0, -1, 0 },
                        { 0, 1, 0 },  { 0, 0, -1 }, { 0, 0, 1 } };
#else
  int offsets[4][2] = {
    { -1, 0 }, // Left (-X)
    { 1, 0 },  // Right (+X)
    { 0, -1 }, // Bottom (-Y)
    { 0, 1 }   // Top (+Y)
  };
#endif

  // Compute valid neighbors
  for (int n = 0; n < 2 * BIOMESH_DIM; n++)
    {
      if (n == fid)
        {
          int ni = i + offsets[n][0];
          int nj = j + offsets[n][1];
#ifndef BIOMESH_ENABLE_2D
          int nk = k + offsets[n][2];
#endif
          // Bounds check
          if (ni >= 0 and ni < nx and nj >= 0 and nj < ny
#ifndef BIOMESH_ENABLE_2D
              and nk >= 0 and nk < nz
#endif
          )
            {
              int temp[3];
              temp[0] = ni;
              temp[1] = nj;
#ifndef BIOMESH_ENABLE_2D
              temp[2] = nk;
#else
              temp[2] = 0;
#endif
              int neighborId = vtkStructuredData::ComputeCellId (dims, temp);
              neighbors[n] = neighborId;
            }
        }
    }

  return neighbors;
}

void
biomesh::cell_table::classify_cells (vtkSmartPointer<vtkStructuredGrid> sgrid)
{
  BIOMESH_ASSERT (sgrid != nullptr);
  size_t cell_count = sgrid->GetNumberOfCells ();

  for (size_t ii = 0; ii < cell_count; ++ii)
    {
      vtkCell *neighbor = sgrid->GetCell (ii);

      /* Check if the cell has non-zero vectors. */
      int arridx = 1;
      vtkDataArray *da = sgrid->GetPointData ()->GetArray ("vectors", arridx);
      // vtkDataArray *da = sgrid->GetPointData ()->GetArray ("flowExt",
      // arridx);
      BIOMESH_ASSERT ((da != nullptr));

      vtkIdList *pids = neighbor->GetPointIds ();
      BIOMESH_ASSERT ((pids != nullptr));

      bool is_zero = false;
#ifndef BIOMESH_ENABLE_2D
      std::array<double, 8> vx{ (da->GetTuple3 (pids->GetId (0)))[0],
                                (da->GetTuple3 (pids->GetId (1)))[0],
                                (da->GetTuple3 (pids->GetId (2)))[0],
                                (da->GetTuple3 (pids->GetId (3)))[0],
                                (da->GetTuple3 (pids->GetId (4)))[0],
                                (da->GetTuple3 (pids->GetId (5)))[0],
                                (da->GetTuple3 (pids->GetId (6)))[0],
                                (da->GetTuple3 (pids->GetId (7)))[0] };

      std::array<double, 8> vy{ (da->GetTuple3 (pids->GetId (0)))[1],
                                (da->GetTuple3 (pids->GetId (1)))[1],
                                (da->GetTuple3 (pids->GetId (2)))[1],
                                (da->GetTuple3 (pids->GetId (3)))[1],
                                (da->GetTuple3 (pids->GetId (4)))[1],
                                (da->GetTuple3 (pids->GetId (5)))[1],
                                (da->GetTuple3 (pids->GetId (6)))[1],
                                (da->GetTuple3 (pids->GetId (7)))[1] };

      std::array<double, 8> vz{ (da->GetTuple3 (pids->GetId (0)))[2],
                                (da->GetTuple3 (pids->GetId (1)))[2],
                                (da->GetTuple3 (pids->GetId (2)))[2],
                                (da->GetTuple3 (pids->GetId (3)))[2],
                                (da->GetTuple3 (pids->GetId (4)))[2],
                                (da->GetTuple3 (pids->GetId (5)))[2],
                                (da->GetTuple3 (pids->GetId (6)))[2],
                                (da->GetTuple3 (pids->GetId (7)))[2] };

      if (std::all_of (vx.begin (), vx.end (),
                       [] (double val) { return BIOMESH_DCOMP (val, 0.0); })
          and std::all_of (
              vy.begin (), vy.end (),
              [] (double val) { return BIOMESH_DCOMP (val, 0.0); })
          and std::all_of (vz.begin (), vz.end (), [] (double val) {
                return BIOMESH_DCOMP (val, 0.0);
              }))
        {
          m_cell_type.push_back (0);
        }
      else if (std::all_of (
                   vx.begin (), vx.end (),
                   [] (double val) { return !BIOMESH_DCOMP (val, 0.0); })
               and std::all_of (
                   vy.begin (), vy.end (),
                   [] (double val) { return !BIOMESH_DCOMP (val, 0.0); })
               and std::all_of (vz.begin (), vz.end (), [] (double val) {
                     return !BIOMESH_DCOMP (val, 0.0);
                   }))
        {
          m_cell_type.push_back (2);
        }
      else
        {
          m_cell_type.push_back (1);
          m_boundary_cell_index.push_back (ii);
        }
#else
      std::array<double, 4> vx{ (da->GetTuple3 (pids->GetId (0)))[0],
                                (da->GetTuple3 (pids->GetId (1)))[0],
                                (da->GetTuple3 (pids->GetId (2)))[0],
                                (da->GetTuple3 (pids->GetId (3)))[0] };

      std::array<double, 4> vy{ (da->GetTuple3 (pids->GetId (0)))[1],
                                (da->GetTuple3 (pids->GetId (1)))[1],
                                (da->GetTuple3 (pids->GetId (2)))[1],
                                (da->GetTuple3 (pids->GetId (3)))[1] };

      is_zero
          = std::all_of (vx.begin (), vx.end (),
                         [] (double val) { return BIOMESH_DCOMP (val, 0.0); })
            and std::all_of (vy.begin (), vy.end (), [] (double val) {
                  return BIOMESH_DCOMP (val, 0.0);
                });
#endif
    }
}

void
ComputeNormal (vtkCell *face, double normal[3])
{
  // We need at least 3 points to define a plane.
  if (face->GetNumberOfPoints () < 3)
    {
      normal[0] = normal[1] = normal[2] = 0.0;
      return;
    }

  double p0[3], p1[3], p2[3];
  face->GetPoints ()->GetPoint (0, p0);
  face->GetPoints ()->GetPoint (1, p1);
  face->GetPoints ()->GetPoint (2, p2);

  double v1[3], v2[3];
  for (int i = 0; i < 3; i++)
    {
      v1[i] = p1[i] - p0[i];
      v2[i] = p2[i] - p0[i];
    }

  // Cross product v1 x v2 to get the face normal.
  normal[0] = v1[1] * v2[2] - v1[2] * v2[1];
  normal[1] = v1[2] * v2[0] - v1[0] * v2[2];
  normal[2] = v1[0] * v2[1] - v1[1] * v2[0];

  // Normalize the normal vector.
  double mag = std::sqrt (normal[0] * normal[0] + normal[1] * normal[1]
                          + normal[2] * normal[2]);
  if (mag != 0)
    {
      normal[0] /= mag;
      normal[1] /= mag;
      normal[2] /= mag;
    }
}

void
biomesh::cell_table::find_seed_cells (vtkSmartPointer<vtkStructuredGrid> sgrid)
{
  size_t cell_count = sgrid->GetNumberOfCells ();
  std::vector<int> temp (cell_count, 1);

  int arridx = 1;
  vtkDataArray *da = sgrid->GetPointData ()->GetArray ("vectors", arridx);
  BIOMESH_ASSERT ((da != nullptr));

  for (const int &bidx : m_boundary_cell_index)
    {
      /* Grab the cell. */
      vtkCell *cell = sgrid->GetCell (bidx);

      /* Find the center of the cell. */
      double pcenter[3];
      cell->GetParametricCenter (pcenter);

      vtkIdList *pids = cell->GetPointIds ();
      BIOMESH_ASSERT ((pids != nullptr));

      /* Grab the vectors. */
      std::array<double, 8> vx{ (da->GetTuple3 (pids->GetId (0)))[0],
                                (da->GetTuple3 (pids->GetId (1)))[0],
                                (da->GetTuple3 (pids->GetId (2)))[0],
                                (da->GetTuple3 (pids->GetId (3)))[0],
                                (da->GetTuple3 (pids->GetId (4)))[0],
                                (da->GetTuple3 (pids->GetId (5)))[0],
                                (da->GetTuple3 (pids->GetId (6)))[0],
                                (da->GetTuple3 (pids->GetId (7)))[0] };

      std::array<double, 8> vy{ (da->GetTuple3 (pids->GetId (0)))[1],
                                (da->GetTuple3 (pids->GetId (1)))[1],
                                (da->GetTuple3 (pids->GetId (2)))[1],
                                (da->GetTuple3 (pids->GetId (3)))[1],
                                (da->GetTuple3 (pids->GetId (4)))[1],
                                (da->GetTuple3 (pids->GetId (5)))[1],
                                (da->GetTuple3 (pids->GetId (6)))[1],
                                (da->GetTuple3 (pids->GetId (7)))[1] };

      std::array<double, 8> vz{ (da->GetTuple3 (pids->GetId (0)))[2],
                                (da->GetTuple3 (pids->GetId (1)))[2],
                                (da->GetTuple3 (pids->GetId (2)))[2],
                                (da->GetTuple3 (pids->GetId (3)))[2],
                                (da->GetTuple3 (pids->GetId (4)))[2],
                                (da->GetTuple3 (pids->GetId (5)))[2],
                                (da->GetTuple3 (pids->GetId (6)))[2],
                                (da->GetTuple3 (pids->GetId (7)))[2] };

      /* Trilinear interpolation in parametric coordinates. */
      biomesh::vertex3D pnext (pcenter[0], pcenter[1], pcenter[2]);
      double x = biomesh::interpolation::trilinear (pnext, vx);
      double y = biomesh::interpolation::trilinear (pnext, vy);
      double z = biomesh::interpolation::trilinear (pnext, vz);
      double iv[3]{ x, y, z };

      /* Now check if the interpolated vector points to 
         a face, corner or edge of the cell.
      */
      
      /* Loop over all corners. */
      std::array<int, 8> cid
          = compute_corner_neighbor_id (sgrid, bidx);
      
          
#ifndef BIOMESH_ENABLE_2D
      /* Loop over all edges. */
#endif

      /* Compute which face the interpolated vector points to. */
      int numFaces = cell->GetNumberOfFaces ();
      double bestDot = -1.0;
      int bestFaceIndex = -1;
      for (int f = 0; f < numFaces; f++)
        {
          vtkCell *face = cell->GetFace (f);
          double normal[3];
          ComputeNormal (face, normal);

          double dot
              = iv[0] * normal[0] + iv[1] * normal[1] + iv[2] * normal[2];
          if (dot > bestDot)
            {
              bestDot = dot;
              bestFaceIndex = f;
            }
        }

      std::array<int, 2 *BIOMESH_DIM> fid
          = compute_face_neighbor_id (sgrid, bidx, bestFaceIndex);
      if (m_cell_type[fid[bestFaceIndex]] == 2)
        {
          temp[bidx] = 3;
        }
    }

  m_seed_cell_index = temp;
}

#if 0
static void
compute_vector (vtkStructuredGrid *sgrid, const std::vector<double> &svec,
                std::vector<double> &drdt, double t, int &cid)
{
  /**
   * The 'FindCell' function in the VTK lib returns more information
   * than needed. We are only interested in the return value of the
   * function and 'pcoords'. The variables 'subid','weights' are
   * return variables which are not needed for our application
   * but are essential to avoid segfaults.
   */
  int subid;
  double pcoords[3];
  double weights[VTK_CELL_SIZE];

  int arridx = 1;
  vtkDataArray *da = sgrid->GetPointData ()->GetArray ("vectors", arridx);
  BIOMESH_ASSERT ((da != nullptr));

  /* The initial seed vertex. */
  double current_vertex[3] = { svec[0], svec[1], svec[2] };
  auto cellid = sgrid->FindCell (current_vertex, nullptr, -1, 0, subid,
                                 pcoords, weights);

  /* Only consider the vertices within the bounds of the structured grid.
   */
  if (cellid >= 0)
    {
      cid = cellid;

      /* Grab the cell. */
      vtkCell *seed_cell = sgrid->GetCell (cellid);
      BIOMESH_ASSERT ((seed_cell != nullptr));
      BIOMESH_ASSERT ((seed_cell->GetCellType () == VTK_HEXAHEDRON));

      /* Grab the point indices. */
      vtkIdList *pids = seed_cell->GetPointIds ();
      BIOMESH_ASSERT ((pids != nullptr));

      /* Grab the vectors. */
      std::array<double, 8> vx{ (da->GetTuple3 (pids->GetId (0)))[0],
                                (da->GetTuple3 (pids->GetId (1)))[0],
                                (da->GetTuple3 (pids->GetId (2)))[0],
                                (da->GetTuple3 (pids->GetId (3)))[0],
                                (da->GetTuple3 (pids->GetId (4)))[0],
                                (da->GetTuple3 (pids->GetId (5)))[0],
                                (da->GetTuple3 (pids->GetId (6)))[0],
                                (da->GetTuple3 (pids->GetId (7)))[0] };

      std::array<double, 8> vy{ (da->GetTuple3 (pids->GetId (0)))[1],
                                (da->GetTuple3 (pids->GetId (1)))[1],
                                (da->GetTuple3 (pids->GetId (2)))[1],
                                (da->GetTuple3 (pids->GetId (3)))[1],
                                (da->GetTuple3 (pids->GetId (4)))[1],
                                (da->GetTuple3 (pids->GetId (5)))[1],
                                (da->GetTuple3 (pids->GetId (6)))[1],
                                (da->GetTuple3 (pids->GetId (7)))[1] };

      std::array<double, 8> vz{ (da->GetTuple3 (pids->GetId (0)))[2],
                                (da->GetTuple3 (pids->GetId (1)))[2],
                                (da->GetTuple3 (pids->GetId (2)))[2],
                                (da->GetTuple3 (pids->GetId (3)))[2],
                                (da->GetTuple3 (pids->GetId (4)))[2],
                                (da->GetTuple3 (pids->GetId (5)))[2],
                                (da->GetTuple3 (pids->GetId (6)))[2],
                                (da->GetTuple3 (pids->GetId (7)))[2] };

      /* Trilinear interpolation in parametric coordinates. */
      biomesh::vertex3D pnext (pcoords[0], pcoords[1], pcoords[2]);
      drdt[0] = biomesh::interpolation::trilinear (pnext, vx);
      drdt[1] = biomesh::interpolation::trilinear (pnext, vy);
      drdt[2] = biomesh::interpolation::trilinear (pnext, vz);
    }
}

static bool
is_inside_grid (vtkStructuredGrid *sgrid, const std::vector<double> &v)
{
  double *bb = sgrid->GetBounds ();
  return ((v[0] >= bb[0] and v[0] <= bb[1])
          and (v[1] >= bb[2] and v[1] <= bb[3])
          and (v[2] >= bb[4] and v[2] <= bb[5]));
}
#endif

#if 0
void
biomesh::cell_table::find_seed_cells (vtkSmartPointer<vtkStructuredGrid> sgrid)
{
  size_t cell_count = sgrid->GetNumberOfCells ();
  std::vector<int> temp(cell_count);

  for (const int &bidx : m_boundary_cell_index)
    {
      /* Grab the cell. */
      vtkCell *cell = sgrid->GetCell (bidx);

      /* Compute the center. */
      double pcenter[3]; // to hold the parametric center
      double xcenter[3]; // to hold the physical center
      double weights[8]; // size depends on the maximum number of cell points
      int subId;
      cell->GetParametricCenter (pcenter);
      cell->EvaluateLocation (subId, pcenter, xcenter, weights);

      /* Trace streamlines in forward and reverse. */
      double t_start = 0.0;
      double t_end = 100.0;
      double dt = 0.1;
      std::vector<double> start{ xcenter[0], xcenter[1], xcenter[2] };

      boost::numeric::odeint::runge_kutta4<std::vector<double> > rk4_stepper;

      while (t_start < t_end and is_inside_grid (sgrid.GetPointer (), start))
        {
          int cell_id = 0;
          rk4_stepper.do_step (
              [&] (const std::vector<double> &svec, std::vector<double> &drdt,
                   double t) {
                compute_vector (sgrid.GetPointer (), svec, drdt, t, cell_id);
              },
              start, t_start, dt);

          if (cell_id != bidx)
            {
              if (m_cell_type[cell_id] == 0)
                {
                  //m_seed_cell_index.push_back (cell_id);
                  temp[cell_id] = 1;
                  break;
                }
            }

          /* Increment step. */
          t_start += dt;
        }
    }

    m_seed_cell_index = temp;
}
#endif

std::vector<int>
biomesh::cell_table::get_seed_cells () const
{
  return m_seed_cell_index;
}

int
biomesh::cell_table::operator[] (size_t cell_index) const
{
  BIOMESH_ASSERT ((cell_index >= 0) and (cell_index < m_cell_type.size ()));
  return m_cell_type[cell_index];
}