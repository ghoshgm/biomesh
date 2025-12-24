
#ifndef BIOMESH_VISUALIZATION_HPP
#define BIOMESH_VISUALIZATION_HPP

#include <biomesh_base.hpp>
#include <biomesh_fiber_grid.hpp>
#include <biomesh_vector_field.hpp>

#include <vtkCellData.h>
#include <vtkIntArray.h>
#include <vtkPoints.h>
#include <vtkSmartPointer.h>
#include <vtkStructuredGrid.h>
#include <vtkStructuredGridWriter.h>

#include <string>

namespace biomesh
{
/**
 * @brief Class for exporting data for visualization
 * using paraview.
 */
namespace visualization
{

/**
 * Export fiber grid to VTK format for visualization in paraview.
 * Every fiber in the fiber grid is written to a separate VTK file.
 *
 * The default directory for the files is the build directory.
 *
 * @param[in] fgrid The fiber grid data structure to be written.
 * @param[in] file_prefix The prefix to the VTK files.
 */
template <class fiber_grid>
void export_fiber_grid_vtk (const fiber_grid &fgrid,
                            const std::string &file_prefix);

/**
 * Write cell type data to a VTK structured grid for
 * visualization in paraview.
 *
 * This function does not modify the VTK file provided
 * as the user.
 * It writes a new VTK structured grid embedded with cell type
 * data.
 *
 * This function is only meant to be used for visualization
 * of the muscle domain.
 *
 * The default directory for the files is the build directory.
 *
 * @param[in] ctable The cell table class to be visualized.
 * @param[in] vfield The vector field provided by the user.
 * @param[in] file_prefix The prefix to the VTK files.
 */
template <class fiber_grid>
void write_cell_type_vtk (const cell_table &ctable, const vector_field &vfield,
                          const std::string &file_prefix);

#include "biomesh_visualization.tpp"

} // namespace visualization

} // namespace biomesh

#endif