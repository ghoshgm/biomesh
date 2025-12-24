
#ifndef BIOMESH_XML_PARSER_HPP
#define BIOMESH_XML_PARSER_HPP

#include <any>
#include <biomesh_base.hpp>
#include <iostream>
#include <unordered_map>
#include <variant>

namespace biomesh
{
/**
 * @brief Class for parsing the configuration file for generating fibers.
 *
 * Currently, the XML format is used.
 *
 */
class configuration
{
public:
  /**
   * Constructor.
   *
   * @param[in] file_path The path to the XML file.
   */
  explicit configuration (const std::string &file_path);

  /**
   * Destructor.
   */
  ~configuration ();

  /**
   * Function to read the XML file.
   */
  void read_config_file ();

  /**
   * Function to return the value for a parameter in the XML file.
   *
   * This function should only be called after 'read_config_file'.
   *
   * @param[in] parameter The parameter name.
   */
  template <typename T> T get_value (const std::string &parameter) const;

private:
  std::string m_file_path;

  using parameter = std::string;
  using value = std::any;

  std::unordered_map<parameter, value> m_settings;
};

template <typename T>
T
configuration::get_value (const std::string &parameter) const
{
  auto it = m_settings.find (parameter);
  if (it == m_settings.end ())
    throw std::runtime_error ("Parameter not found: " + parameter);

  try
    {
      return std::any_cast<T> (it->second);
    }
  catch (const std::bad_any_cast &)
    {
      throw std::runtime_error ("Type mismatch for parameter: " + parameter);
    }
}

} // namespace biomesh

#endif