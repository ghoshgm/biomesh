
#include <biomesh_fiber3d.hpp>

namespace biomesh
{
fiber3D::fiber3D () {}

fiber3D::fiber3D (const vertex3D &seed) : m_seed{ seed } {}

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

} // namespace biomesh