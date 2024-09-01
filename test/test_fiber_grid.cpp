
#include <iostream>
#include <biomesh_vector_field.hpp>
#include <biomesh_json_parser.hpp>
#include <biomesh_fiber_grid.hpp>
#include <biomesh_visualization.hpp>

using namespace biomesh;

int main(int argc, char** argv)
{
  /* Load vector field from VTK file. */
  vector_field field(argv[1]);
  field.load_vtk_grid();

  /* Generate fibers. */
  fiber_grid<fiber2D,vertex2D> f(argv[2]);
  f.generate_fiber_grid(field, 15, 0.2);

  /* Write fibers to JSON format. */
  json_parser jp;
  jp.export_fiber_grid_json< fiber_grid<fiber2D,vertex2D> >(f,"test.json");

  /* Write fibers to VTK format. */
  visualization::export_fiber_grid_vtk< fiber_grid<fiber2D,vertex2D> >(f);

  return EXIT_SUCCESS;
}