
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

/**
 * Function for bilinear interpolation on an unit square.
 *
 * The vertex ordering is conformal to VTK_QUAD ordering.
 *
 * The input vertex 'probe' must be in the parametric space.
 *
 * @param[in] probe The vertex at which interpolation needs to be performed.
 * @param[in] scalar0 The scalar magnitude at vertex 0.
 * @param[in] scalar1 The scalar magnitude at vertex 1.
 * @param[in] scalar2 The scalar magnitude at vertex 2.
 * @param[in] scalar3 The scalar magnitude at vertex 3.
 *
 * @return The interpolated scalar at the probe.
 */
double bilinear (const vertex2D &probe, double scalar0, double scalar1,
                 double scalar2, double scalar3);

/**
 * Function for trilinear interpolation on an unit cube.
 *
 * The vertex ordering is conformal to VTK_HEXAHEDRON ordering.
 *
 * The input vertex 'probe' must be in the parametric space.
 *
 * @param[in] probe The vertex at which interpolation needs to be performed.
 * @param[in] scalar0 The scalar magnitude at vertex 0.
 * @param[in] scalar1 The scalar magnitude at vertex 1.
 * @param[in] scalar2 The scalar magnitude at vertex 2.
 * @param[in] scalar3 The scalar magnitude at vertex 3.
 * @param[in] scalar4 The scalar magnitude at vertex 4.
 * @param[in] scalar5 The scalar magnitude at vertex 5.
 * @param[in] scalar6 The scalar magnitude at vertex 6.
 * @param[in] scalar7 The scalar magnitude at vertex 7.
 *
 * @return The interpolated scalar at the probe.
 */
double trilinear (const vertex3D &probe, double scalar0, double scalar1,
                  double scalar2, double scalar3, double scalar4,
                  double scalar5, double scalar6, double scalar7);

} // namespace interpolation.

} // namespace biomesh

#endif