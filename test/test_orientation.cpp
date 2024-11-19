
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
    fiber_grid<fiber3D, vertex3D> f(argv[3]);
    f.generate_fiber_grid(field, 4, 0.1);

    /* Write fibers to JSON format. */
    json_parser jp;
    jp.export_fiber_grid_json<fiber_grid<fiber3D, vertex3D>>(f, "fiber_x.json");
  }

  {
    /* Load vector field from VTK file. */
    vector_field field(argv[2]);
    field.load_vtk_grid();

    /* Generate fibers. */
    fiber_grid<fiber3D, vertex3D> f(argv[3]);
    f.generate_fiber_grid(field, 4, 0.1);

    /* Write fibers to JSON format. */
    json_parser jp;
    jp.export_fiber_grid_json<fiber_grid<fiber3D, vertex3D>>(f, "fiber_z.json");
  }

  return EXIT_SUCCESS;
}