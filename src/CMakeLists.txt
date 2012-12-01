SET(SourceFiles
  sensor_connection.cpp
)

add_library (owl-sensor SHARED ${SourceFiles})
target_link_libraries (owl-sensor owl-common)
set (FULLVERSION ${LibOwlSensor_VERSION_MAJOR}.${LibOwlSensor_VERSION_MINOR}.${LibOwlSensor_VERSION_REVISION})
SET_TARGET_PROPERTIES(owl-sensor PROPERTIES VERSION ${FULLVERSION} SOVERSION ${FULLVERSION})

SET(CMAKE_INSTALL_LIBDIR lib CACHE PATH "Output directory for libraries")
INSTALL(TARGETS owl-sensor DESTINATION ${CMAKE_INSTALL_LIBDIR})
