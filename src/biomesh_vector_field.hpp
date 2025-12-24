
#ifndef BIOMESH_VECTOR_FIELD_HPP
#define BIOMESH_VECTOR_FIELD_HPP

#include <vtkSmartPointer.h>
#include <vtkStructuredGrid.h>
#include <vtkStructuredGridReader.h>

#include <biomesh_base.hpp>
#include <biomesh_cell_table.hpp>

namespace biomesh
{
/**
 * @brief Class to load and preprocess vector data from a vtk file.
 *
 * The input is a vtk file which encodes the vtk structured
 * grid data structure. The vertices of the grid cells hold
 * the vectors ( one vector per vertex ).
 *
 * The class performs preprocessing of the vtk data.
 * The processed vector field will be used for generating
 * the 1D grids.
 *
 * The output is a vtk structured grid which holds all the necessary vector
 * data for generating muscle fibers (1D grids).
 */
class vector_field
{
public:
  /**
   * Default constructor.
   *
   * @param[in] file_path Path to the vtk file.
   */
  vector_field (const std::string &file_path);

  /**
   * Copy constructor.
   *
   * @param[in] other Instantiated vector field object.
   */
  vector_field (const vector_field &other);

  /**
   * Move constructor.
   *
   * @param[in] other Instantiated vector field object.
   */
  vector_field (vector_field &&other);

  /**
   * Destructor.
   */
  ~vector_field ();

  /**
   * @brief Read structured grid data from a vtk file.
   *
   * Only The legacy VTK file format for structured grid is supported.
   * The structured data structure is replicated on every MPI rank.
   *
   * @return Success if the file was read without error otherwise Error is
   * returned.
   */
  int load_vtk_grid ();

  /**
   * @brief Preprocess vector data.
   *
   * The muscle geometry is enclosed within the structured grid.
   * Not every vector contributes to the muscle geometry.
   * The function flags vectors which are not part of the
   * actual muscle geometry.
   */
  void preprocess ();

  int operator[] (size_t cell_index) const;

  /**
   * Getter to the underlying VTK structured grid.
   */
  vtkSmartPointer<vtkStructuredGrid> get_grid () const;

private:
  std::string m_file_path;
  vtkSmartPointer<vtkStructuredGrid> m_sgrid;
  cell_table m_ct;
};
} // namespace biomesh

#endif