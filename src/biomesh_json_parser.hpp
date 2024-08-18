
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
  Json::Value m_jstring;
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
   * Function to retrive JSON string from the JSON file.
   */
  Json::Value get_json_string () const;

  /**
   * @brief Function to export fiber grid to JSON format.
   *
   * This function should be only called when the computation
   * of fibers is completed.
   *
   * The default directory for the generated JSON file
   * is the build directory.
   *
   * @param[in] fiber_grid The vector of fibers computed by libbiomesh.
   * @param[in] file_name The desired name of the JSON file.
   */
  template <typename fiber>
  void export_fiber_grid_json (std::vector<fiber> &fiber_grid,
                               std::string &file_name);
};

}

#endif