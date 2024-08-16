
#include <iostream>
#include <biomesh_vector_field.hpp>
#include <biomesh_fiber_grid2D.hpp>

int main(int argc, char** argv)
{
  biomesh::vector_field field(argv[1]);

  field.load_vtk_grid();

  biomesh::fiber_grid2D fg(argv[2]);
  fg.generate_fiber_grid(field, 4);

  return EXIT_SUCCESS;
}