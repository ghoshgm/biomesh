
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
public:
  /**
   * Default constructor.
   */
  json_parser ();

  /**
   * Constructor.
   *
   * @param[in] file_path The path to json file.
   */
  json_parser (const std::string &file_path);

  /**
   * Destructor.
   */
  ~json_parser ();

  /**
   * Function to read JSON file and store the data.
   *
   * @return Success if the file was read without error otherwise Error is
   * returned.
   */
  int read ();

  /**
   * Function to retrive JSON string from the JSON file.
   *
   * @return The JSON string.
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
   * This is just the name of the file and not the path to the file.
   */
  template <class T>
  void export_fiber_grid_json (const T &fiber_grid,
                               std::string file_name) const;

private:
  Json::Value m_jstring;
  std::string m_file_path;
  Json::Reader reader;
};

}

#endif