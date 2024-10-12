
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
  scalars (0, 1) = scalar4;
  scalars (1, 0) = scalar2;
  scalars (1, 1) = scalar3;

  double xdiff = vertex_max ('x') - vertex_min ('x');
  double ydiff = vertex_max ('y') - vertex_min ('y');
  BIOMESH_ASSERT (xdiff > 0.0);
  BIOMESH_ASSERT (ydiff > 0.0);
  BIOMESH_ASSERT (std::isinf (1 / (xdiff * ydiff)) == false);

  return (1 / (xdiff * ydiff)) * x_vec * scalars * y_vec;
}

double
bilinear (const vertex2D &probe, double scalar0, double scalar1,
          double scalar2, double scalar3)
{
  double interp_res = 0.0;

  BIOMESH_ASSERT (probe ('x') <= 1.0 && probe ('x') >= 0.0);
  BIOMESH_ASSERT (probe ('y') <= 1.0 && probe ('y') >= 0.0);

  /* Compute interpolation weights. */
  double w0 = probe ('x') * probe ('y');
  double w1 = (1.0 - probe ('x')) * probe ('y');
  double w2 = (1.0 - probe ('x')) * (1.0 - probe ('y'));
  double w3 = probe ('x') * (1.0 - probe ('y'));
  BIOMESH_ASSERT ((w0 + w1 + w2 + w3) == 1.0);

  /* Interpolate. */
  interp_res
      = (w0 * scalar0) + (w1 * scalar1) + (w2 * scalar2) + (w3 * scalar3);

  return interp_res;
}

double
trilinear (const vertex3D &probe, double scalar1, double scalar2,
           double scalar3, double scalar4, double scalar5, double scalar6,
           double scalar7, double scalar8)
{
  double interp_res = 0.0;

  BIOMESH_ASSERT (probe ('x') <= 1.0 && probe ('x') >= 0.0);
  BIOMESH_ASSERT (probe ('y') <= 1.0 && probe ('y') >= 0.0);
  BIOMESH_ASSERT (probe ('z') <= 1.0 && probe ('z') >= 0.0);

  /* Compute interpolation weights. */
  double w0 = (1.0 - probe ('x')) * (1.0 - probe ('y')) * (1.0 - probe ('z'));
  double w1 = probe ('x') * (1.0 - probe ('y')) * (1.0 - probe ('z'));
  double w2 = probe ('x') * probe ('y') * (1.0 - probe ('z'));
  double w3 = (1.0 - probe ('x')) * probe ('y') * (1.0 - probe ('z'));
  double w4 = (1.0 - probe ('x')) * (1.0 - probe ('y')) * probe ('z');
  double w5 = probe ('x') * (1.0 - probe ('y')) * probe ('z');
  double w6 = probe ('x') * probe ('y') * probe ('z');
  double w7 = (1.0 - probe ('x')) * probe ('y') * probe ('z');
  BIOMESH_ASSERT ((w0 + w1 + w2 + w3 + w4 + w5 + w6 + w7) == 1.0);

  /* Interpolate. */
  interp_res = (w0 * scalar1) + (w1 * scalar2) + (w2 * scalar3)
               + (w3 * scalar4) + (w4 * scalar5) + (w5 * scalar6)
               + (w6 * scalar7) + (w7 * scalar8);

  return interp_res;
}

} // namespace interpolation.

} // namespace biomesh