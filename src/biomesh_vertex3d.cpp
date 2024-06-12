
#include <biomesh_vertex3d.hpp>

namespace biomesh
{

vertex3D::vertex3D () {}

vertex3D::vertex3D (double x, double y, double z)
{
  m_position (0) = x;
  m_position (1) = y;
  m_position (2) = z;
}

vertex3D::~vertex3D () {}

}