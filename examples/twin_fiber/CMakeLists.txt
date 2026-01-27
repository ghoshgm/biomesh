
add_executable(twin_fiber twin_fiber.cpp)
target_include_directories(twin_fiber PUBLIC ${PETSC_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/include)
target_link_libraries(twin_fiber PUBLIC ${VTK_LIBRARIES} ${CMAKE_BINARY_DIR}/lib/libbiomesh.so Eigen3::Eigen ${JSONCPP_LIBRARIES})