
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <biomesh_json_parser.hpp>

int main(int argc, char** argv)
{
  biomesh::json_parser jp(argv[1]);
  int ret = jp.read();
  assert(ret == true);

  auto data = jp.get_json_string();
  std::cout << data["seed_points"].size() << std::endl;

  std::cout << data["seed_points"][0]["x"] << std::endl;
  std::cout << data["seed_points"][0]["y"] << std::endl;
  std::cout << data["seed_points"][0]["z"] << std::endl;

  std::cout << data["seed_points"][1]["x"] << std::endl;
  std::cout << data["seed_points"][1]["y"] << std::endl;
  std::cout << data["seed_points"][1]["z"] << std::endl;

  return EXIT_SUCCESS;
}