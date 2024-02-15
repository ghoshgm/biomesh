
include(CheckIncludeFile)
include(CheckIncludeFileCXX)
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
endif()
check_include_file(stdint.h HAVE_STDINT_H)
check_include_file(math.h HAVE_MATH_H)
check_include_file_cxx("memory" HAVE_MEMORY_H)
check_include_file_cxx("algorithm" HAVE_ALGORITHM_H)
check_include_file_cxx("vector" HAVE_VECTOR_H)
