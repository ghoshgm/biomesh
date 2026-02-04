
#include "biomesh_stopwatch.hpp"

namespace biomesh
{

stopwatch::stopwatch () {}

stopwatch::~stopwatch () {}

void
stopwatch::start ()
{
  /* Start measuring CPU time. */
  m_cstart = std::clock ();

  /* Start measruing Wall time. */
  m_wstart = std::chrono::high_resolution_clock::now ();
}

void
stopwatch::end ()
{
  /* Stop measuring CPU time. */
  m_cend = std::clock ();
  auto cspan = 1000.0 * (m_cend - m_cstart) / CLOCKS_PER_SEC;

  /* Stop measuring Wall time. */
  m_wend = std::chrono::high_resolution_clock::now ();
  auto wspan = std::chrono::duration_cast<
      std::chrono::duration<double, std::ratio<1, 1000> > > (m_wend
                                                             - m_wstart);

  BIOMESH_LINFO ("Wall time = " + std::to_string (wspan.count ()) + "ms" + "  "
                 + "CPU time = " + std::to_string (cspan) + "ms");
}

}