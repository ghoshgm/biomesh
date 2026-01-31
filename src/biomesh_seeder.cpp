
#include <biomesh_seeder.hpp>

namespace biomesh
{
seeder::seeder (size_t seed_count) : m_seed_count{ seed_count }
{
  m_seeds.reserve (m_seed_count);
}

seeder::~seeder () {}

const vertex3D &
seeder::operator[] (size_t index) const
{
  BIOMESH_ASSERT ((index >= 0 and index < m_seed_count));
  return m_seeds[index];
}

void
seeder::generate_seeds (const vector_field &vfield, seed_plane &splane)
{
  BIOMESH_LINFO ("Seed generation begin.");
  std::vector<double> cumulative_areas;
  double total_area = 0.0;

  std::for_each (splane.begin (), splane.end (),
                 [&, this] (vtkTriangle *cell) {
#if 1
                   // vtkTriangle *cell = &c;
                   double p0[3], p1[3], p2[3];
                   cell->GetPoints ()->GetPoint (0, p0);
                   cell->GetPoints ()->GetPoint (1, p1);
                   cell->GetPoints ()->GetPoint (2, p2);

                   double area = vtkTriangle::TriangleArea (p0, p1, p2);
                   total_area += area;

                   cumulative_areas.push_back (total_area);
#endif
                 });
  std::cout << "-----------------------" << std::endl;
  vtkNew<vtkPoints> sampledPoints;
  sampledPoints->SetNumberOfPoints (m_seed_count);

  vtkNew<vtkMinimalStandardRandomSequence> rng;
  rng->SetSeed (1);
#if 0
  for (vtkIdType i = 0; i < m_seed_count; ++i)
    {
      rng->Next ();
      double r = rng->GetValue () * total_area;

      vtkIdType tid = std::lower_bound (cumulative_areas.begin (),
                                        cumulative_areas.end (), r)
                      - cumulative_areas.begin ();

      vtkTriangle &cell = splane[tid];

      double p0[3], p1[3], p2[3];
      (&cell)->GetPoints ()->GetPoint (0, p0);
      (&cell)->GetPoints ()->GetPoint (1, p1);
      (&cell)->GetPoints ()->GetPoint (2, p2);

      rng->Next ();
      double u = rng->GetValue ();
      rng->Next ();
      double v = rng->GetValue ();

      if (u + v > 1.0)
        {
          u = 1.0 - u;
          v = 1.0 - v;
        }

      double w = 1.0 - u - v;

      double x[3] = { w * p0[0] + u * p1[0] + v * p2[0],
                      w * p0[1] + u * p1[1] + v * p2[1],
                      w * p0[2] + u * p1[2] + v * p2[2] };

      vertex3D seed (x[0], x[1], x[2]);
      m_seeds.push_back (seed);

      sampledPoints->SetPoint (i, x);
    }
#endif
  BIOMESH_LINFO ("Seed generation end.");
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