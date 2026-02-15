
# Gather all header files.
file(GLOB_RECURSE BIOMESH_HEADERS ${CMAKE_CURRENT_SOURCE_DIR} *.hpp *.h *.tpp)

# Gather all source files.
file(GLOB_RECURSE BIOMESH_SOURCES ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

# Build libbiomesh.
add_library(biomesh SHARED ${BIOMESH_SOURCES})
add_library(BIOMESH::biomesh ALIAS biomesh)

message(STATUS ${CMAKE_INSTALL_PREFIX})

include(GNUInstallDirs)
target_include_directories(biomesh 
      PUBLIC 
      "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
      "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>"
      "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

install(TARGETS biomesh 
      EXPORT biomeshTargets
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
      INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES ${BIOMESH_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${PROJECT_BINARY_DIR}/include/biomesh_config.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT biomeshTargets
      FILE biomeshTargets.cmake
      NAMESPACE BIOMESH::
      DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/biomesh
)

include(CMakePackageConfigHelpers)

configure_package_config_file(${CMAKE_SOURCE_DIR}/cmake/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/biomeshConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/biomesh
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/biomeshConfig.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/biomesh
)

target_link_libraries(biomesh PUBLIC
                           ${VTK_LIBRARIES}
                           Eigen3::Eigen
                           ${JSONCPP_LIBRARIES}
                           ${LIBXML2_LIBRARIES}
                           Boost::boost
                     )