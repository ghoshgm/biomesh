
#ifndef BIOMESH_STOPWATCH_HPP
#define BIOMESH_STOPWATCH_HPP

#include <biomesh_base.hpp>

#include <chrono>

namespace biomesh
{

using time_point = std::chrono::high_resolution_clock::time_point;

class stopwatch
{
public:
  /**
   * Constructor.
   */
  stopwatch ();

  /**
   * Destructor.
   */
  ~stopwatch ();

  /**
   * Start the stopwatch.
   */
  void start ();

  /**
   * End the stopwatch.
   * This function prints the wall time to the console.
   */
  void end ();

private:
  time_point m_start;
  time_point m_end;
};

} // namespace biomesh

#endif