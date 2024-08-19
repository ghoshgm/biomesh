
#include "biomesh_json_parser.hpp"

#include <biomesh_fiber_grid2D.hpp>

namespace biomesh
{

json_parser::json_parser () {}

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

template <class T>
void
json_parser::export_fiber_grid_json (const T &fiber_grid,
                                     std::string file_name) const
{
  BIOMESH_ASSERT (!file_name.empty ());
  std::ofstream file_id;
  Json::Value fiber_root;
  Json::StyledWriter writer;
  std::vector<Json::Value> jfiber;

  BIOMESH_LINFO (0, "Export fibers begin.");

  /* Convert fiber data to JSON format. */
  jfiber.reserve (fiber_grid.size ());
  /* Loop over every fiber. */
  for (int ii = 0; ii < fiber_grid.size (); ++ii)
    {
      /* Identifier for the fiber in the JSON file. */
      std::string fiber_name = "fiber" + std::to_string (ii);

      /* Loop over every vertex in a single fiber. */
      for (int jj = 0; jj < fiber_grid[ii].size (); ++jj)
        {
          jfiber[ii][jj]["x"] = fiber_grid[ii][jj]('x');
          jfiber[ii][jj]["y"] = fiber_grid[ii][jj]('y');
          jfiber[ii][jj]["z"] = fiber_grid[ii][jj]('z');
        }
      /* Root of the JSON file. */
      fiber_root[fiber_name] = jfiber[ii];
    }
  BIOMESH_ASSERT (!fiber_root.isNull ());

  /* Set directory for the JSON file. */
  std::string build_dir = BIOMESH_BUILD_DIR;
  std::string file_path = build_dir + "/" + file_name;

  /* Write to JSON file. */
  file_id.open (file_path);
  BIOMESH_ASSERT (file_id.is_open ());
  file_id << writer.write (fiber_root);
  file_id.close ();

  BIOMESH_LINFO (0, "Export fibers end.");
}

template void
json_parser::export_fiber_grid_json (const fiber_grid2D &fiber_grid,
                                     std::string file_name) const;
}