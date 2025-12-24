
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
/**
 * @brief Class to perform cell classification for the VTK structured grid.
 *
 * The input file for generating fibers is a VTK structured grid, a vector
 * field is embedded in on the grid. It is important to classify the cells
 * to identify the bounds of the fibers.
 *
 * The cell classification is as follows:
 * 0 -> The cells whose corners have no vectors.
 * 1 -> The cells whose corners have 1 or more corners ( not every corner )
 * with a vector. 2 -> The cells with vectors in all corners.
 *
 * The fibers are allowed to move in the '1' and '2' cells.
 */
class cell_table
{
public:
  /**
   * Constructor.
   */
  cell_table ();

  // void cell_table (vtkSmartPointer<vtkStructuredGrid> sgrid);

  /**
   * Function to perform the classification operation.
   *
   * @param[in] sgrid The VTK grid imported from the input VTK file.
   */
  void classify_cells (vtkSmartPointer<vtkStructuredGrid> sgrid);

  // void find_seed_cells (vtkSmartPointer<vtkStructuredGrid> sgrid);

  /**
   * Function to return the seed cell indices.
   */
  std::vector<int> get_seed_cells () const;

  /**
   * Function to return the cell type of a cell.
   *
   * @param[in] cell_index The index of the VTK cell.
   */
  int operator[] (size_t cell_index) const;

private:
  // vtkStructuredGrid *sgrid;
  std::vector<int> m_boundary_cell_index;
  std::vector<int> m_seed_cell_index;
  std::vector<int> m_cell_type;
};

} // namespace biomesh