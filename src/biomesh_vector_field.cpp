
#include <biomesh_vector_field.hpp>

biomesh::vector_field(const std::string& file_name)
  : m_file_name{file_name},
    m_sgrid{std::make_unique<vtkStructuredGrid>()}
{}

biomesh::vector_field::load_vtk_grid()
{
  BIOMESH_ASSERT(!file_name.empty());

#ifndef BIOMESH_ENABLE_MPI
  std::unique_ptr<vtkStructuredGridReader> reader = std::make_unique<vtkStructuredGridReader>();
  reader->SetFileName(this->file_name.c_str());
  reader->Update();
  m_sgrid = reader->GetOutput();
#elif
  /* TODO: Add the parallel xml reader when the parallel file format is available. */
#endif
}