
#include <iostream>
#include <biomesh_vector_field.hpp>
#include <biomesh_json_parser.hpp>
#include <biomesh_fiber_grid.hpp>
#include <biomesh_visualization.hpp>

using namespace biomesh;

int main(int argc, char** argv)
{
#if 0
  double lenx = 12;
  int vertex_count = 100;
  double mesh_width = lenx / (double)vertex_count;
#endif

  /* Load vector field from VTK file. */
  vector_field field(argv[1]);
  field.load_vtk_grid();

  /* Generate fibers. */
  fiber_grid<fiber2D,vertex2D> f(argv[2]);
  f.generate_fiber_grid(field, 10, 0.0001);

  /* Write fibers to JSON format. */
  json_parser jp;
  jp.export_fiber_grid_json< fiber_grid<fiber2D,vertex2D> >(f,"cuboid_fibers.json");

  /* Write fibers to VTK format. */
  visualization::export_fiber_grid_vtk< fiber_grid<fiber2D,vertex2D> >(f,"straight");

  return EXIT_SUCCESS;
}