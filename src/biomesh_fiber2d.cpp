
#include <biomesh_fiber2d.hpp>

namespace biomesh
{
fiber2D::fiber2D () {}

fiber2D::fiber2D (const vertex2D &seed) : m_seed{ seed } {}

fiber2D::fiber2D (const fiber2D &other)
{
  this->m_seed = other.m_seed;
  this->m_fiber_vertices = other.m_fiber_vertices;
}

fiber2D::fiber2D (fiber2D &&other)
{
  this->m_seed = other.m_seed;
  this->m_fiber_vertices = std::move (other.m_fiber_vertices);
}

fiber2D::~fiber2D () {}

int
fiber2D::generate_fiber ()
{
}

} // namespace biomesh