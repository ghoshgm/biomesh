# BioMesh
**BioMesh** is a C++ library to generate computational meshes for skeletal muscle simulations.

The software is developed at the University of Stuttgart.

## Dependencies
* VTK 9.3.0 or newer
* Eigen 3.4.0 or newer
* JsonCpp 1.9.5 or newer
* Boost 1.74.0 or newer

## Building dependencies
The dependencies can be built from source or package managers like Spack, apt.

Make sure you have Spack installed on your machine.\
Instructions to build Spack:
```
git clone https://github.com/spack/spack.git
cd spack
. share/spack/setup-env.sh
```

### VTK
Building VTK from source is advisable.\
The Spack container for VTK has build issues.
```
git clone https://github.com/Kitware/VTK.git
mkdir vtk_build && cd vtk_build
cmake path/to/vtk/source
make -j8
```
### Eigen
Using Spack is easier and faster.
```
spack install eigen
```
### JsonCpp
Using Spack is easier and faster.
```
spack install jsoncpp
```
### Boost
Using apt is easier and faster.
```
sudo apt-get update && sudo apt-get install libboost-all-dev
```

## Compiler support
* GCC 11.4.0 or newer

## OS support
* Ubuntu 22.04

## Build
CMake is required to build BioMesh from source.  
The default directory for installtion is the build directory.

### Obtaining the source code
The source code is hosted on GitHub.  
```
git clone https://github.com/opendihu/biomesh.git
```

### Configuration
`-DCMAKE_BUILD_TYPE` enables debug mode.  
It activates assertions and additional code verifications.  
Set to 'debug' to enable.  

`-DCMAKE_PREFIX_PATH` points CMake to the build directories of dependencies.

An example configuration line for debug builds:  
```
cmake -DCMAKE_BUILD_TYPE=debug -DCMAKE_CXX_FLAGS="-O0 -g -Wall" -DCMAKE_PREFIX_PATH="path/to/dependencies" path/to/source
```

An example configuration line for release builds:  
```
cmake -DCMAKE_CXX_FLAGS="-O2 -Wall -Wno-unused-parameter" -DCMAKE_PREFIX_PATH="path/to/dependencies" path/to/source
```

### Compilation
Run the command: 
```
make
```  

**NOTE:** Parallel builds are not supported at the moment.

### Testing

Tests can executed via `ctest path/to/build/dir`  

For checking memory leaks use `ctest path/to/build/dir -T memcheck` 

## License
The BioMesh library is distributed under the MIT License.




