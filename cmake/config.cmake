
include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckSymbolExists)
include(CheckCXXSymbolExists)
include(ProcessorCount)
include(CheckTypeSize)

# Check for primitive data types.
check_type_size(float SIZEOF_FLOAT)
check_type_size(double SIZEOF_DOUBLE)
message(STATUS "Size of float - ${SIZEOF_FLOAT} bytes.")
message(STATUS "Size of double - ${SIZEOF_DOUBLE} bytes.")

check_include_file(stdint.h HAVE_STDINT_H)
check_include_file(math.h HAVE_MATH_H)
check_include_file_cxx("memory" HAVE_MEMORY_H)
check_include_file_cxx("algorithm" HAVE_ALGORITHM_H)
check_include_file_cxx("vector" HAVE_VECTOR_H)

# Check for functions.
set(CMAKE_REQUIRED_LIBRARIES m)
check_symbol_exists(fabs math.h HAVE_FABS)

# Set macros for configure macros.
set(BIOMESH_CC \"${CMAKE_C_COMPILER}\")
set(BIOMESH_CPP \"${CMAKE_CXX_COMPILER}\")

set(BIOMESH_CPPFLAGS \"${CMAKE_CXX_FLAGS}\")

set(BIOMESH_BUILD_DIR \"${PROJECT_BINARY_DIR}\")

if(CMAKE_BUILD_TYPE MATCHES "debug")
  set(BIOMESH_ENABLE_DEBUG 1)
elseif(CMAKE_BUILD_TYPE MATCHES "release")
  set(BIOMESH_ENABLE_DEBUG 0)
endif()

# Generate configure file.
configure_file(${CMAKE_CURRENT_LIST_DIR}/biomesh_config.hpp.in ${PROJECT_BINARY_DIR}/include/biomesh_config.hpp)