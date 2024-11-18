
#include <iostream>
#include <biomesh_vector_field.hpp>
#include <biomesh_json_parser.hpp>
#include <biomesh_fiber_grid.hpp>
#include <biomesh_visualization.hpp>

using namespace biomesh;

int main(int argc, char **argv)
{
  {
    /* Load vector field from VTK file. */
    vector_field field(argv[1]);
    field.load_vtk_grid();

    /* Generate fibers. */
    fiber_grid<fiber3D, vertex3D> f(argv[2]);
    f.generate_fiber_grid(field, 1000, 0.02);

    /* Write fibers to JSON format. */
    json_parser jp;
    jp.export_fiber_grid_json<fiber_grid<fiber3D, vertex3D>>(f, "straight3d.json");

    /* Write fibers to VTK format. */
    visualization::export_fiber_grid_vtk<fiber_grid<fiber3D, vertex3D>>(f, "straight3d");
  }

  {
    /* Load vector field from VTK file. */
    vector_field field(argv[3]);
    field.load_vtk_grid();

    /* Generate fibers. */
    fiber_grid<fiber3D, vertex3D> f(argv[4]);
    f.generate_fiber_grid(field, 1000, 0.02);

    /* Write fibers to JSON format. */
    json_parser jp;
    jp.export_fiber_grid_json<fiber_grid<fiber3D, vertex3D>>(f, "diagnol3d.json");

    /* Write fibers to VTK format. */
    visualization::export_fiber_grid_vtk<fiber_grid<fiber3D, vertex3D>>(f, "diagnol3d");
  }

  {
    /* Load vector field from VTK file. */
    vector_field field(argv[5]);
    field.load_vtk_grid();

    /* Generate fibers. */
    fiber_grid<fiber3D, vertex3D> f(argv[6]);
    f.generate_fiber_grid(field, 1000, 0.02);

    /* Write fibers to JSON format. */
    json_parser jp;
    jp.export_fiber_grid_json<fiber_grid<fiber3D, vertex3D>>(f, "diagnol_z3d.json");

    /* Write fibers to VTK format. */
    visualization::export_fiber_grid_vtk<fiber_grid<fiber3D, vertex3D>>(f, "diagnol_z3d");
  }

  {
    /* Load vector field from VTK file. */
    vector_field field(argv[7]);
    field.load_vtk_grid();

    /* Generate fibers. */
    fiber_grid<fiber3D, vertex3D> f(argv[8]);
    f.generate_fiber_grid(field, 1000, 0.02);

    /* Write fibers to JSON format. */
    json_parser jp;
    jp.export_fiber_grid_json<fiber_grid<fiber3D, vertex3D>>(f, "wave_laminar3d.json");

    /* Write fibers to VTK format. */
    visualization::export_fiber_grid_vtk<fiber_grid<fiber3D, vertex3D>>(f, "wave_laminar3d");
  }

  {
    /* Load vector field from VTK file. */
    vector_field field(argv[9]);
    field.load_vtk_grid();

    /* Generate fibers. */
    fiber_grid<fiber3D, vertex3D> f(argv[10]);
    f.generate_fiber_grid(field, 1000, 0.02);

    /* Write fibers to JSON format. */
    json_parser jp;
    jp.export_fiber_grid_json<fiber_grid<fiber3D, vertex3D>>(f, "spiral3d.json");

    /* Write fibers to VTK format. */
    visualization::export_fiber_grid_vtk<fiber_grid<fiber3D, vertex3D>>(f, "spiral3d");
  }

  return EXIT_SUCCESS;
}