
#ifndef BIOMESH_XML_PARSER_HPP
#define BIOMESH_XML_PARSER_HPP

#include <any>
#include <biomesh_base.hpp>
#include <iostream>
#include <unordered_map>

namespace biomesh
{

class configuration
{
public:
  explicit configuration (const std::string &file_path);

  ~configuration ();

  void read_config_file ();

  auto operator[] (std::string &parameter);

  void print () const;

private:
  std::string m_file_path;

  using parameter = std::string;
  using value = std::any;

  std::unordered_map<parameter, value> m_settings;
};

} // namespace biomesh

#endif