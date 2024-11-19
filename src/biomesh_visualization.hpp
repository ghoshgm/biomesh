
#ifndef BIOMESH_VISUALIZATION_HPP
#define BIOMESH_VISUALIZATION_HPP

#include <biomesh_base.hpp>
#include <biomesh_fiber_grid.hpp>

#include <vtkStructuredGrid.h>
#include <vtkStructuredGridWriter.h>

#include <string>

namespace biomesh
{

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

#include "biomesh_visualization.tpp"

} // namespace visualization

} // namespace biomesh

#endif