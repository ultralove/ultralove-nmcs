
if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  set(EXTRA_LIBRARIES "-framework AppKit" "-framework Carbon" "-framework IOKit" "-framework Security")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 12)
    message(STATUS "Building for x86_64 using clang ${CMAKE_CXX_COMPILER_VERSION}.")
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.11 CACHE INTERNAL "")
    set(CMAKE_OSX_ARCHITECTURES x86_64 CACHE INTERNAL "")
    add_compile_options(-mmacosx-version-min=10.11)
  else()
    message(STATUS "Building for x86_64 and arm64 using clang ${CMAKE_CXX_COMPILER_VERSION}.")
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.15 CACHE INTERNAL "")
    set(CMAKE_OSX_ARCHITECTURES arm64 x86_64 CACHE INTERNAL "")
    add_compile_options(-mmacosx-version-min=10.15)
  endif()
else()
    message(FATAL_ERROR "macOS builds require clang.")
endif()

set(NMCS_SERVER_INCLUDES
  ${NMCS_INCLUDE_DIRECTORY}/nmcs/servercommon.h
  ${NMCS_INCLUDE_DIRECTORY}/nmcs/serverglobals.h
  ${NMCS_INCLUDE_DIRECTORY}/nmcs/serverservice.h
  ${NMCS_INCLUDE_DIRECTORY}/nmcs/serverservicecallback.h
  ${NMCS_INCLUDE_DIRECTORY}/nmcs/serverservicemanager.h
)

set(NMCS_SERVER_SOURCES
  server.cpp
  serverservicemanager.cpp
)

source_group("Header Files" FILES ${NMCS_SERVER_INCLUDES})
source_group("Source Files" FILES ${NMCS_SERVER_SOURCES})

add_library(nmcsserver
  ${NMCS_SERVER_INCLUDES}
  ${NMCS_SERVER_SOURCES}
)

add_dependencies(nmcsserver nmcsmodelv1)
add_dependencies(nmcsserver nmcsmodelv2)
