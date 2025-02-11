
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
    fiber_grid<fiber2D, vertex2D> f(argv[2]);
    f.generate_fiber_grid(field, 1000, 0.2);

    /* Write fibers to JSON format. */
    json_parser jp;
    jp.export_fiber_grid_json<fiber_grid<fiber2D, vertex2D>>(f, "straight2d.json");

    /* Write fibers to VTK format. */
    visualization::export_fiber_grid_vtk<fiber_grid<fiber2D, vertex2D>>(f, "straight2d");
  }

  {
    /* Load vector field from VTK file. */
    vector_field field(argv[3]);
    field.load_vtk_grid();

        /* Generate fibers. */
    fiber_grid<fiber2D, vertex2D> f(argv[4]);
    f.generate_fiber_grid(field, 100, 0.2);

    /* Write fibers to JSON format. */
    json_parser jp;
    jp.export_fiber_grid_json<fiber_grid<fiber2D, vertex2D>>(f, "radial2d.json");

    /* Write fibers to VTK format. */
    visualization::export_fiber_grid_vtk<fiber_grid<fiber2D, vertex2D>>(f, "radial2d");
  }

  {
    /* Load vector field from VTK file. */
    vector_field field(argv[5]);
    field.load_vtk_grid();

    /* Generate fibers. */
    fiber_grid<fiber2D, vertex2D> f(argv[6]);
    f.generate_fiber_grid(field, 1000, 0.2);

    /* Write fibers to JSON format. */
    json_parser jp;
    jp.export_fiber_grid_json<fiber_grid<fiber2D, vertex2D>>(f, "diagnol2d.json");

    /* Write fibers to VTK format. */
    visualization::export_fiber_grid_vtk<fiber_grid<fiber2D, vertex2D>>(f, "diagnol2d");
  }

  {
    /* Load vector field from VTK file. */
    vector_field field(argv[7]);
    field.load_vtk_grid();

    /* Generate fibers. */
    fiber_grid<fiber2D, vertex2D> f(argv[8]);
    f.generate_fiber_grid(field, 100, 0.2);

    /* Write fibers to JSON format. */
    json_parser jp;
    jp.export_fiber_grid_json<fiber_grid<fiber2D, vertex2D>>(f, "quarter_circle2d.json");

    /* Write fibers to VTK format. */
    visualization::export_fiber_grid_vtk<fiber_grid<fiber2D, vertex2D>>(f, "quarter_circle2d");
  }

  {
    /* Load vector field from VTK file. */
    vector_field field(argv[9]);
    field.load_vtk_grid();

    /* Generate fibers. */
    fiber_grid<fiber2D, vertex2D> f(argv[10]);
    f.generate_fiber_grid(field, 50, 0.04);

    /* Write fibers to JSON format. */
    json_parser jp;
    jp.export_fiber_grid_json<fiber_grid<fiber2D, vertex2D>>(f, "melon2d.json");

    /* Write fibers to VTK format. */
    visualization::export_fiber_grid_vtk<fiber_grid<fiber2D, vertex2D>>(f, "melon2d");
  }

  {
    /* Load vector field from VTK file. */
    vector_field field(argv[11]);
    field.load_vtk_grid();

    /* Generate fibers. */
    fiber_grid<fiber2D, vertex2D> f(argv[12]);
    f.generate_fiber_grid(field, 1000, 0.01);

    /* Write fibers to JSON format. */
    json_parser jp;
    jp.export_fiber_grid_json<fiber_grid<fiber2D, vertex2D>>(f, "random2d.json");

    /* Write fibers to VTK format. */
    visualization::export_fiber_grid_vtk<fiber_grid<fiber2D, vertex2D>>(f, "random2d");
  }

  {
    /* Load vector field from VTK file. */
    vector_field field(argv[13]);
    field.load_vtk_grid();

    /* Generate fibers. */
    fiber_grid<fiber2D, vertex2D> f(argv[14]);
    f.generate_fiber_grid(field, 1000, 0.2);

    /* Write fibers to JSON format. */
    json_parser jp;
    jp.export_fiber_grid_json<fiber_grid<fiber2D, vertex2D>>(f, "circle2d.json");

    /* Write fibers to VTK format. */
    visualization::export_fiber_grid_vtk<fiber_grid<fiber2D, vertex2D>>(f, "circle2d");
  }

  {
    /* Load vector field from VTK file. */
    vector_field field(argv[15]);
    field.load_vtk_grid();

    /* Generate fibers. */
    fiber_grid<fiber2D, vertex2D> f(argv[16]);
    f.generate_fiber_grid(field, 30, 0.1);

    /* Write fibers to JSON format. */
    json_parser jp;
    jp.export_fiber_grid_json<fiber_grid<fiber2D, vertex2D>>(f, "zero2d.json");

    /* Write fibers to VTK format. */
    visualization::export_fiber_grid_vtk<fiber_grid<fiber2D, vertex2D>>(f, "zero2d");
  }

  return EXIT_SUCCESS;
}