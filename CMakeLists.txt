cmake_minimum_required (VERSION 2.6)
project (LibOwlSensorC++)

# The version number.
set (LibOwlSensor_VERSION_MAJOR 1)
set (LibOwlSensor_VERSION_MINOR 0)
set (LibOwlSensor_VERSION_REVISION 0)

set(CMAKE_CXX_FLAGS "-O2 -std=c++0x -Wall -Wextra -Wno-sign-compare")

#SUBDIRS(src)
#add_subdirectory ("${PROJECT_SOURCE_DIR}/src")

include_directories ("${LibOwlSensorC++_SOURCE_DIR}/include")
add_subdirectory (include)
add_subdirectory (src)

#Set the correct library directory suffix
if(NOT DEFINED LIB_SUFFIX)
  get_property(LIB64 GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS)
  if (${LIB64} STREQUAL "TRUE")
    set(LIBSUFFIX 64)
  else()
    set(LIBSUFFIX "")
  endif()
  set(LIB_SUFFIX ${LIBSUFFIX} CACHE STRING "lib directory suffix")
endif()

## the following are directories where stuff will be installed to
SET(PKGCONFIG_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/pkgconfig/" CACHE STRING "Base directory for pkgconfig files")
SET(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include/owl/" CACHE PATH "The subdirectory to the header prefix")

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/owl-sensor.pc.cmake ${CMAKE_CURRENT_BINARY_DIR}/owl-sensor.pc @ONLY)
INSTALL( FILES ${CMAKE_CURRENT_BINARY_DIR}/owl-sensor.pc DESTINATION ${PKGCONFIG_INSTALL_PREFIX})

# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

