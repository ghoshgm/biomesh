cmake_minimum_required(VERSION 3.13...3.24)

# Project description.
project(BIOMESH
LANGUAGES C CXX
DESCRIPTION "biomesh is a highly scalable meshing library for musculoskeletal simulations."
)

# Find external dependencies.
include(cmake/find_dependencies.cmake)

# Configure biomesh.
include(cmake/config.cmake)

# Unit tests.
include(CTest)
add_subdirectory(test)

# Build source.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
add_subdirectory(src)