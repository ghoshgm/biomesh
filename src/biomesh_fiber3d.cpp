
#include <biomesh_fiber3d.hpp>

namespace biomesh
{
fiber3D::fiber3D (size_t gpoint_count) : m_gpoint_count{ gpoint_count }
{
  m_fiber_vertices.reserve (m_gpoint_count);
  m_fiber_vertices.emplace_back (m_seed);
}

fiber3D::fiber3D (const vertex3D &seed, size_t gpoint_count)
    : m_seed{ seed }, m_gpoint_count{ gpoint_count }
{
  m_fiber_vertices.reserve (m_gpoint_count);
  m_fiber_vertices.emplace_back (m_seed);
}

fiber3D::fiber3D (const fiber3D &other)
{
  this->m_seed = other.m_seed;
  this->m_fiber_vertices = other.m_fiber_vertices;
}

fiber3D::fiber3D (fiber3D &&other)
{
  this->m_seed = other.m_seed;
  this->m_fiber_vertices = std::move (other.m_fiber_vertices);
}

fiber3D::~fiber3D () {}

int
fiber3D::generate_fiber ()
{
}

size_t
fiber3D::size () const
{
  return m_gpoint_count;
}

vertex3D
fiber3D::operator[] (int idx) const
{
  BIOMESH_ASSERT (idx >= 0 && idx < m_gpoint_count);
  return m_fiber_vertices[idx];
}

bool
fiber3D::operator== (const fiber3D &other) const
{
  return this->m_seed == other.m_seed;
}

} // namespace biomesh