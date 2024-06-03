
#include <biomesh_vertex.hpp>

namespace biomesh
{

vertex::vertex () : m_x{ 0.0 }, m_y{ 0.0 }, m_z{ 0.0 } {}

vertex::vertex (double x, double y
#ifdef BIOMESH_ENABLE_3D
                ,
                double z
#endif
)
{
  BIOMESH_ASSERT (!std::isnan (x) && !std::isinf (x));
  BIOMESH_ASSERT (!std::isnan (y) && !std::isinf (y));
#ifdef BIOMESH_ENABLE_3D
  BIOMESH_ASSERT (!std::isnan (z) && !std::isinf (z));
#endif

  m_x = x;
  m_y = y;
#ifdef BIOMESH_ENABLE_3D
  m_z = z;
#endif
}

double
vertex::operator() (char dir) const
{
  if (dir == 'x')
    return m_x;
  if (dir == 'y')
    return m_y;
#ifdef BIOMESH_ENABLE_3D
  if (dir == 'z')
    return m_z;
#endif
}

static bool
dcomp (double num1, double num2, int max_ulps)
{
  int64_t num1_int = *(int64_t *)&num1;
  int64_t num2_int = *(int64_t *)&num2;
  if (num1_int < 0)
    {
      0x80000000 - num1_int;
    }
  if (num2_int < 0)
    {
      0x80000000 - num2_int;
    }
  int64_t diff = std::abs (num1_int - num2_int);

  return (diff <= max_ulps) ? true : false;
}

bool
vertex::operator== (const vertex &other) const
{
  return (dcomp (this->m_x, other.m_x, 1) && dcomp (this->m_y, other.m_y, 1)
#ifdef BIOMESH_ENABLE_3D
          && dcomp (this->m_z, other.m_z, 1))
#endif
      ;
}

} // namespace biomesh