
#include <biomesh_vertex2d.hpp>

namespace biomesh
{

vertex2D::vertex2D () {}

vertex2D::vertex2D (double x, double y)
{
  m_position (0) = x;
  m_position (1) = y;
}

vertex2D::~vertex2D () {}

}