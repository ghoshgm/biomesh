
#include <iostream>
#include <cassert>

#include <biomesh_mapping.hpp>

using namespace biomesh;

int main()
{
  /* Test for 2D isoparametric mapping for unit square. */
  {
    vertex2D v0(0, 0);
    vertex2D v1(1, 0);
    vertex2D v2(1, 1);
    vertex2D v3(0, 1);
    vertex2D zero(0, 0);
    std::array<vertex2D, 8> vertices{v0, v1, v2, v3, zero, zero, zero, zero};

    vertex2D pcoords(0.5, 0.5);
    vertex2D ref_result(0.5, 0.5);
    vertex2D result = mapping::isoparametric<vertex2D>(pcoords, vertices);
    assert(result == ref_result);
  }

  /* Test for 3D isoparametric mapping for unit cube. */
  {
    vertex3D v0(0, 0, 0);
    vertex3D v1(1, 0, 0);
    vertex3D v2(1, 1, 0);
    vertex3D v3(0, 1, 0);
    vertex3D v4(0, 0, 1);
    vertex3D v5(1, 0, 1);
    vertex3D v6(1, 1, 1);
    vertex3D v7(0, 1, 1);
    std::array<vertex3D, 8> vertices{v0, v1, v2, v3, v4, v5, v6, v7};

    vertex3D pcoords(0.5, 0.5, 0.5);
    vertex3D ref_result(0.5, 0.5, 0.5);
    vertex3D result = mapping::isoparametric<vertex3D>(pcoords, vertices);
    assert(result == ref_result);
  }

  /* Test for 2D isoparametric mapping for quadrilateral. */
  {
    vertex2D v0(0, 0);
    vertex2D v1(2, 0);
    vertex2D v2(3, 1);
    vertex2D v3(1, 1);
    vertex2D zero(0, 0);
    std::array<vertex2D, 8> vertices{v0, v1, v2, v3, zero, zero, zero, zero};

    vertex2D pcoords(0.5, 0.5);
    vertex2D ref_result(1.5, 0.5);
    vertex2D result = mapping::isoparametric<vertex2D>(pcoords, vertices);
    assert(result == ref_result);
  }

  /* Test for 3D isoparametric mapping for prism. */
  {
    vertex3D v0(0, 0, 0);
    vertex3D v1(2, 0, 0);
    vertex3D v2(2, 1, 0);
    vertex3D v3(0, 1, 1);
    vertex3D v4(1, 0, 1);
    vertex3D v5(3, 0, 1);
    vertex3D v6(3, 1, 1);
    vertex3D v7(1, 1, 1);
    std::array<vertex3D, 8> vertices{v0, v1, v2, v3, v4, v5, v6, v7};

    vertex3D pcoords(0.5, 0.5, 0.5);
    vertex3D ref_result(1.5, 0.5, 0.625);
    vertex3D result = mapping::isoparametric<vertex3D>(pcoords, vertices);
    assert(result == ref_result);
  }

  return EXIT_SUCCESS;
}