
#include <biomesh_json_parser.hpp>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

int
main (int argc, char **argv)
{
  biomesh::json_parser jp (argv[1]);
  int ret = jp.read ();
  assert (ret == BIOMESH_SUCCESS);

  return EXIT_SUCCESS;
}