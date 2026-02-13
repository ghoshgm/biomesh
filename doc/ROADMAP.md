# Project status

This document outlines the current status, known limitations, and planned future work for the BioMesh library.

## Current Status

1. The algorithms and data structures for generating 1D fiber meshes are fully implemented and have been validated for correctness.
2. The 1D fiber generation workflow is fully functional and has been tested using real-world ultrasound imaging datasets.
3. Affine transformation operations, including translation and reflection, can be applied to a fiber grid.
4. Support for adaptive time stepping in the Runge–Kutta 4 (RK4) scheme has been implemented; comprehensive testing is currently pending.
5. Seed vertices are generated automatically and conform to the spatial bounds of the input vector field.

## Limitations

1. The number of vertices may vary between fibers due to the physical bounds of the vector fields derived from imaging data. The current implementation does not enforce a fixed vertex count across all fibers.
2. Seed vertices can be specified manually via JSON files; however, this functionality is not part of the planned development roadmap. It is available only for specialized use cases on the `feature-legacy-seeder` branch.
3. Support for 2D features has been discontinued and is not planned for the foreseeable future. These components may be phased out entirely in future releases.

## Future Work

1. Implementation of algorithms and data structures for 3D volumetric mesh generation.
2. Development of parallelization strategies to improve runtime performance.
3. Introduction of more rigorous validation routines for fiber generation. Currently, validation is limited to detecting duplicate fiber vertices.
4. The current seed vertex generation algorithm relies on random sampling. Developing methods to control the spatial distribution and pattern of seed vertices is an area of interest.
5. Implement code to enforce a fixed vertex count across all fibers. This may require an update to the existing adaptive time stepping strategy.