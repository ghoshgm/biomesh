
# Test for fiber grid.
add_executable(unit_square_fibers unit_square_fibers.cpp)
target_include_directories(unit_square_fibers PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include)
target_link_libraries(unit_square_fibers PUBLIC ${VTK_LIBRARIES} ${CMAKE_BINARY_DIR}/lib/libbiomesh.so Eigen3::Eigen ${JSONCPP_LIBRARIES})