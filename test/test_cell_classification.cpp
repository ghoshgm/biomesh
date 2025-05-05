#include <iostream>
#include <biomesh_vector_field.hpp>
#include <biomesh_json_parser.hpp>
#include <biomesh_fiber_grid.hpp>
#include <biomesh_visualization.hpp>

using namespace biomesh;

int main(int argc, char **argv)
{
#ifndef BIOMESH_ENABLE_2D
  /* Load vector field from VTK file. */
  vector_field field(argv[2]);
  field.load_vtk_grid();

  /* Classify cell in the vector field. */
  cell_table ct;
  ct.classify_cells(field.get_grid());

  visualization::write_cell_type_vtk(ct, field, "test3d");
#else
  /* Load vector field from VTK file. */
  vector_field field(argv[1]);
  field.load_vtk_grid();

  /* Classify cell in the vector field. */
  cell_table ct(field.get_grid());
  ct.classify_cells();

  visualization::write_cell_type_vtk(ct, field, "test2d");
#endif

  return EXIT_SUCCESS;
}