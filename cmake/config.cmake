
include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckSymbolExists)
include(CheckCXXSymbolExists)
include(ProcessorCount)
include(CheckTypeSize)

# Generic routine to set appropriate cores for all tests.
# Typically the tests are executed with maximum 2 cores.
cmake_host_system_information(RESULT Ncpu QUERY NUMBER_OF_PHYSICAL_CORES)
if(Ncpu LESS 2)
  ProcessorCount(n)
  if(n GREATER Ncpu)
    set(Ncpu ${n})
  endif()
  set(MPIEXEC_NUMPROC_MAX 1)
else()
  set(MPIEXEC_NUMPROC_MAX 2)
endif()

# Check for primitive data types.
check_type_size(float SIZEOF_FLOAT)
check_type_size(double SIZEOF_DOUBLE)
message(STATUS "Size of float - ${SIZEOF_FLOAT} bytes.")
message(STATUS "Size of double - ${SIZEOF_DOUBLE} bytes.")

# Check for headers.
if(${MPI_FOUND})
  set(CMAKE_REQUIRED_LIBRARIES MPI::MPI_CXX)
  check_include_file(mpi.h HAVE_MPI_H)
  set(CMAKE_REQUIRED_LIBRARIES)
endif()
check_include_file(stdint.h HAVE_STDINT_H)
check_include_file(math.h HAVE_MATH_H)
check_include_file_cxx("memory" HAVE_MEMORY_H)
check_include_file_cxx("algorithm" HAVE_ALGORITHM_H)
check_include_file_cxx("vector" HAVE_VECTOR_H)

# Check for functions.
set(CMAKE_REQUIRED_LIBRARIES m)
check_symbol_exists(sqrt math.h HAVE_SQRT)
check_symbol_exists(fabs math.h HAVE_FABS)

# Set macros for configure macros.
if(ENABLE_MPI)
  set(BIOMESH_ENABLE_MPI 1)
  set(BIOMESH_CC \"${MPI_C_COMPILER}\")
  set(BIOMESH_CPP \"${MPI_CXX_COMPILER}\")
else()
  set(BIOMESH_CC \"${CMAKE_C_COMPILER}\")
  set(BIOMESH_CPP \"${CMAKE_CXX_COMPILER}\")
endif()

set(BIOMESH_CPPFLAGS \"${CMAKE_CXX_FLAGS}\")

set(BIOMESH_BUILD_DIR \"${PROJECT_BINARY_DIR}\")

if(CMAKE_BUILD_TYPE MATCHES "debug")
  set(BIOMESH_ENABLE_DEBUG 1)
endif()

# Generate configure file.
configure_file(${CMAKE_CURRENT_LIST_DIR}/biomesh_config.hpp.in ${PROJECT_BINARY_DIR}/include/biomesh_config.hpp)