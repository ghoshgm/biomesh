
#include <biomesh_interpolation.hpp>
#include <cassert>
#include <cmath>
#include <array>

using vertex2D = biomesh::vertex2D;
using vertex3D = biomesh::vertex3D;

int main()
{
  {
    vertex2D probe(0.5, 0.5);
    std::array<double,4> s{10,20,30,40};

    double actual_val = 100 / 4;
    double iterp_val = biomesh::interpolation::bilinear(probe, s);
    assert(actual_val == iterp_val);
  }

  {
    vertex3D probe(0.5, 0.5, 0.5);
    std::array<double,8> s {10,20,30,40,50,60,70,80};
  
    double actual_val = 0.125 * (s[0] + s[1] + s[2] + s[3] + s[4] + s[5] + s[6] + s[7]);
    double res = biomesh::interpolation::trilinear(probe, s);
    assert(res == actual_val);
  }

  return EXIT_SUCCESS;
}