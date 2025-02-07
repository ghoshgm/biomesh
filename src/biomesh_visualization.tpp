
template <class fiber_grid>
void
export_fiber_grid_vtk (const fiber_grid &fgrid, const std::string &file_prefix)
{
  BIOMESH_LINFO ("Export fibers to VTK format begin.");

  /* Loop over all fibers. */
  for (size_t ii = 0; ii < fgrid.size (); ++ii)
    {
      /* Set VTK file name for fiber. */
      std::string file_name = file_prefix + "_" + std::to_string (ii);

      /* Set path for files. */
      std::string file_path
          = std::string (BIOMESH_BUILD_DIR) + "/results/" + file_name + ".vtk";

      vtkNew<vtkPoints> vertices;

      /* Loop over fiber vertex coordinates. */
      auto fiber = fgrid[ii];
      for (size_t jj = 0; jj < fiber.size (); ++jj)
        {
          /* Grab the vertex. */
          auto vertex = fiber[jj];

          /* Push to VTK array. */
          vertices->InsertNextPoint (vertex ('x'), vertex ('y'), vertex ('z'));
        }

      /**
       * Create a VTK structured grid.
       * Every fiber is imagined as a 1D structured grid.
       */

      /** It is assumed that the fiber move forward in the X-direction.
       *  This may need to refactored as the code evolves.
       */
      vtkNew<vtkStructuredGrid> sgrid;
      sgrid->SetDimensions ((int)fiber.size (), 1, 1);
      sgrid->SetPoints (vertices);

      vtkNew<vtkStructuredGridWriter> writer;
      writer->SetFileName (file_path.c_str ());
      writer->SetInputData (sgrid);
      writer->Write ();
    }

  BIOMESH_LINFO ("Export fibers to VTK format end.");
  BIOMESH_LINFO ("The VTK files are written to: "
                 + std::string (BIOMESH_BUILD_DIR) + "/results");
}

void
write_cell_type_vtk (const cell_table &ctable, const vector_field &vfield,
                     const std::string &file_prefix)
{
  BIOMESH_LINFO ("Write cell type data to VTK format begin.");

  /* Set file name. */
  std::string file_name = file_prefix + "_" + "cell_type";
  std::string file_path
      = std::string (BIOMESH_BUILD_DIR) + "/results/" + file_name + ".vtk";

  /* Make a copy of the user-provided VTK structured grid. */
  vtkSmartPointer<vtkStructuredGrid> sgrid
      = vtkSmartPointer<vtkStructuredGrid>::New ();
  sgrid->DeepCopy (vfield.get_grid ());
  BIOMESH_ASSERT ((sgrid != nullptr));

  /* Allocate memory for cell type data. */
  vtkSmartPointer<vtkIntArray> cell_type
      = vtkSmartPointer<vtkIntArray>::New ();
  cell_type->SetName ("cell_type");
  cell_type->SetNumberOfComponents (1);
  cell_type->SetNumberOfTuples (sgrid->GetNumberOfCells ());

  /* Copy cell type data. */
  for (size_t ii = 0; ii < (size_t)sgrid->GetNumberOfCells (); ++ii)
    {
      cell_type->SetTuple1 (ii, ctable[ii]);
    }
  sgrid->GetCellData ()->SetScalars (cell_type);

  /* Export to VTK format for visualization. */
  vtkSmartPointer<vtkStructuredGridWriter> writer
      = vtkSmartPointer<vtkStructuredGridWriter>::New ();
  writer->SetFileName (file_path.c_str ());
  writer->SetInputData (sgrid);
  writer->Write ();

  BIOMESH_LINFO ("Write cell type data to VTK format end.");
  BIOMESH_LINFO ("The VTK files are written to: "
                 + std::string (BIOMESH_BUILD_DIR) + "/results");
}