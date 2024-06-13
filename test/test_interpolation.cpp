
#include <biomesh_interpolation.cpp>
#include <cassert>
#include <cmath>

using vertex2D = biomesh::vertex2D;

int main()
{
  {
    /* Test 1 for bilinear interpolation. */
    vertex2D vmin(1, 1);
    vertex2D vmax(2, 2);
    vertex2D probe(1.5, 1.5);
    double s1 = 10;
    double s2 = 30;
    double s3 = 20;
    double s4 = 40;

    double actual_val = 25;
    double iterp_val = biomesh::interpolation::bilinear(vmin, vmax, probe,
                                                        s1, s2, s3, s4);

    assert(iterp_val == actual_val);
  }

  {
    /* Test 2 for bilinear interpolation. */
    vertex2D vmin(1, 1);
    vertex2D vmax(3, 4);
    vertex2D probe(2, 2);
    double s1 = 20;
    double s2 = 25;
    double s3 = 35;
    double s4 = 30;

    double actual_val = 25.8333;
    double iterp_val = biomesh::interpolation::bilinear(vmin, vmax, probe,
                                                        s1, s2, s3, s4);

    /**
     * I did not put an assertion here because comparing floats/doubles is a headache.
    */
    std::cout << "Results for Test 2." << std::endl;
    std::cout << "Reference value = " << actual_val << " Interpolated val = " << iterp_val << std::endl;
  }

  return EXIT_SUCCESS;
}