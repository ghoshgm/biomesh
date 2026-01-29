
#include <biomesh_seeder.hpp>

namespace biomesh
{
seeder::seeder (size_t seed_count) : m_seed_count{ seed_count }
{
  m_seeds.reserve (m_seed_count);
}

seeder::~seeder () {}

vertex3D
seeder::operator[] (size_t index) const
{
  BIOMESH_ASSERT (index >= 0 and index < m_seed_count);
  return m_seeds[index];
}

void
seeder::generate_seeds (const vector_field &vfield)
{
}

seeder::iterator
seeder::begin ()
{
  return iterator (&m_seeds[0]);
}

seeder::iterator
seeder::end ()
{
  return iterator (&m_seeds[m_seed_count]);
}
}