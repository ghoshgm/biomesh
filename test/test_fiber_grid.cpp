
#include <iostream>
#include <biomesh_vector_field.hpp>
#include <biomesh_fiber_grid2D.hpp>
#include <biomesh_json_parser.hpp>

int main(int argc, char** argv)
{
  biomesh::vector_field field(argv[1]);

  field.load_vtk_grid();

  biomesh::fiber_grid2D fg(argv[2]);
  fg.generate_fiber_grid(field, 4);

  //biomesh::json_parser::export_fiber_grid_json();

  return EXIT_SUCCESS;
}