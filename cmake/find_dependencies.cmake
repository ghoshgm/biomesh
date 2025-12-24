include(FindPkgConfig)
include(FetchContent)


find_package(VTK REQUIRED)
if(${VTK_FOUND})
  message(STATUS "Found VTK: ${VTK_DIR} (found version ${VTK_VERSION})")
endif()

find_package(Eigen3 REQUIRED)
if(${Eigen3_FOUND})
  message(STATUS "Found Eigen3: ${Eigen3_DIR} (found version ${Eigen3_VERSION})")
endif()

pkg_check_modules(JSONCPP REQUIRED jsoncpp)
message(STATUS "Found jsoncpp: ${JSONCPP_LIBDIR} (found version ${JSONCPP_VERSION})")

find_package(Boost REQUIRED)

find_package(LibXml2 REQUIRED)
if(${LibXml2_FOUND})
  message(STATUS "Found xml2: ${LIBXML2_INCLUDE_DIRS} (found version ${LIBXML2_VERSION_STRING})")
endif()