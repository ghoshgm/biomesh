
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

# Test for Eigen installation.
add_executable(test_eigen test_eigen.cpp)
target_link_libraries(test_eigen PUBLIC Eigen3::Eigen)
add_test(NAME test_eigen COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_eigen)

# Test for VTK structured grid reader.
add_executable(test_vtk_structured_grid test_vtk_structured_grid.cpp)
target_include_directories(test_vtk_structured_grid PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include)
target_link_libraries(test_vtk_structured_grid PUBLIC ${VTK_LIBRARIES} ${CMAKE_BINARY_DIR}/lib/libbiomesh.so)
add_test(NAME test_vtk_structured_grid COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_vtk_structured_grid ${CMAKE_SOURCE_DIR}/test/sgrid_example.vtk)

# Test for vertex class.
add_executable(test_vertex test_vertex.cpp)
target_include_directories(test_vertex PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include)
target_link_libraries(test_vertex PUBLIC ${CMAKE_BINARY_DIR}/lib/libbiomesh.so Eigen3::Eigen)
add_test(NAME test_vertex COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_vertex)

# Test for interpolation methods.
add_executable(test_interpolation test_interpolation.cpp)
target_include_directories(test_interpolation PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include)
target_link_libraries(test_interpolation PUBLIC ${CMAKE_BINARY_DIR}/lib/libbiomesh.so Eigen3::Eigen)
add_test(NAME test_interpolation COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_interpolation)

# Test for jsoncpp installation.
add_executable(test_jsoncpp test_json.cpp)
target_include_directories(test_jsoncpp PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include)
target_link_libraries(test_jsoncpp PUBLIC ${CMAKE_BINARY_DIR}/lib/libbiomesh.so ${JSONCPP_LIBRARIES} Eigen3::Eigen ${VTK_LIBRARIES})
add_test(NAME test_jsoncpp COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_jsoncpp ${CMAKE_SOURCE_DIR}/test/read_sample.json)

# Test Boost installation.
add_executable(test_boost test_boost.cpp)
target_include_directories(test_boost PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include)
target_link_libraries(test_boost PUBLIC ${VTK_LIBRARIES} ${CMAKE_BINARY_DIR}/lib/libbiomesh.so)
add_test(NAME test_boost COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_boost)

# Test for stopwatch.
add_executable(test_stopwatch test_stopwatch.cpp)
target_include_directories(test_stopwatch PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include)
target_link_libraries(test_stopwatch PUBLIC ${CMAKE_BINARY_DIR}/lib/libbiomesh.so)
add_test(NAME test_stopwatch COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_stopwatch)

# Test for 3D fiber grid.
#add_executable(test_fiber_grid3d test_fiber_grid3d.cpp)
#target_include_directories(test_fiber_grid3d PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include ${PETSC_INCLUDE_DIRS})
#target_link_libraries(test_fiber_grid3d PUBLIC ${VTK_LIBRARIES} ${CMAKE_BINARY_DIR}/lib/libbiomesh.so Eigen3::Eigen ${JSONCPP_LIBRARIES} ${PETSC_LINK_LIBRARIES})
#add_test(NAME test_fiber_grid3d COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_fiber_grid3d ${CMAKE_SOURCE_DIR}/test/sgrid3d_unit_z.vtk ${CMAKE_SOURCE_DIR}/test/sgrid3d_unit_seed.json)

# Test VTK cell orientation for interpolation techniques.
add_executable(test_orientation test_orientation.cpp)
target_include_directories(test_orientation PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include ${PETSC_INCLUDE_DIRS})
target_link_libraries(test_orientation PUBLIC ${CMAKE_BINARY_DIR}/lib/libbiomesh.so ${JSONCPP_LIBRARIES} Eigen3::Eigen ${VTK_LIBRARIES} ${PETSC_LINK_LIBRARIES})
add_test(NAME test_orientation COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_orientation ${CMAKE_SOURCE_DIR}/test/sgrid3d_unit_x.vtk ${CMAKE_SOURCE_DIR}/test/sgrid3d_unit_z.vtk ${CMAKE_SOURCE_DIR}/test/sgrid3d_unit_seed.json)

# Test for fiber grid.
add_executable(test_fiber_grid test_fiber_grid.cpp)
target_include_directories(test_fiber_grid PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include ${PETSC_INCLUDE_DIRS})
target_link_libraries(test_fiber_grid PUBLIC ${VTK_LIBRARIES} ${CMAKE_BINARY_DIR}/lib/libbiomesh.so Eigen3::Eigen ${JSONCPP_LIBRARIES} ${PETSC_LINK_LIBRARIES})
add_test(NAME test_fiber_grid COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_fiber_grid ${CMAKE_SOURCE_DIR}/test/sgrid2d_straight_x.vtk ${CMAKE_SOURCE_DIR}/test/sgrid2d_straight_x_seed.json
${CMAKE_SOURCE_DIR}/test/sgrid2d_radial.vtk ${CMAKE_SOURCE_DIR}/test/sgrid2d_radial_seed.json
${CMAKE_SOURCE_DIR}/test/sgrid2d_diagnol.vtk ${CMAKE_SOURCE_DIR}/test/sgrid2d_diagnol_seed.json
${CMAKE_SOURCE_DIR}/test/sgrid2d_quarter_circle.vtk ${CMAKE_SOURCE_DIR}/test/sgrid2d_quarter_circle_seed.json
)