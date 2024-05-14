
#include <biomesh_vector_field.hpp>

namespace biomesh
{
vector_field::vector_field (const std::string &file_name)
    : m_file_name{ file_name }, m_sgrid{
        vtkSmartPointer<vtkStructuredGrid>::New ()
      }
{
}

int
vector_field::load_vtk_grid ()
{
  BIOMESH_ASSERT (!file_name.empty ());

#ifndef BIOMESH_ENABLE_MPI
  std::unique_ptr<vtkStructuredGridReader> m_sgrid_reader
      = std::make_unique<vtkStructuredGridReader> ();
  BIOMESH_ASSERT (this->m_sgrid_reader != nullptr);
  reader->SetFileName (this->file_name.c_str ());
  reader->Update ();
  BIOMESH_ASSERT (reader->IsFileValid ("structured"));
  m_sgrid = reader->GetOutput ();
  BIOMESH_ASSERT (this->m_sgrid != nullptr);
#endif

  /* TODO: Add the parallel xml reader when the parallel file format is
   * available. */

  return (m_sgrid != nullptr) ? BIOMESH_SUCCESS : BIOMESH_ERROR;
}
}