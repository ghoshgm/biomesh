
# Example for ellipsoid.
add_executable(ellipsoid ellipsoid.cpp)
target_include_directories(ellipsoid PUBLIC ${PETSC_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include)
target_link_libraries(ellipsoid PUBLIC ${VTK_LIBRARIES} ${CMAKE_BINARY_DIR}/lib/libbiomesh.so Eigen3::Eigen ${JSONCPP_LIBRARIES})