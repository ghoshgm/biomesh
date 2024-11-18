
#include <iostream>
#include <biomesh_vector_field.hpp>
#include <biomesh_json_parser.hpp>
#include <biomesh_fiber_grid.hpp>
#include <biomesh_visualization.hpp>

using namespace biomesh;
using fiber_grid3d = fiber_grid<fiber3D, vertex3D>;

int main(int argc, char **argv)
{
  /* Load vector field from VTK file. */
  vector_field field(argv[1]);
  field.load_vtk_grid();

  /* Generate fibers. */
  fiber_grid3d f(argv[2]);
  f.generate_fiber_grid(field, 100, 0.02);

  /* Write fibers to JSON format. */
  json_parser jp;
  jp.export_fiber_grid_json<fiber_grid3d>(f, "ellipsoid3d.json");

  /* Write fibers to VTK format. */
  visualization::export_fiber_grid_vtk<fiber_grid3d>(f, "ellipsoid3d");

  return EXIT_SUCCESS;
}