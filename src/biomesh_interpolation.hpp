
#ifndef BIOMESH_INTERPOLATION_HPP
#define BIOMESH_INTERPOLATION_HPP

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
 * Function for bilinear interpolation on a 2D rectangle.
 *
 * The numbering is assumed to be CCW.
 * The start is assumed to be the lower left vertex of the rectangle.
 * The lower left vertex should have the lowest X,Y coordinates.
 *
 * @param[in] vertex_min The vertex with the lowest X,Y coorindates.
 * @param[in] vertex_max The vertex with the highest X,Y coorindates.
 * @param[in] probe The vertex at which interpolation needs to be performed.
 * @param[in] scalar1 The scalar magnitude at vertex 1.
 * @param[in] scalar2 The scalar magnitude at vertex 2.
 * @param[in] scalar3 The scalar magnitude at vertex 3.
 * @param[in] scalar4 The scalar magnitude at vertex 4.
 *
 * @return The interpolated scalar at the probe.
 */
double bilinear (const vertex2D &vertex_min, const vertex2D &vertex_max,
                 const vertex2D &probe, double scalar1, double scalar2,
                 double scalar3, double scalar4);

} // namespace interpolation.

} // namespace biomesh

#endif