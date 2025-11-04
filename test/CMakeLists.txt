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

# Test XML installation.
add_executable(test_xml test_xml.cpp)
target_include_directories(test_xml PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include ${LIBXML2_INCLUDE_DIRS})
target_link_libraries(test_xml PUBLIC ${CMAKE_BINARY_DIR}/lib/libbiomesh.so LibXml2::LibXml2)
add_test(NAME test_xml COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_xml)

# Test for stopwatch.
add_executable(test_stopwatch test_stopwatch.cpp)
target_include_directories(test_stopwatch PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include)
target_link_libraries(test_stopwatch PUBLIC ${CMAKE_BINARY_DIR}/lib/libbiomesh.so)
add_test(NAME test_stopwatch COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_stopwatch)

# Test for 3D fiber grid.
add_executable(test_fiber_grid3d test_fiber_grid3d.cpp)
target_include_directories(test_fiber_grid3d PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include)
target_link_libraries(test_fiber_grid3d PUBLIC ${VTK_LIBRARIES} ${CMAKE_BINARY_DIR}/lib/libbiomesh.so Eigen3::Eigen ${JSONCPP_LIBRARIES})
add_test(NAME test_fiber_grid3d COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_fiber_grid3d ${CMAKE_SOURCE_DIR}/test/sgrid3d_straight.vtk ${CMAKE_SOURCE_DIR}/test/sgrid3d_straight_seed.json
${CMAKE_SOURCE_DIR}/test/sgrid3d_diagnol.vtk ${CMAKE_SOURCE_DIR}/test/sgrid3d_diagnol_seed.json
${CMAKE_SOURCE_DIR}/test/sgrid3d_diagnol_z.vtk ${CMAKE_SOURCE_DIR}/test/sgrid3d_diagnol_z_seed.json
${CMAKE_SOURCE_DIR}/test/sgrid3d_wave_laminar.vtk ${CMAKE_SOURCE_DIR}/test/sgrid3d_wave_laminar_seed.json
${CMAKE_SOURCE_DIR}/test/sgrid3d_spiral.vtk ${CMAKE_SOURCE_DIR}/test/sgrid3d_spiral_seed.json
)

# Test for 2D fiber grid.
add_executable(test_fiber_grid2d test_fiber_grid2d.cpp)
target_include_directories(test_fiber_grid2d PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include)
target_link_libraries(test_fiber_grid2d PUBLIC ${VTK_LIBRARIES} ${CMAKE_BINARY_DIR}/lib/libbiomesh.so Eigen3::Eigen ${JSONCPP_LIBRARIES})
add_test(NAME test_fiber_grid2d COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_fiber_grid2d ${CMAKE_SOURCE_DIR}/test/sgrid2d_straight_x.vtk ${CMAKE_SOURCE_DIR}/test/sgrid2d_straight_x_seed.json
${CMAKE_SOURCE_DIR}/test/sgrid2d_radial.vtk ${CMAKE_SOURCE_DIR}/test/sgrid2d_radial_seed.json
${CMAKE_SOURCE_DIR}/test/sgrid2d_diagnol.vtk ${CMAKE_SOURCE_DIR}/test/sgrid2d_diagnol_seed.json
${CMAKE_SOURCE_DIR}/test/sgrid2d_quarter_circle.vtk ${CMAKE_SOURCE_DIR}/test/sgrid2d_quarter_circle_seed.json
${CMAKE_SOURCE_DIR}/test/sgrid2d_melon.vtk ${CMAKE_SOURCE_DIR}/test/sgrid2d_melon_seed.json
${CMAKE_SOURCE_DIR}/test/sgrid2d_random.vtk ${CMAKE_SOURCE_DIR}/test/sgrid2d_random_seed.json
${CMAKE_SOURCE_DIR}/test/sgrid2d_circle.vtk ${CMAKE_SOURCE_DIR}/test/sgrid2d_circle_seed.json
${CMAKE_SOURCE_DIR}/test/sgrid2d_zero.vtk ${CMAKE_SOURCE_DIR}/test/sgrid2d_zero_seed.json
)

# Test for cell classification.
add_executable(test_cell_classification test_cell_classification.cpp)
target_include_directories(test_cell_classification PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include)
target_link_libraries(test_cell_classification PUBLIC ${VTK_LIBRARIES} ${CMAKE_BINARY_DIR}/lib/libbiomesh.so Eigen3::Eigen ${JSONCPP_LIBRARIES})
#add_test(NAME test_cell_classification COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_cell_classification ${CMAKE_SOURCE_DIR}/test/cell_classification_2d.vtk ${CMAKE_SOURCE_DIR}/examples/sgrid3d_ellipsoid_new.vtk)
add_test(NAME test_cell_classification COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_cell_classification ${CMAKE_SOURCE_DIR}/test/cell_classification_2d.vtk ${CMAKE_SOURCE_DIR}/test/Static_90_S09_2_deep.vtk)

# Test for configuration class.
add_executable(test_configuration test_configuration.cpp)
target_include_directories(test_configuration PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include)
target_link_libraries(test_configuration PUBLIC ${VTK_LIBRARIES} ${CMAKE_BINARY_DIR}/lib/libbiomesh.so LibXml2::LibXml2)
add_test(NAME test_configuration COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_configuration)