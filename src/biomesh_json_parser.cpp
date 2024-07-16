
#include "biomesh_json_parser.hpp"

namespace biomesh
{

json_parser::json_parser (const std::string &file_name)
    : m_file_name{ file_name }
{
}

json_parser::~json_parser () {}

int
json_parser::read ()
{
  std::ifstream m_file (m_file_name);
  BIOMESH_ASSERT (m_file.is_open ());

  Json::Reader reader;
  bool success = reader.parse (m_file, m_data);
  BIOMESH_ASSERT (success == true);

  m_file.close ();
  BIOMESH_ASSERT (!m_file.is_open ());

  return (success == true) ? BIOMESH_SUCCESS : BIOMESH_ERROR;
}

Json::Value
json_parser::get_json_data () const
{
  return m_data;
}

}