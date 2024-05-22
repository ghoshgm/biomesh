
#include <biomesh_vertex.hpp>
#include <cmath>
#include <iostream>

using vertex = biomesh::vertex;

int main()
{
  /* Test for equality of two vertices. */
  vertex v1(1.889,2.1,3.4899);
  vertex v2(1.89,2.09,3.499);
  assert(!(v1 == v2));

  /* Test getter. */
  std::cout << v1('x') << std::endl;
  assert(v1('x') == 1.889);
  std::cout << v1('y') << std::endl;
  assert(v1('y') == 2.1);
  std::cout << v1('z') << std::endl;
  assert(v1('z') == 3.4899);

  return EXIT_SUCCESS;
}