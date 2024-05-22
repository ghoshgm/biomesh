
if(ENABLE_MPI)
 find_package(MPI REQUIRED)
endif()

find_package(VTK REQUIRED)
if(${VTK_FOUND})
  message(STATUS "Found VTK: ${VTK_DIR} (found version ${VTK_VERSION})")
endif()