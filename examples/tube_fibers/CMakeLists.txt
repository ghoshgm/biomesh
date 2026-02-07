
add_executable(tube_fibers tube_fibers.cpp)
target_include_directories(tube_fibers PUBLIC ${PETSC_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include)
target_link_libraries(tube_fibers PUBLIC ${VTK_LIBRARIES} ${CMAKE_BINARY_DIR}/lib/libbiomesh.so Eigen3::Eigen ${JSONCPP_LIBRARIES} ${LIBXML2_LIBRARIES})