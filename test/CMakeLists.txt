
# Test for MPI installation.
add_executable(test_mpi test_mpi.cpp)
target_include_directories(test_mpi PUBLIC ${MPI_CXX_INCLUDE_DIRS})
target_link_libraries(test_mpi PUBLIC ${MPI_CXX_LIBRARIES})
add_test(NAME test_mpi COMMAND ${MPIEXEC_EXECUTABLE} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_NUMPROC_MAX} ${CMAKE_CURRENT_BINARY_DIR}/test_mpi)

# Test for VTK installation.
add_executable(test_vtk test_vtk.cpp)
target_link_libraries(test_vtk PUBLIC ${VTK_LIBRARIES})
add_test(NAME test_vtk COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_vtk)