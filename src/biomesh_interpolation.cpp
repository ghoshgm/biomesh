
#include <biomesh_interpolation.hpp>

namespace biomesh
{

namespace interpolation
{

double
bilinear (const vertex2D &probe, std::array<double, 4> &scalars)
{
  double interp_res = 0.0;

  BIOMESH_ASSERT (probe ('x') <= 1.0 && probe ('x') >= 0.0);
  BIOMESH_ASSERT (probe ('y') <= 1.0 && probe ('y') >= 0.0);

  /* Compute interpolation weights. */
  double w0 = (1.0 - probe ('x')) * (1.0 - probe ('y'));
  double w1 = probe ('x') * (1.0 - probe ('y'));
  double w2 = (1.0 - probe ('x')) * probe ('y');
  double w3 = probe ('x') * probe ('y');
  BIOMESH_ASSERT (std::abs ((w0 + w1 + w2 + w3) - 1.0) < 1e-8);

  /* Interpolate. */
  interp_res = (w0 * scalars[0]) + (w1 * scalars[1]) + (w2 * scalars[2])
               + (w3 * scalars[3]);

  return interp_res;
}

double
trilinear (const vertex3D &probe, std::array<double, 8> &scalars)
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
  BIOMESH_ASSERT (std::abs ((w0 + w1 + w2 + w3 + w4 + w5 + w6 + w7) - 1.0)
                  < 1e-8);

  /* Interpolate. */
  interp_res = (w0 * scalars[0]) + (w1 * scalars[1]) + (w2 * scalars[2])
               + (w3 * scalars[3]) + (w4 * scalars[4]) + (w5 * scalars[5])
               + (w6 * scalars[6]) + (w7 * scalars[7]);

  return interp_res;
}

} // namespace interpolation.

} // namespace biomesh