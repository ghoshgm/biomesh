
#include <span>
#include <vector>

#include <vtkCell.h>
#include <vtkPointData.h>
#include <vtkSmartPointer.h>
#include <vtkStructuredData.h>
#include <vtkStructuredGrid.h>

#include <biomesh_base.hpp>

namespace biomesh
{

class cell_table
{
public:
  cell_table ();

  // void cell_table (vtkSmartPointer<vtkStructuredGrid> sgrid);

  void classify_cells (vtkSmartPointer<vtkStructuredGrid> sgrid);

  void find_seed_cells (vtkSmartPointer<vtkStructuredGrid> sgrid);

  std::vector<int> get_seed_cells () const;

  int operator[] (size_t cell_index) const;

private:
  // vtkStructuredGrid *sgrid;
  std::vector<int> m_boundary_cell_index;
  std::vector<int> m_seed_cell_index;
  std::vector<int> m_cell_type;
};

} // namespace biomesh