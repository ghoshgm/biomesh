
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

void
vertex3D::scale (double scaling_factor)
{
  if (scaling_factor > 0.0)
    {
      m_position (0) += scaling_factor;
      m_position (1) += scaling_factor;
      m_position (2) += scaling_factor;
    }
  else if (scaling_factor < 0.0)
    {
      m_position (0) -= std::fabs (scaling_factor);
      m_position (1) -= std::fabs (scaling_factor);
      m_position (2) -= std::fabs (scaling_factor);
    }
}

void
vertex3D::scale (char dir, double scaling_factor)
{
  BIOMESH_ASSERT (dir == 'x' || dir == 'y' || dir == 'z');
  if (dir == 'x' && scaling_factor > 0.0)
    m_position (0) += scaling_factor;
  if (dir == 'x' && scaling_factor < 0.0)
    m_position (0) -= std::fabs (scaling_factor);
  if (dir == 'y' && scaling_factor > 0.0)
    m_position (1) += scaling_factor;
  if (dir == 'y' && scaling_factor < 0.0)
    m_position (1) -= std::fabs (scaling_factor);
  if (dir == 'z' && scaling_factor > 0.0)
    m_position (2) += scaling_factor;
  if (dir == 'z' && scaling_factor < 0.0)
    m_position (2) -= std::fabs (scaling_factor);
}

}