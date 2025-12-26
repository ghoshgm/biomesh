
#include <biomesh.hpp>
#include <iostream>

using namespace biomesh;
using fiber_grid3d = fiber_grid<fiber3D, vertex3D>;

int
main (int argc, char **argv)
{
  /* Load vector field from VTK file. */
  vector_field field (argv[1]);
  field.load_vtk_grid ();
  field.preprocess ();

  /* Generate fibers. */
  fiber_grid3d f (argv[2]);
  f.generate_fiber_grid (field, 200, 0.14);
  std::cout << f.size () << std::endl;

  /* Write fibers to JSON format. */
  json_parser jp1;
  jp1.export_fiber_grid_json<fiber_grid3d> (f, "ellipsoid3dr.json");

  /* Write fibers to VTK format. */
  visualization::export_fiber_grid_vtk<fiber_grid3d> (f, "ellipsoid3dr");

#if 0
  f.transformation(affine_transform::translation<fiber3D>, 0.0, 0.0, 16);
  f.transformation(affine_transform::reflection<fiber3D>, 2);

  /* Write fibers to JSON format. */
  json_parser jp2;
  jp2.export_fiber_grid_json<fiber_grid3d>(f, "ellipsoid3dr.json");

  /* Write fibers to VTK format. */
  visualization::export_fiber_grid_vtk<fiber_grid3d>(f, "ellipsoid3d_r");
#endif

  return EXIT_SUCCESS;
}