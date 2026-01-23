#include "biomesh_cell_table.hpp"

#include <biomesh_interpolation.hpp>
#include <biomesh_vertex3d.hpp>
#include <boost/numeric/odeint.hpp>
#include <map>
#include <vtkHexahedron.h>

biomesh::cell_table::cell_table () {}

void
biomesh::cell_table::classify_cells (vtkSmartPointer<vtkStructuredGrid> sgrid)
{
  BIOMESH_LINFO ("Cell classification begin.");
  BIOMESH_ASSERT (sgrid != nullptr);
  size_t cell_count = sgrid->GetNumberOfCells ();

  for (size_t ii = 0; ii < cell_count; ++ii)
    {
      vtkCell *neighbor = sgrid->GetCell (ii);

      /* Check if the cell has non-zero vectors. */
      int arridx = 1;
      // vtkDataArray *da = sgrid->GetPointData ()->GetArray ("vectors",
      // arridx);
      vtkDataArray *da = sgrid->GetPointData ()->GetArray ("flowExt", arridx);
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
  BIOMESH_LINFO ("Cell classification end.");
}

int
biomesh::cell_table::operator[] (size_t cell_index) const
{
  BIOMESH_ASSERT ((cell_index >= 0) and (cell_index < m_cell_type.size ()));
  return m_cell_type[cell_index];
}