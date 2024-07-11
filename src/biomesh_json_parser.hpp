
#ifndef BIOMESH_JSON_PARSER_HPP
#define BIOMESH_JSON_PARSER_HPP

#include <fstream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>

#include <biomesh_base.hpp>

namespace biomesh
{

class json_parser
{
private:
  Json::Value m_data;
  std::string m_file_name;

public:
  json_parser (const std::string &file_name);

  ~json_parser ();

  int read ();

  Json::Value get_json_data () const;
};

}

#endif