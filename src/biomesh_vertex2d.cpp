
#include <biomesh_vertex2d.hpp>

namespace biomesh
{

vertex2D::vertex2D () {}

vertex2D::vertex2D (double x, double y)
{
  m_position (0) = x;
  m_position (1) = y;
}

vertex2D::vertex2D (double x, double y, double z)
{
  m_position (0) = x;
  m_position (1) = y;
  m_position (2) = z;
}

vertex2D::~vertex2D () {}

void
vertex2D::scale (double scaling_factor)
{
  if (scaling_factor > 0.0)
    {
      m_position (0) += scaling_factor;
      m_position (1) += scaling_factor;
    }
  else if (scaling_factor < 0.0)
    {
      m_position (0) -= std::fabs (scaling_factor);
      m_position (1) -= std::fabs (scaling_factor);
    }
}

void
vertex2D::scale (char dir, double scaling_factor)
{
  BIOMESH_ASSERT (dir == 'x' || dir == 'y');
  if (dir == 'x' && scaling_factor > 0.0)
    m_position (0) += scaling_factor;
  if (dir == 'x' && scaling_factor < 0.0)
    m_position (0) -= std::fabs (scaling_factor);
  if (dir == 'y' && scaling_factor > 0.0)
    m_position (1) += scaling_factor;
  if (dir == 'y' && scaling_factor < 0.0)
    m_position (1) -= std::fabs (scaling_factor);
}

}