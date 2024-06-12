
#include <biomesh_interpolation.cpp>
#include <cassert>

using vertex2D = biomesh::vertex2D;

int main()
{
  /* Test for bilinear interpolation. */
  vertex2D vmin(1,1);
  vertex2D vmax(2,2);
  vertex2D probe(1.5,1.5);
  double s1 = 10;
  double s2 = 30;
  double s3 = 20;
  double s4 = 40;

  double iterp_val = biomesh::interpolation::bilinear(vmin,vmax,probe,
                                                      s1,s2,s3,s4);

  assert(iterp_val == 25);

  return EXIT_SUCCESS;
}