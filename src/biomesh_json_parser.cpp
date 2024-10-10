
#include "biomesh_json_parser.hpp"

#include <biomesh_fiber_grid.hpp>

namespace biomesh
{

json_parser::json_parser () {}

json_parser::json_parser (const std::string &file_path)
    : m_file_path{ file_path }
{
}

json_parser::~json_parser () {}

int
json_parser::read ()
{
  /* Open the JSON file. */
  std::ifstream m_file (m_file_path);
  BIOMESH_ASSERT (m_file.is_open ());

  /* Read the JSON file. */
  BIOMESH_LINFO (0, "Input JSON file path: " + m_file_path);
  BIOMESH_LINFO (0, "JSON file read begin.");
  bool success = reader.parse (m_file, m_jstring);
  BIOMESH_ASSERT (success == true);
  BIOMESH_LINFO (0, "JSON file read end.");

  /* Close the JSON file. */
  m_file.close ();
  BIOMESH_ASSERT (!m_file.is_open ());

  return (success == true) ? BIOMESH_SUCCESS : BIOMESH_ERROR;
}

Json::Value
json_parser::get_json_string () const
{
  BIOMESH_ASSERT (!m_jstring.isNull ());
  return m_jstring;
}

template <class T>
void
json_parser::export_fiber_grid_json (const T &fgrid,
                                     std::string file_name) const
{
  BIOMESH_ASSERT (!file_name.empty ());
  std::ofstream file_id;
  Json::Value fiber_root;
  Json::StyledWriter writer;
  std::vector<Json::Value> jfiber;

  BIOMESH_LINFO (0, "Export fibers begin.");

  /* Loop over every fiber. */
  for (int ii = 0; ii < fgrid.size (); ++ii)
    {
      /* Loop over every vertex in a single fiber. */
      for (int jj = 0; jj < fgrid[ii].size (); ++jj)
        {
          fiber_root[ii][jj]["x"] = fgrid[ii][jj]('x');
          fiber_root[ii][jj]["y"] = fgrid[ii][jj]('y');
          fiber_root[ii][jj]["z"] = fgrid[ii][jj]('z');
        }
      BIOMESH_ASSERT (!fiber_root.isNull ());
      /* Push fiber into JSON string format. */
      jfiber.push_back (fiber_root[ii]);
    }

  /* Set directory for the JSON file. */
  std::string file_path = std::string (BIOMESH_BUILD_DIR) + "/" + file_name;

  /* Write to JSON file. */
  file_id.open (file_path);
  BIOMESH_ASSERT (file_id.is_open ());
  for (int ii = 0; ii < jfiber.size (); ++ii)
    file_id << writer.write (jfiber[ii]);

  file_id.close ();
  BIOMESH_ASSERT (!file_id.is_open ());
  BIOMESH_LINFO (0, "The JSON file is written to: " + file_path);

  BIOMESH_LINFO (0, "Export fibers end.");
}

template void json_parser::export_fiber_grid_json (
    const fiber_grid<fiber2D, vertex2D> &fgrid, std::string file_name) const;
template void json_parser::export_fiber_grid_json (
    const fiber_grid<fiber3D, vertex3D> &fgrid, std::string file_name) const;

}