
template <class fiber_grid>
void
export_fiber_grid_vtk (const fiber_grid &fgrid, const std::string &file_prefix)
{
  BIOMESH_LINFO (0, "Export fibers to VTK format begin.");

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

  BIOMESH_LINFO (0, "Export fibers to VTK format end.");
  BIOMESH_LINFO (0, "The VTK files are written to: "
                        + std::string (BIOMESH_BUILD_DIR) + "/results");
}