
#ifndef BIOMESH_XML_PARSER_HPP
#define BIOMESH_XML_PARSER_HPP

#include <any>
#include <biomesh_base.hpp>
#include <iostream>
#include <unordered_map>
#include <variant>

namespace biomesh
{

class configuration
{
public:
  explicit configuration (const std::string &file_path);

  ~configuration ();

  void read_config_file ();

  template <typename T> T get_value (const std::string &parameter) const;

  void print () const;

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
    throw std::runtime_error ("Key not found: " + parameter);

  try
    {
      return std::any_cast<T> (it->second);
    }
  catch (const std::bad_any_cast &)
    {
      throw std::runtime_error ("Type mismatch for key: " + parameter);
    }
}

} // namespace biomesh

#endif