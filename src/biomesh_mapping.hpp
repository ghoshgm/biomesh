
#ifndef BIOMESH_MAPPING_HPP
#define BIOMESH_MAPPING_HPP

#include <array>
#include <memory>

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

#include "biomesh_mapping.tpp"

} // namespace linear_mapping

} // namespace biomesh

#endif