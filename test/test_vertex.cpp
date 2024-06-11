
#include <biomesh_vertex2d.hpp>
#include <biomesh_vertex3d.hpp>
#include <cmath>
#include <iostream>

using vertex3D = biomesh::vertex3D;
using vertex2D = biomesh::vertex2D;

int main()
{
  /* Test for equality of two vertices. */
  vertex3D v1(1.889,2.1 ,3.4899);
  vertex3D v2(1.89 ,2.09,3.499);
  assert(!(v1 == v2));

  vertex2D v3(1.889,2.1);
  vertex2D v4(1.889,2.1);
  assert((v3 == v4));

  /* Test for data initialization. */
  std::cout << v1('x') << std::endl;
  std::cout << v1('y') << std::endl;
  std::cout << v1('z') << std::endl;

  return EXIT_SUCCESS;
}