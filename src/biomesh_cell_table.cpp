#include "biomesh_cell_table.hpp"

biomesh::cell_table::cell_table (const vector_field &vfield)
    : sgrid{ vfield.get_grid ().GetPointer () }
{
  m_cell_type.reserve (sgrid->GetNumberOfCells ());
}

static std::array<int, 2 * BIOMESH_DIM>
compute_face_neighbor_id (vtkStructuredGrid *structuredGrid, int cellId)
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

  return neighbors;
}

void
biomesh::cell_table::classify_cells ()
{
  size_t cell_count = sgrid->GetNumberOfCells ();

  for (size_t ii = 0; ii < cell_count; ++ii)
    {
      /* Compute face neighbor indices. */
      std::array<int, 2 *BIOMESH_DIM> face_neighbors
          = compute_face_neighbor_id (sgrid, ii);

      /* Determine cell type. */
      int valid_neighbor_count = 0;
      for (size_t jj = 0; jj < face_neighbors.size (); ++jj)
        {
          if (face_neighbors[jj] > 0)
            {
              /* Construct face neighbor. */
              vtkCell *neighbor = sgrid->GetCell (face_neighbors[jj]);
              BIOMESH_ASSERT ((neighbor != nullptr));

              /* Check if the cell has non-zero vectors. */
              int arridx = 1;
              vtkDataArray *da
                  = sgrid->GetPointData ()->GetArray ("vectors", arridx);
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

              is_zero
                  = std::all_of (
                        vx.begin (), vx.end (),
                        [] (double val) { return BIOMESH_DCOMP (val, 0.0); })
                    and std::all_of (
                        vy.begin (), vy.end (),
                        [] (double val) { return BIOMESH_DCOMP (val, 0.0); })
                    and std::all_of (vz.begin (), vz.end (), [] (double val) {
                          return BIOMESH_DCOMP (val, 0.0);
                        });
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
                  = std::all_of (
                        vx.begin (), vx.end (),
                        [] (double val) { return BIOMESH_DCOMP (val, 0.0); })
                    and std::all_of (vy.begin (), vy.end (), [] (double val) {
                          return BIOMESH_DCOMP (val, 0.0);
                        });
#endif
              if (!is_zero)
                {
                  ++valid_neighbor_count;
                }
            }
        }

      if (valid_neighbor_count == 0)
        {
          m_cell_type.push_back (0);
        }
      else if (valid_neighbor_count > 0
               and valid_neighbor_count < 2 * BIOMESH_DIM)
        {
          m_cell_type.push_back (1);
          m_boundary_cell_index.push_back (ii);
        }
      else if (valid_neighbor_count == 2 * BIOMESH_DIM)
        {
          m_cell_type.push_back (2);
        }
    }
}

int
biomesh::cell_table::operator[] (size_t cell_index) const
{
  BIOMESH_ASSERT ((cell_index >= 0) and (cell_index < m_cell_type.size ()));
  return m_cell_type[cell_index];
}