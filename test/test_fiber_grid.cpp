
#include <iostream>
#include <biomesh_vector_field.hpp>
#include <biomesh_fiber_grid2D.hpp>
#include <biomesh_json_parser.hpp>

using namespace biomesh;

int main(int argc, char** argv)
{
  vector_field field(argv[1]);

  field.load_vtk_grid();

  fiber_grid2D fg(argv[2]);
  fg.generate_fiber_grid(field, 4);

  json_parser jp;
  jp.export_fiber_grid_json<fiber_grid2D>(fg,"test.json");

  return EXIT_SUCCESS;
}