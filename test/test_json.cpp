
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

  return EXIT_SUCCESS;
}