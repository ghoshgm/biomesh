
#include <iostream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <fstream>
#include <string>

int main()
{
  std::ifstream file("read_sample.json");
  Json::Value val;
  Json::Reader reader;

  reader.parse(file,val);

  std::cout << "Data :" << val << std::endl;

  std::cout << "x: " << val["x"] << std::endl;
  std::cout << "y: " << val["y"] << std::endl;
  std::cout << "z: " << val["z"] << std::endl;

  return EXIT_SUCCESS;
}