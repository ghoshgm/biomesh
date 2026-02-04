
#ifndef BIOMESH_STOPWATCH_HPP
#define BIOMESH_STOPWATCH_HPP

#include <biomesh_base.hpp>

#include <chrono>
#include <ctime>

namespace biomesh
{
/**
 * @brief Class for measuring wall time and CPU time.
 */

class stopwatch
{
public:
  using wtime_point = std::chrono::high_resolution_clock::time_point;
  using ctime_point = std::clock_t;

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
  ctime_point m_cstart;
  ctime_point m_cend;
  wtime_point m_wstart;
  wtime_point m_wend;
};

} // namespace biomesh

#endif