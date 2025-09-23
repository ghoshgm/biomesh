
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
  field.preprocess();

#if 1
  /* Classify cell in the vector field. */
  //cell_table ct;
  //ct.classify_cells(field.get_grid());
  //ct.find_seed_cells(field.get_grid());
  //visualization::write_cell_type_vtk(ct, field, "ellipsoid");
  //visualization::write_seed_type_vtk(ct, field, "ellipsoid");

  /* Generate fibers. */
  fiber_grid3d f(argv[2]);
  f.generate_fiber_grid(field, 100, 0.14);

  /* Write fibers to JSON format. */
  json_parser jp1;
  //jp1.export_fiber_grid_json<fiber_grid3d>(f, "ellipsoid3d.json");
  jp1.export_fiber_grid_json<fiber_grid3d>(f, "ellipsoid3dr.json");

  /* Write fibers to VTK format. */
  //visualization::export_fiber_grid_vtk<fiber_grid3d>(f, "ellipsoid3d");
  visualization::export_fiber_grid_vtk<fiber_grid3d>(f, "ellipsoid3dr");
#endif

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