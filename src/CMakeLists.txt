
# Gather all header files.
file(GLOB_RECURSE OPENDIHU_HEADERS ${CMAKE_CURRENT_SOURCE_DIR} *.hpp *.h)

# Gather all source files.
file(GLOB_RECURSE OPENDIHU_SOURCES ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

# Build libbiomesh.
add_library(biomesh SHARED ${OPENDIHU_HEADERS} ${OPENDIHU_SOURCES})
target_include_directories(biomesh PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${MPI_CXX_INCLUDE_DIRS})
target_link_libraries(biomesh PUBLIC ${MPI_CXX_LIBRARIES} ${VTK_LIBRARIES})