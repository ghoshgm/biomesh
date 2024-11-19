
#ifndef BIOMESH_INTERPOLATION_HPP
#define BIOMESH_INTERPOLATION_HPP

#include <array>
#include <biomesh_base.hpp>
#include <biomesh_vertex2d.hpp>
#include <biomesh_vertex3d.hpp>
#include <cmath>

/**
 * File for interpolation methods in 2D/3D.
 */

namespace biomesh
{

namespace interpolation
{

/**
 * Function for bilinear interpolation on an unit square.
 *
 * The vertex ordering is conformal to VTK_QUAD ordering.
 *
 * The input vertex 'probe' must be in the parametric space.
 *
 * @param[in] probe The vertex at which interpolation needs to be performed.
 * @param[in] scalars The scalar magnitude at the vertices.
 *
 * @return The interpolated scalar at the probe.
 */
double bilinear (const vertex2D &probe, std::array<double, 4> &scalars);

/**
 * Function for trilinear interpolation on an unit cube.
 *
 * The vertex ordering is conformal to VTK_HEXAHEDRON ordering.
 *
 * The input vertex 'probe' must be in the parametric space.
 *
 * @param[in] probe The vertex at which interpolation needs to be performed.
 * @param[in] scalars The scalar magnitude at the vertices.
 *
 * @return The interpolated scalar at the probe.
 */
double trilinear (const vertex3D &probe, std::array<double, 8> &scalars);

} // namespace interpolation.

} // namespace biomesh

#endif