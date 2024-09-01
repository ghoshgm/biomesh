
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

  /* Test for copy assignment. */
  vertex2D v2d_original(1.0,2.0);
  vertex2D v2d_copy;
  v2d_copy = v2d_original;
  assert(v2d_copy == v2d_original);

  vertex3D v3d_original(1.0,2.0,3.0);
  vertex3D v3d_copy;
  v3d_copy = v3d_original;
  assert(v3d_copy == v3d_original);

  /* Test for scaling operation. */
#if 0
  vertex2D v2d(1.0,2.0);
  v2d.scale(2.0);
  vertex2D v2d_up(2.0,4.0);
  assert(v2d == v2d_up);

  v2d.scale(-2.0);
  vertex2D v2d_down(1.0,2.0);
  assert(v2d == v2d_down);
  
  v2d.scale('x',2.0);
  vertex2D v2d_xup(2.0,2.0);
  assert(v2d == v2d_xup);

  v2d.scale('x',-2.0);
  vertex2D v2d_xdown(1.0,2.0);
  assert(v2d == v2d_xdown);

  v2d.scale('y',2.0);
  vertex2D v2d_yup(1.0,4.0);
  assert(v2d == v2d_yup);

  v2d.scale('y',-2.0);
  vertex2D v2d_ydown(1.0,2.0);
  assert(v2d == v2d_ydown);

  vertex3D v3d(1.0,2.0,3.0);
  v3d.scale(2.0);
  vertex3D v3d_up(2.0,4.0,6.0);
  assert(v3d == v3d_up);
  
  v3d.scale(-2.0);
  vertex3D v3d_down(1.0,2.0,3.0);
  assert(v3d == v3d_down);

  v3d.scale('x',2.0);
  vertex3D v3d_xup(2.0,2.0,3.0);
  assert(v3d == v3d_xup);

  v3d.scale('x',-2.0);
  vertex3D v3d_xdown(1.0,2.0,3.0);
  assert(v3d == v3d_xdown);

  v3d.scale('y',2.0);
  vertex3D v3d_yup(1.0,4.0,3.0);
  assert(v3d == v3d_yup);

  v3d.scale('y',-2.0);
  vertex3D v3d_ydown(1.0,2.0,3.0);
  assert(v3d == v3d_ydown);

  v3d.scale('z',2.0);
  vertex3D v3d_zup(1.0,2.0,6.0);
  assert(v3d == v3d_zup);

  v3d.scale('z',-2.0);
  vertex3D v3d_zdown(1.0,2.0,3.0);
  assert(v3d == v3d_zdown);
#endif

  /* Test for distance function. */
  vertex2D origin2d(0.0,0.0);
  vertex2D end2d(1.0,1.0);
  double dist2d = origin2d.distance(end2d);
  assert(std::sqrt(2) == dist2d);
  
  vertex3D origin3d(0.0,0.0,0.0);
  vertex3D end3d(1.0,1.0,1.0);
  double dist3d = origin3d.distance(end3d);
  assert(std::sqrt(3) == dist3d);
  
  return EXIT_SUCCESS;
}