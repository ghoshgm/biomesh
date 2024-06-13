
#include <biomesh_interpolation.hpp>

namespace biomesh
{

namespace interpolation
{

double
bilinear (const vertex2D &vertex_min, const vertex2D &vertex_max,
          const vertex2D &probe, double scalar1, double scalar2,
          double scalar3, double scalar4)
{
  double xmax_diff = vertex_max ('x') - probe ('x');
  double xmin_diff = probe ('x') - vertex_min ('x');
  Eigen::Matrix<double, 1, 2> x_vec{ { xmax_diff, xmin_diff } };

  double ymax_diff = vertex_max ('y') - probe ('y');
  double ymin_diff = probe ('y') - vertex_min ('y');
  Eigen::Matrix<double, 2, 1> y_vec{ { ymax_diff }, { ymin_diff } };

  Eigen::Matrix2d scalars;
  scalars (0, 0) = scalar1;
  scalars (0, 1) = scalar3;
  scalars (1, 0) = scalar2;
  scalars (1, 1) = scalar4;

  double xdiff = vertex_max ('x') - vertex_min ('x');
  double ydiff = vertex_max ('y') - vertex_min ('y');

  return (1 / (xdiff * ydiff)) * x_vec * scalars * y_vec;
}

} // namespace interpolation.

} // namespace biomesh