
add_executable(fiber_demo fiber_demo.cpp)
target_include_directories(fiber_demo PUBLIC ${PETSC_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include)
target_link_libraries(fiber_demo PUBLIC ${VTK_LIBRARIES} ${CMAKE_BINARY_DIR}/lib/libbiomesh.so Eigen3::Eigen ${JSONCPP_LIBRARIES})