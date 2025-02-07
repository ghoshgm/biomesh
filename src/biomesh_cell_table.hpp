
#include <bitset>
#include <vector>

#include <vtkCell.h>
#include <vtkPointData.h>
#include <vtkStructuredData.h>
#include <vtkStructuredGrid.h>

#include <biomesh_base.hpp>
#include <biomesh_vector_field.hpp>

namespace biomesh
{

class cell_table
{
public:
  cell_table (const vector_field &vfield);

  void classify_cells ();

  int operator[] (size_t cell_index) const;

private:
  vtkStructuredGrid *sgrid;
  std::vector<int> m_boundary_cell_index;
  std::vector<int> m_cell_type;
};

} // namespace biomesh