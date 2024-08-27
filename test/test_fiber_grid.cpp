
#include <iostream>
#include <biomesh_vector_field.hpp>
#include <biomesh_fiber_grid2D.hpp>
#include <biomesh_json_parser.hpp>

using namespace biomesh;

int main(int argc, char** argv)
{
  /* Load vector field from VTK file. */
  vector_field field(argv[1]);
  field.load_vtk_grid();

  /* Generate fibers. */
  fiber_grid2D fg(argv[2]);
  fg.generate_fiber_grid(field, 15);

  /* Write fibers to JSON format. */
  json_parser jp;
  jp.export_fiber_grid_json<fiber_grid2D>(fg,"test.json");

  return EXIT_SUCCESS;
}