# BioMesh
**BioMesh** is a C++ library to generate computational meshes for skeletal muscle simulations.

The software is developed at the University of Stuttgart.

## Dependencies
* VTK
* Eigen
* JsonCpp
* Boost

## Compiler support
* GCC 11.4.0 or newer

## OS support
* Ubuntu 22.04

## Build
CMake is required to build BioMesh from source.  
The default directory for installtion is the build directory.

### Obtaining the source code
The source code is hosted on GitHub.  
`git clone https://github.com/opendihu/biomesh.git`

### Configuration
`-DCMAKE_BUILD_TYPE` enables debug mode.  
It activates assertions and additional code verifications.  
Set to 'debug' to enable.  

An example configuration line for debug builds:  
```cmake -DCMAKE_BUILD_TYPE=debug -DCMAKE_CXX_FLAGS="-O0 -g -Wall" -DCMAKE_PREFIX_PATH="path/to/dependencies" path/to/source```

An example configuration line for release builds:  
```cmake -DCMAKE_CXX_FLAGS="-O2 -Wall -Wno-unused-parameter" -DCMAKE_PREFIX_PATH="path/to/dependencies" path/to/source```

### Compilation
Run the command: `make`  

**NOTE:** Parallel builds are not supported at the moment.

### Testing

Tests can executed via `ctest path/to/build/dir`  

For checking memory leaks use `ctest path/to/build/dir -T memcheck` 

## License
The BioMesh library is distributed under the MIT License.




