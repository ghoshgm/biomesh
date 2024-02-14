
find_package(MPI REQUIRED)
if(${MPI_FOUND})
  set(CMAKE_REQUIRED_LIBRARIES MPI::MPI_CXX)
endif()