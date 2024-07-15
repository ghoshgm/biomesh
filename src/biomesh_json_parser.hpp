
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
  /**
   * Constructor.
   *
   * @param[in] file_name The path to json file.
   */
  json_parser (const std::string &file_name);

  /**
   * Destructor.
   */
  ~json_parser ();

  /**
   * Function to read JSON file and store the data.
   */
  int read ();

  /**
   * Function to retrive the data object obtained from the JSON file.
   */
  Json::Value get_json_data () const;
};

}

#endif