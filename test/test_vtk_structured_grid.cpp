
#include <biomesh_vector_field.hpp>

int main(int argc, char** argv)
{
  biomesh::vector_field field(argv[1]);

  field.load_vtk_grid();

  return EXIT_SUCCESS;
}