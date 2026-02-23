# BioMesh

**BioMesh** is an open source C++ library for generating computational meshes for skeletal muscle simulations.

BioMesh is intended to be used as a thirdparty meshing tool for the [OpenDiHu](https://github.com/opendihu/opendihu/tree/develop) simulation software.

It is being actively developed at the [University of Stuttgart](https://www.ipvs.uni-stuttgart.de/departments/sgs/).

## Purpose

A crucial part of neuromuscular simulations involves modelling the interaction between muscle components. The core biological strucuture of a muscle is composed of fibers, sacromeres and muscle belly, this naturally results in complex configurations with meshes in different dimensions:

- **0D** meshes for sarcomeres  
- **1D** meshes for muscle fibers  
- **3D** meshes for mechanical deformation and EMG simulations on the muscle belly.

Therefore, it becomes necessary to develop a specialized meshing tool to accurately capture the muscle deformations and neural responses.

The BioMesh library is being developed to offer implementations of these meshing algorithms. In literature, researchers have used MRI scans and CT-Scans as the starting point in the meshing workflow. It has been observed that the workflows are not optimized. We primarily build upon the work of [Benjamin Maier](https://doi.org/10.48550/arXiv.2107.07104) and offer an alternative approach. In our work we primarily use Ultrasound Imaging data (Vector Fields indicating local fiber orientations) as a starting point for mesh generation. Our approach is a two-step process:

1. **Generation of muscle fibers as 1D meshes**
2. **Construction of the volumetric mesh (3D) using the fiber mesh as the basis**

## Installation
Refer to the [installation guide](doc/INSTALLATION.md) for building and installation.

## Getting started
- If this your first time using the library, it is highly recommended to read the [introduction](doc/INTRODUCTION.md) to get a basic overview of the library.
- For a minimal example you may refer to [tutorial](doc/TUTORIAL.md).

## Documentation
- BioMesh uses [Doxygen](https://www.doxygen.nl/) to generate the code documentation.
- Refer to the [developer](doc/DEVELOPER_GUIDE.md) page if you wish to develop the source code.
- Refer to [roadmap](doc/ROADMAP.md) to get latest development status.
- Refer to the [documentation](doc/OPENDIHU.md) to see muscle simulation results successfully supported by BioMesh.

## Contributing
BioMesh is an open-source project and contributions from the community are much appreciated.

Refer to the [contributing](doc/CONTRIBUTING.md) document for guidelines.

## License
BioMesh is released under the MIT License — see the [LICENSE](LICENSE)
file for details.

## Acknowledgement
We thank the Deutsche Forschungsgemeinschaft (DFG, German Research Foundation) for supporting this work by funding - [EXC2075](https://gepris.dfg.de/gepris/projekt/390740016?language=en) – 390740016 under Germany's Excellence Strategy. We acknowledge the support by the Stuttgart Center for Simulation Science (SimTech).