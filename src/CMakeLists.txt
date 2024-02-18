
# Gather all header files.
file(GLOB_RECURSE BIOMESH_HEADERS ${CMAKE_CURRENT_SOURCE_DIR} *.hpp *.h)

# Gather all source files.
file(GLOB_RECURSE BIOMESH_SOURCES ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

# Build libbiomesh.
add_library(biomesh SHARED ${BIOMESH_HEADERS} ${BIOMESH_SOURCES})
target_include_directories(biomesh PUBLIC ${PROJECT_SOURCE_DIR}/src
                                          ${PROJECT_BINARY_DIR}/include
                                          ${MPI_CXX_INCLUDE_DIRS}
                          )
target_link_libraries(biomesh PUBLIC ${MPI_CXX_LIBRARIES} ${VTK_LIBRARIES})