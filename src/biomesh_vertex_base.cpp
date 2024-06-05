
#include <biomesh_vertex_base.hpp>

namespace biomesh
{

vertex::vertex () : m_x{ 0.0 }, m_y{ 0.0 }, m_z{ 0.0 } {}

vertex::~vertex () {}

double
vertex::operator() (char dir) const
{
  if (dir == 'x')
    return m_x;
  if (dir == 'y')
    return m_y;
  if (dir == 'z')
    return m_z;

  return std::numeric_limits<double>::max ();
}

static bool
dcomp (double num1, double num2)
{
  int num1_int = *(int *)&num1;
  int num2_int = *(int *)&num2;
  if (num1_int < 0)
    num1_int = 0x80000000 - num1_int;
  if (num2_int < 0)
    num2_int = 0x80000000 - num2_int;

  return (std::abs (num1_int - num2_int) <= 1) ? true : false;
}

bool
vertex::operator== (const vertex &other) const
{
  return (dcomp (this->m_x, other.m_x) && dcomp (this->m_y, other.m_y)
          && dcomp (this->m_z, other.m_z));
}

} // namespace biomesh