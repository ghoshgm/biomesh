
This document provides detailed information about building and installing the source code on Unix machines.

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
| Tool       | Minimum Version|
|------------|----------------|
| Paraview   | 5.13.3         |
| Valgrind   | 3.26.0         |

You can install these via a package manager (e.g., `apt`, `spack`), or build from source.

**NOTE:** It is highly recommended to build the VTK library from source because the package managers offer limited support. See the instructions below to build from source:
```bash
git clone https://github.com/Kitware/VTK.git
mkdir vtk_build && cd vtk_build
cmake path/to/vtk/source
make -j8
```

### Supported compilers
| Compiler   | Minimum Version|
|------------|----------------|
|GCC         | 11.4.0         |

### Supported OS
|  Operating system  | Minimum Version|
|--------------------|----------------|
|Ubuntu              | 22.04          |

## Building from source

### 1. Getting the source code:
```bash
git clone https://github.com/ghoshgm/biomesh.git
```
**NOTE:** All latest updates are on the ```develop``` branch.

### 2. Configuration:
It is always good practice to keep the build directory separate to keep the source directory clean.
```bash
mkdir biomesh_build && cd biomesh_build
```

An example configuration line for debug builds:
```bash
cmake -DCMAKE_BUILD_TYPE=debug
-DCMAKE_CXX_FLAGS="-O0 -g -Wall" 
-DCMAKE_PREFIX_PATH="path/to/dependencies" path/to/source
```
An example configuration line for release builds:
```bash
cmake -DCMAKE_BUILD_TYPE=release
-DCMAKE_CXX_FLAGS="-O2 -Wall -Wno-unused-parameter" 
-DCMAKE_PREFIX_PATH="path/to/dependencies" path/to/source
```

### 3. Compilation
```bash
make
```
**NOTE:** Parallel builds are not functional at the moment due to dependency conflicts during compilation. It will be fixed eventually in the future.

### 4. Installation (optional)
The default location for the header files is the build directory.
```bash
make install
```

### 5. Unit Testing
Tests are executed using the CTest package from CMake
```bash
ctest /path/to/build/directory --output-on-failure
```

Tests for memory leaks
```bash
ctest /path/to/build/directory -T memcheck
```

### Linking BioMesh for your CMake project

Use these commands in your root CMakeLists.txt
```bash
find_package(biomesh REQUIRED)
...
target_link_libraries(project_name PUBLIC BIOMESH::biomesh)
```

**NOTE:** Since BioMesh has external dependencies, if the dependencies are not installed in the typical GNU install locations then make sure you tell CMake the path to the install directory via ```-DCMAKE_INSTALL_PREFIX```.