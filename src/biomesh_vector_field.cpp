
#include <biomesh_vector_field.hpp>

namespace biomesh
{
vector_field::vector_field (const std::string &file_name)
    : m_file_name{ file_name }, m_sgrid{
        vtkSmartPointer<vtkStructuredGrid>::New ()
      }
{
}

vector_field::vector_field (const vector_field &other)
{
  this->m_file_name = other.m_file_name;
  this->m_sgrid->DeepCopy (other.m_sgrid);
}

vector_field::vector_field (vector_field &&other)
{
  this->m_file_name = other.m_file_name;
  other.m_file_name.clear ();
  this->m_sgrid->ShallowCopy (other.m_sgrid);
}

vector_field::~vector_field () {}

int
vector_field::load_vtk_grid ()
{
  BIOMESH_ASSERT (!m_file_name.empty ());
  BIOMESH_LINFO (0, "File: " + m_file_name);

  /* Initialize serial reader. */
  vtkSmartPointer<vtkStructuredGridReader> reader
      = vtkSmartPointer<vtkStructuredGridReader>::New ();
  BIOMESH_ASSERT (reader != nullptr);

  /* Read the file. */
  BIOMESH_LINFO (0, "Read vtk file start.");
  reader->SetFileName (this->m_file_name.c_str ());
  reader->Update ();
  BIOMESH_ASSERT (reader->IsFileValid ("structured"));
  BIOMESH_LINFO (0, "Read vtk file finish.");

  /* Obtain the structured grid data. */
  m_sgrid = reader->GetOutput ();
  BIOMESH_ASSERT (this->m_sgrid != nullptr);
#ifdef BIOMESH_ENABLE_DEBUG
  m_sgrid->Print (std::cout);
#endif

  /* TODO: Add the parallel xml reader when the parallel file format is
   * available. */

  return (m_sgrid != nullptr) ? BIOMESH_SUCCESS : BIOMESH_ERROR;
}
}