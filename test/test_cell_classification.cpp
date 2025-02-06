#include <iostream>
#include <biomesh_vector_field.hpp>
#include <biomesh_json_parser.hpp>
#include <biomesh_fiber_grid.hpp>
#include <biomesh_visualization.hpp>

using namespace biomesh;

int main(int argc, char **argv)
{
  /* Load vector field from VTK file. */
  vector_field field(argv[1]);
  field.load_vtk_grid();

  /* Classify cell in the vector field. */
  cell_table ct(field);
  ct.classify_cells();

  visualization::write_cell_type_vtk(ct, field, "foo");

  return EXIT_SUCCESS;
}