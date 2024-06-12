
#include <iostream>
#include <Eigen/Dense>
#include <cassert>

int main()
{
  Eigen::Vector2d v1(0.99,2.0);
  Eigen::Vector2d v2(0.998,2.0);

  assert(v1 != v2);

  return EXIT_SUCCESS;
}