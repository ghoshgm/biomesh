
#include <biomesh_vertex_base.hpp>

namespace biomesh
{

vertex::vertex () : m_position (0.0, 0.0, 0.0) {}

vertex::~vertex () {}

double
vertex::operator() (char dir) const
{
  BIOMESH_ASSERT (dir == 'x' || dir == 'y' || dir == 'z');
  if (dir == 'x')
    return m_position (0);
  if (dir == 'y')
    return m_position (1);
  if (dir == 'z')
    return m_position (2);

  return std::numeric_limits<double>::max ();
}

bool
vertex::operator== (const vertex &other) const
{
  return (this->m_position == other.m_position);
}

void
vertex::operator= (const vertex &other)
{
  m_position = other.m_position;
}

void
vertex::scale (double scaling_factor, int scale_up)
{
  BIOMESH_ASSERT (scale_up == 1 || scale_up == 0)
  if (scale_up == 1)
    m_position *= scaling_factor;
  else if(scale_up == 0)
    m_position /= scaling_factor;
}

void
vertex::print ()
{
  std::cout << "x: " << m_position (0) << " y: " << m_position (1)
            << " z: " << m_position (2) << std::endl;
}

} // namespace biomesh