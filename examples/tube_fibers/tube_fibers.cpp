
#include <biomesh.hpp>
#include <iostream>

using namespace biomesh;
using fiber_grid3d = fiber_grid<fiber3D, vertex3D>;

int
main (int argc, char **argv)
{
  /* Load vector field from VTK file. */
  vector_field field (argv[1], argv[2]);
  field.load_vtk_grid ();
  field.preprocess ();

  /* Generate fibers. */
  fiber_grid3d f (argv[3]);
  int ret = f.generate_fiber_grid (field);
  BIOMESH_ASSERT(ret == BIOMESH_SUCCESS);

  /* Write fibers to JSON format. */
  json_parser jp1;
  jp1.export_fiber_grid_json<fiber_grid3d> (f, "fiber_demo.json");

  /* Write fibers to VTK format. */
  visualization::export_fiber_grid_vtk<fiber_grid3d> (f, "fiber_demo");

  return EXIT_SUCCESS;
}