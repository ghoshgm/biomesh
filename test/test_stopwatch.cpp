
#include <biomesh_stopwatch.hpp>

int main()
{
  biomesh::stopwatch sw;

  sw.start();
  for(int i = 0; i < 10e8; ++i)
  {}
  sw.end();

  return EXIT_SUCCESS;
}