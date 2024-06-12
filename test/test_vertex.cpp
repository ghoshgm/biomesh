
#include <biomesh_vertex2d.hpp>
#include <biomesh_vertex3d.hpp>
#include <cmath>
#include <iostream>

using vertex3D = biomesh::vertex3D;
using vertex2D = biomesh::vertex2D;

int main()
{
  /* Test for zero initialization. */
  vertex2D v1;
  vertex3D v2;
  assert( v1('x') == 0.0 && v1('y') == 0.0 && v1('z') == 0.0 );
  assert( v2('x') == 0.0 && v2('y') == 0.0 && v2('z') == 0.0 );

  /* Test for non-zero initialization. */
  vertex2D v3(1.1,2.2345);
  vertex3D v4(1.1,2.2345,4.356);
  assert( v3('x') == 1.1 && v3('y') == 2.2345 && v3('z') == 0.0 );
  assert( v4('x') == 1.1 && v4('y') == 2.2345 && v4('z') == 4.356 );

  /* Test for equality. */
  assert(!(v1 == v3));
  assert(!(v2 == v4));
  vertex3D v5(0.99,2.0988,5.78889);
  vertex3D v6(0.99,2.0988,5.78889);
  assert(v5 == v6);

  /* Test for getter. */
  std::cout << v1('x') << " " << v1('y') << " " << v1('z') << std::endl;
  std::cout << v4('x') << " " << v4('y') << " " << v4('z') << std::endl;

  return EXIT_SUCCESS;
}