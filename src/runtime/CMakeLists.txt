
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

set(NMCS_RUNTIME_INCLUDES
  ${NMCS_INCLUDE_DIRECTORY}/nmcs/runtimecommon.h
  ${NMCS_INCLUDE_DIRECTORY}/nmcs/runtimedatetime.h
  ${NMCS_INCLUDE_DIRECTORY}/nmcs/runtimeglobals.h
  ${NMCS_INCLUDE_DIRECTORY}/nmcs/runtimeguid.h
  ${NMCS_INCLUDE_DIRECTORY}/nmcs/runtimesharedobject.h
  ${NMCS_INCLUDE_DIRECTORY}/nmcs/runtimestream.h
  ${NMCS_INCLUDE_DIRECTORY}/nmcs/runtimestring.h
)

set(NMCS_RUNTIME_SOURCES
  runtimeguid.cpp
  runtimesharedobject.cpp
  runtimestream.cpp
  runtimestring.cpp
)

source_group("Header Files" FILES ${NMCS_RUNTIME_INCLUDES})
source_group("Source Files" FILES ${NMCS_RUNTIME_SOURCES})

add_library(nmcsruntime
  ${NMCS_RUNTIME_INCLUDES}
  ${NMCS_RUNTIME_SOURCES}
)
