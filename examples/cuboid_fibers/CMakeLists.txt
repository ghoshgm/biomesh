
add_executable(cuboid_fibers cuboid_fibers.cpp)
target_include_directories(cuboid_fibers PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include)
target_link_libraries(cuboid_fibers PUBLIC ${VTK_LIBRARIES} ${CMAKE_BINARY_DIR}/lib/libbiomesh.so Eigen3::Eigen ${JSONCPP_LIBRARIES} ${LIBXML2_LIBRARIES})