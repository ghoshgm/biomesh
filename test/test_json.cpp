
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>

int main(int argc, char** argv)
{
  std::ifstream file(argv[1]);
  assert(file.is_open());

  Json::Value val;
  Json::Reader reader;

  reader.parse(file,val);

  std::cout << val << std::endl;
  std::cout << val["x"] << std::endl;
  std::cout << val["y"] << std::endl;
  std::cout << val["z"] << std::endl;

  return EXIT_SUCCESS;
}