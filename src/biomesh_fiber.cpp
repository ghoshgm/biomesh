
#include <biomesh_fiber.hpp>

namespace biomesh
{

fiber::fiber (const vertex &start_point) : seed{ start_point } {}

fiber::fiber (const fiber &other)
{
  seed = other.seed;
  m_vset = other.m_vset;
}

fiber::fiber (fiber &&other)
{
  seed = other.seed;
  m_vset = std::move (other.m_vset);
}

std::vector<vertex>
fiber::get_vertices () const
{
  return m_vset;
}

vertex
fiber::operator[] (size_t index) const
{
  return m_vset[index];
}

} // namespace biomesh