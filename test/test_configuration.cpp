
#include <biomesh_configuration.hpp>
#include <cassert>

int main(int argc, char** argv)
{
  biomesh::configuration c(argv[1]);

  c.read_config_file();

  int vertex_count = c.get_value<int>("vertex_count");
  assert(vertex_count == 200);

  double vertex_width = c.get_value<double>("vertex_width");
  assert(vertex_width == 0.14);

  std::string integration_scheme = c.get_value<std::string>("integration_scheme");
  assert(integration_scheme == "runge-kutta4");

  int adaptive_steps_max = c.get_value<int>("adaptive_steps_max");
  assert(adaptive_steps_max == 1000);

  std::string strategy = c.get_value<std::string>("strategy");
  assert(strategy == "static");

  std::tuple<double,double,double> point = c.get_value<std::tuple<double,double,double>>("plane_point");
  assert(std::get<0>(point) == 0.0);
  assert(std::get<1>(point) == 1.0);
  assert(std::get<2>(point) == 2.0);

  std::tuple<double,double,double> normal = c.get_value<std::tuple<double,double,double>>("plane_normal");
  assert(std::get<0>(normal) == 0.0);
  assert(std::get<1>(normal) == 0.0);
  assert(std::get<2>(normal) == 1.0);

  std::string seed_file = c.get_value<std::string>("seed_file");
  assert(seed_file == "");

  return EXIT_SUCCESS;
}