
#ifndef BIOMESH_VECTOR_FIELD_HPP
#define BIOMESH_VECTOR_FIELD_HPP

#include <vtkSmartPointer.h>
#include <vtkStructuredGrid.h>
#include <vtkStructuredGridReader.h>

#include <biomesh.hpp>
#include <memory>

namespace biomesh
{
class vector_field
{
public:
  vector_field (const std::string &file_name);
  vector_field (const vector_field &other);
  vector_field (const vector_field &&other);
  ~vector_field ();
  int load_vtk_grid ();
  int generate_field ();

private:
  std::string m_file_name;
  vtkSmartPointer<vtkStructuredGrid> m_sgrid;
};
} // namespace biomesh

#endif