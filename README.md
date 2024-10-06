1. Introduction

BioMesh is a C++ library to generate meshes for skeletal muscle simula-
tions.

The software is developed at the University of Stuttgart.
Mesh generation plays a fundamental role to numerically solve Partial Differ-
ential Equations(PDE). The accuracy and stability of numerical discretiza-
tions are heavily dependent on the characteristics of the mesh. Many multi-
physics applications may require specialized meshing techniques for accurate
discretizations.

This work improves and expands the meshing algorithms implemented in
the OpenDiHu software library.
In our context, the term muscle mesh refers to the combination of mus-
cle fibers and muscle volume. Fibers are discretized as a set of 1D meshes
and the muscle volume is discretized as a 3D hexahedral mesh. The fibers
are embedded into the muscle volume.
