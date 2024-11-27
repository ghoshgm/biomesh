
#include "biomesh_stopwatch.hpp"

namespace biomesh
{

stopwatch::stopwatch () {}

stopwatch::~stopwatch () {}

void
stopwatch::start ()
{
  m_start = std::chrono::high_resolution_clock::now ();
}

void
stopwatch::end ()
{
  m_end = std::chrono::high_resolution_clock::now ();
  auto span = std::chrono::duration_cast<
      std::chrono::duration<double, std::milli> > (m_end - m_start);
  BIOMESH_LINFO ("Wall time = " + std::to_string (span.count ()) + "ms");
}

}