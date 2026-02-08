# BioMesh

**BioMesh** is an open source C++ library for generating computational meshes for skeletal muscle simulations.

BioMesh is intended to be used as a thirdparty meshing tool for the **OpenDiHu** library.

It is being actively developed at the [University of Stuttgart](https://www.ipvs.uni-stuttgart.de/).

## Purpose


A crucial part of neuromuscular simulations involves modelling the interaction between muscle components. The core biological strucuture of a muscle is composed of fibers, sacromeres and muscle belly, this naturally results in complex configurations with meshes in different dimensions:

- **0D** meshes for sarcomeres  
- **1D** meshes for muscle fibers  
- **3D** meshes for mechanical deformation and EMG simulations on the muscle belly.

Therefore, it becomes necessary to develop a specialized meshing tool to accurately capture the muscle deformations and neural responses.

The BioMesh library is being developed to offer implementations of these meshing algorithms. In literature, researchers have used MRI scans and CT-Scans as the starting point in the meshing workflow. It has been observed that the workflows are not optimized. We primarily build upon the work of Benjamin Maier and offer an alternative approach. In our work we primarily use Ultrasound Imaging data (Vector Fields indicating local fiber orientations) as a starting point for mesh generation. Our approach is a two-step process:

1. **Generation of muscle fibers as 1D meshes**
2. **Construction of the volumetric mesh (3D) using the fiber mesh as the basis**

## Dependencies

### Required dependencies

| Dependency | Minimum Version|
|------------|----------------|
| VTK        | 9.3.0          |
| Eigen      | 3.4.0          |
| JsonCpp    | 1.9.5          |
| Boost      | 1.74.0         |
| LibXml2    | 2.13.5         |
| CMake      | 3.15           |

### Useful tools
| Dependency | Minimum Version|
|------------|----------------|
| Paraview   | 9.3.0          |
| Valgrind   | 3.26.0         |


You can install these via a package manager (e.g., `apt`, `spack`), or build from source.

**NOTE:** It is highly recommended to build the VTK library from source because the package managers offer limited support.

## Installation
Installation instructions can be found at our wiki page for install instructions.

## Getting started
We recommend exploring the examples directory to get warmed-up. For a minimal hello world example you may refer to the wiki page for [examples/cuboid_fibers](examples/cuboid_fibers).

## Documentation
BioMesh uses [Doxygen](https://www.doxygen.nl/) to generate the code documentation. Refer to the wiki for more useful information.

## Contributing
BioMesh is an open-source project and contributions from the community are much appreciated.

Here’s how you can help:

1. Open issues for bugs or feature requests

2. Open pull requests with improvements

Please ensure your contributions are consistent with the existing coding style and include tests when applicable.

## License
BioMesh is released under the MIT License — see the [LICENSE](LICENSE)
file for details.