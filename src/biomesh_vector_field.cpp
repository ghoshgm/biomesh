
#include <biomesh_vector_field.hpp>

#include <biomesh_visualization.hpp>

namespace biomesh
{
vector_field::vector_field (const std::string &file_path)
    : m_file_path{ file_path }, m_sgrid{
        vtkSmartPointer<vtkStructuredGrid>::New ()
      }
#if 0
      ,
      m_ct{m_sgrid}
#endif
{
}

vector_field::vector_field (const vector_field &other)
{
  this->m_file_path = other.m_file_path;
  this->m_sgrid->DeepCopy (other.m_sgrid);
}

vector_field::vector_field (vector_field &&other)
{
  this->m_file_path = other.m_file_path;
  other.m_file_path.clear ();
  this->m_sgrid->ShallowCopy (other.m_sgrid);
}

vector_field::~vector_field () {}

int
vector_field::load_vtk_grid ()
{
  BIOMESH_ASSERT (!m_file_path.empty ());
  BIOMESH_LINFO ("File: " + m_file_path);

  /* Initialize serial reader. */
  vtkSmartPointer<vtkStructuredGridReader> reader
      = vtkSmartPointer<vtkStructuredGridReader>::New ();
  BIOMESH_ASSERT (reader != nullptr);

  /* Read the file. */
  BIOMESH_LINFO ("Read vtk file start.");
  reader->SetFileName (this->m_file_path.c_str ());
  reader->Update ();
  BIOMESH_ASSERT (reader->IsFileValid ("structured"));
  BIOMESH_LINFO ("Read vtk file finish.");

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

void
vector_field::preprocess ()
{
  // m_ct.classify_cells (m_sgrid);
  // m_ct.find_seed_cells (m_sgrid);
}

int
vector_field::operator[] (size_t cell_index) const
{
  return m_ct[cell_index];
}

vtkSmartPointer<vtkStructuredGrid>
vector_field::get_grid () const
{
  return m_sgrid;
}

} // namespace biomesh