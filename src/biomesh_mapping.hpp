
#ifndef BIOMESH_MAPPING_HPP
#define BIOMESH_MAPPING_HPP

#include <Eigen/Dense>
#include <array>
#include <memory>
#include <petsc.h>

#include <biomesh_vertex2d.hpp>
#include <biomesh_vertex3d.hpp>

namespace biomesh
{

namespace mapping
{

/**
 * Function to map parametric coordinates to cartesian coordiantes.
 *
 * The ordering of the vertices conforms to the VTK_HEXAHEDRON convention.
 * For 2D mapping, v4,v5,v6,v7 in the 'vertices' array must be zeros.
 *
 * @param[in] parametric_coords The parametric coordiantes that need to be
 * mapped.
 * @param[in] vertices The vertices of the hexahedron.
 *
 * @return The mapped cartesian coordinates.
 */
template <class vertex>
vertex isoparametric (const vertex &parametric_coords,
                      std::array<vertex, 8> &vertices);

/**
 * Function to map cartesian coordinates to parametric coordiantes.
 *
 * The ordering of the vertices conforms to the VTK_HEXAHEDRON convention.
 * For 2D mapping, v4,v5,v6,v7 in the 'vertices' array must be zeros.
 *
 * @param[in] cartesian_coords The cartesian coordiantes that need to be
 * mapped.
 * @param[in] vertices The vertices of the hexahedron.
 *
 * @return The mapped cartesian coordinates.
 */
vertex3D inverse_isoparametric_3d (const vertex3D &cartesian_coords,
                                   std::array<vertex3D, 8> &vertices);

#include "biomesh_mapping.tpp"

} // namespace linear_mapping

} // namespace biomesh

#endif