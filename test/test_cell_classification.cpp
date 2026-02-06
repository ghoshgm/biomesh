#include <biomesh_fiber_grid.hpp>
#include <biomesh_json_parser.hpp>
#include <biomesh_vector_field.hpp>
#include <biomesh_visualization.hpp>
#include <iostream>

using namespace biomesh;

int
main (int argc, char **argv)
{
  std::string t = argv[2];
  std::cout << t << std::endl;

  /* Load vector field from VTK file. */
  vector_field field (argv[1], argv[2]);
  field.load_vtk_grid ();

  /* Classify cell in the vector field. */
  cell_table ct;
  ct.classify_cells (field.get_grid (), argv[2]);

  return EXIT_SUCCESS;
}