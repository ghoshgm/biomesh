cmake_minimum_required(VERSION 3.13...3.24)

# Project description.
project(biomesh
VERSION 1.0.0
LANGUAGES C CXX
DESCRIPTION "biomesh is a meshing library for musculoskeletal simulations."
)

# Find external dependencies.
include(cmake/find_dependencies.cmake)

# Configure biomesh.
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_BUILD_RPATH_USE_ORIGIN TRUE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/results)
include(cmake/config.cmake)

# Build source.
add_subdirectory(src)

message(STATUS "-------- SUMMARY --------")
message(STATUS "CXX: ${BIOMESH_CPP}")
message(STATUS "CXXFLAGS: ${BIOMESH_CPPFLAGS}")
message(STATUS "Build: ${CMAKE_BUILD_TYPE}")
message(STATUS "Install directory: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "-------------------------")

# Build examples.
add_subdirectory(examples)

# Unit tests.
include(CTest)
add_subdirectory(test)

# Packaging
include(GNUInstallDirs)

set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VENDOR "OpenDiHu")
set(CPACK_PACKAGE_CONTACT "gautam.ghosh@ipvs.uni-stuttgart.de")

set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")

# Ensure a clean top-level directory inside tarball
set(CPACK_PACKAGE_FILE_NAME
    "${PROJECT_NAME}-${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}"
)

set(CPACK_GENERATOR "TGZ")

# Optional but recommended
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README  "${CMAKE_SOURCE_DIR}/README.md")

# ------------------------
# Source tarball
# ------------------------

set(CPACK_SOURCE_GENERATOR "TGZ")

set(CPACK_SOURCE_PACKAGE_FILE_NAME
    "${PROJECT_NAME}-${PROJECT_VERSION}-source"
)

set(CPACK_SOURCE_IGNORE_FILES
    "/build/"
    "/.git/"
    "/.github/"
    ".*\\\\.swp$"
)

include(CPack)