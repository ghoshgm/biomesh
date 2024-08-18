
#include "biomesh_json_parser.hpp"

#include <biomesh_fiber2d.hpp>
#include <biomesh_fiber3d.hpp>

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
  bool success = reader.parse (m_file, m_jstring);
  BIOMESH_ASSERT (success == true);

  m_file.close ();
  BIOMESH_ASSERT (!m_file.is_open ());

  return (success == true) ? BIOMESH_SUCCESS : BIOMESH_ERROR;
}

Json::Value
json_parser::get_json_string () const
{
  return m_jstring;
}

template <typename fiber>
void
json_parser::export_fiber_grid_json (std::vector<fiber> &fiber_grid,
                                     std::string &file_name)
{
  std::ofstream file_id;
  Json::Value fiber_root;
  Json::StyledWriter writer;
  std::vector<Json::Value> jfiber;

  for (int ii = 0; ii < fiber_grid.size (); ++ii)
    {
      std::string fiber_name = "fiber" + std::to_string (ii);
      for (int jj = 0; jj < fiber_grid[ii].size (); ++jj)
        {
          jfiber[ii][jj]["x"] = fiber_grid[ii][jj]('x');
          jfiber[ii][jj]["y"] = fiber_grid[ii][jj]('y');
          jfiber[ii][jj]["z"] = fiber_grid[ii][jj]('z');
        }
      fiber_root[fiber_name] = jfiber[ii];
    }

  file_id.open (file_name);
  file_id << writer.write (fiber_root);
  file_id.close ();
}
}