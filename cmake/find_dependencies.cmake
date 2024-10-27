include(FindPkgConfig)

if(ENABLE_MPI)
 find_package(MPI REQUIRED)
endif()

find_package(VTK REQUIRED)
if(${VTK_FOUND})
  message(STATUS "Found VTK: ${VTK_DIR} (found version ${VTK_VERSION})")
endif()

find_package(Eigen3 REQUIRED)
if(${Eigen3_FOUND})
  message(STATUS "Found Eigen3: ${Eigen3_DIR} (found version ${Eigen3_VERSION})")
endif()

pkg_check_modules(PETSC REQUIRED PETSc)
if(${PETSC_FOUND})
  message(STATUS "PETSc path: ${PETSC_LIBDIR}")
endif()

pkg_check_modules(JSONCPP REQUIRED jsoncpp)
message(STATUS "Found jsoncpp: ${JSONCPP_LIBDIR}")