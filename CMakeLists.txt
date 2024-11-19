cmake_minimum_required(VERSION 3.13...3.24)

# Project description.
project(BIOMESH
LANGUAGES C CXX
DESCRIPTION "biomesh is a highly scalable meshing library for musculoskeletal simulations."
)

# Find external dependencies.
include(cmake/find_dependencies.cmake)

# Configure biomesh.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/results)
include(cmake/config.cmake)

# Build source.
add_subdirectory(src)

# Build examples.
add_subdirectory(examples)

# Unit tests.
include(CTest)
add_subdirectory(test)