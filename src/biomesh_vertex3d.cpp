
#include <biomesh_vertex3d.hpp>

namespace biomesh
{

vertex3D::vertex3D (double x, double y, double z)
{
  m_x = x;
  m_y = y;
  m_z = z;
}

vertex3D::~vertex3D () {}

}