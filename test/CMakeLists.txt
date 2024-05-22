
if(ENABLE_MPI)
  # Test for MPI installation.
  add_executable(test_mpi test_mpi.cpp)
  target_include_directories(test_mpi PUBLIC ${MPI_CXX_INCLUDE_DIRS})
  target_link_libraries(test_mpi PUBLIC ${MPI_CXX_LIBRARIES})
  add_test(NAME test_mpi COMMAND ${MPIEXEC_EXECUTABLE} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_NUMPROC_MAX} ${CMAKE_CURRENT_BINARY_DIR}/test_mpi)
endif()

# Test for VTK installation.
add_executable(test_vtk test_vtk.cpp)
target_link_libraries(test_vtk PUBLIC ${VTK_LIBRARIES})
add_test(NAME test_vtk COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_vtk)

# Test for VTK structured grid reader.
add_executable(test_vtk_structured_grid test_vtk_structured_grid.cpp)
target_include_directories(test_vtk_structured_grid PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include)
target_link_libraries(test_vtk_structured_grid PUBLIC ${VTK_LIBRARIES} ${CMAKE_BINARY_DIR}/lib/libbiomesh.so)
add_test(NAME test_vtk_structured_grid COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_vtk_structured_grid ${CMAKE_SOURCE_DIR}/test/sgrid_example.vtk)

# Test for vertex class.
add_executable(test_vertex test_vertex.cpp)
target_include_directories(test_vertex PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include)
target_link_libraries(test_vertex PUBLIC ${CMAKE_BINARY_DIR}/lib/libbiomesh.so)
add_test(NAME test_vertex COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_vertex)