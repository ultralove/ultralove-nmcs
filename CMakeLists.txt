################################################################################
#
# Copyright (c) ultralove contributors (https://github.com/ultralove)
#
# The MIT License (MIT)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
################################################################################

cmake_minimum_required(VERSION 3.23)

project(nmcs
  VERSION 2.0.0
  DESCRIPTION "Network Media Control System"
  LANGUAGES ASM C CXX
)

set(NMCS_VERSION "${PROJECT_VERSION}")
if(NOT DEFINED NMCS_BUILD_ID)
  set(NMCS_BUILD_ID 0)
endif()
string(TIMESTAMP NMCS_BUILD_TIMESTAMP "%Y-%m-%d %H:%M:%S")
configure_file(version.h.in version.h)
include_directories(${CMAKE_BINARY_DIR})

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

if(WIN32)
    set(NMCS_TARGET_SYSTEM "windows")
elseif(APPLE)
    set(NMCS_TARGET_SYSTEM "darwin")
elseif(UNIX)
  execute_process(COMMAND uname -a RESULT_VARIABLE UNAME_RESULT OUTPUT_VARIABLE UNAME_OUTPUT OUTPUT_STRIP_TRAILING_WHITESPACE)
  if(UNAME_RESULT EQUAL 0)
    if(${UNAME_OUTPUT} MATCHES "[L|l]inux")
        set(NMCS_TARGET_SYSTEM "linux")
    else()
      message(STATUS "Unsupported platform: " ${UNAME_OUTPUT})
      message(FATAL_ERROR "Supported platforms are Windows, Darwin and Linux")
    endif()
  else()
    message(FATAL_ERROR "Failed to run uname, result: ${UNAME_RESULT}")
  endif()
else()
  message(FATAL_ERROR "Supported platforms are Windows, Darwin and Linux")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON  CACHE INTERNAL "")
set(CMAKE_WARN_DEPRECATED           OFF CACHE INTERNAL "")

if(BUILD_SHARED_LIBS)
  add_compile_definitions("NMCS_SHARED=1")
endif()

if(NMCS_TARGET_SYSTEM STREQUAL "darwin")
  if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    set(EXTRA_LIBRARIES "-framework AppKit" "-framework Carbon" "-framework IOKit" "-framework Security")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 12)
      message(STATUS "Building for x86_64 using clang ${CMAKE_CXX_COMPILER_VERSION}.")
      set(CMAKE_OSX_DEPLOYMENT_TARGET 10.15 CACHE INTERNAL "")
      set(CMAKE_OSX_ARCHITECTURES x86_64 CACHE INTERNAL "")
      add_compile_options(-mmacosx-version-min=10.15)
    else()
      message(STATUS "Building for x86_64 and arm64 using clang ${CMAKE_CXX_COMPILER_VERSION}.")
      set(CMAKE_OSX_DEPLOYMENT_TARGET 13.0 CACHE INTERNAL "")
      set(CMAKE_OSX_ARCHITECTURES arm64 x86_64 CACHE INTERNAL "")
      add_compile_options(-mmacosx-version-min=13.0)
    endif()
  endif()
endif()

set(LIBCLI11_VERSION_TAG    "v2.3.2")
set(LIBZ_VERSION_TAG        "v1.2.13")
set(LIBGRPC_VERSION_TAG     "v1.54.0")
set(LIBCURL_VERSION_TAG     "curl-8_0_1")
set(LIBXML2_VERSION_TAG     "v2.10.3")
set(LIBSIMDJSON_VERSION_TAG "v3.1.6")
set(LIBSPDLOG_VERSION_TAG   "v1.11.0")
set(LIBSIMDUTF_VERSION_TAG  "v3.2.5")
set(LIBWHISPER_VERSION_TAG  "v1.2.1")

message(STATUS "Configuring dependencies for ${NMCS_TARGET_SYSTEM}...")
include(cmake/${NMCS_TARGET_SYSTEM}.cmake)
message(STATUS "Done configuring dependencies for ${NMCS_TARGET_SYSTEM}.")

message(STATUS "LIBCLI11_INCLUDE_PATH    = ${LIBCLI11_INCLUDE_PATH}")
message(STATUS "LIBCLI11_LIBRARY_PATH    = ${LIBCLI11_LIBRARY_PATH}")
message(STATUS "LIBZ_INCLUDE_PATH        = ${LIBZ_INCLUDE_PATH}")
message(STATUS "LIBZ_LIBRARY_PATH        = ${LIBZ_LIBRARY_PATH}")
message(STATUS "LIBGRPC_INCLUDE_PATH     = ${LIBGRPC_INCLUDE_PATH}")
message(STATUS "LIBGRPC_LIBRARY_PATH     = ${LIBGRPC_LIBRARY_PATH}")
message(STATUS "LIBCURL_INCLUDE_PATH     = ${LIBCURL_INCLUDE_PATH}")
message(STATUS "LIBCURL_LIBRARY_PATH     = ${LIBCURL_LIBRARY_PATH}")
message(STATUS "LIBXML2_INCLUDE_PATH     = ${LIBXML2_INCLUDE_PATH}")
message(STATUS "LIBXML2_LIBRARY_PATH     = ${LIBXML2_LIBRARY_PATH}")
message(STATUS "LIBSIMDJSON_INCLUDE_PATH = ${LIBSIMDJSON_INCLUDE_PATH}")
message(STATUS "LIBSIMDJSON_LIBRARY_PATH = ${LIBSIMDJSON_LIBRARY_PATH}")
message(STATUS "LIBSPDLOG_INCLUDE_PATH   = ${LIBSPDLOG_INCLUDE_PATH}")
message(STATUS "LIBSPDLOG_LIBRARY_PATH   = ${LIBSPDLOG_LIBRARY_PATH}")
message(STATUS "LIBSIMDUTF_INCLUDE_PATH  = ${LIBSIMDUTF_INCLUDE_PATH}")
message(STATUS "LIBSIMDUTF_LIBRARY_PATH  = ${LIBSIMDUTF_LIBRARY_PATH}")
message(STATUS "LIBWHISPER_INCLUDE_PATH  = ${LIBWHISPER_INCLUDE_PATH}")
message(STATUS "LIBWHISPER_LIBRARY_PATH  = ${LIBWHISPER_LIBRARY_PATH}")

set(NMCS_INCLUDE_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/include")
include_directories(${NMCS_INCLUDE_DIRECTORY})

add_subdirectory("src/platform")
add_subdirectory("src/runtime")
add_subdirectory("src/model")
add_subdirectory("src/server")
add_subdirectory("src/agent")
add_subdirectory("src/client")

# install(TARGETS nmcsplatform nmcsruntime nmcsmodel nmcsserver nmcsagent nmcsclient
# install(TARGETS nmcsplatform
#   RUNTIME DESTINATION "bin"
#   LIBRARY DESTINATION "lib"
#   ARCHIVE DESTINATION "lib/${PROJECT_NAME}"
# )
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include" DESTINATION include)

set(CPACK_PACKAGE_NAME "nmcs")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${NMCS_VERSION}-build${NMCS_BUILD_ID}-${NMCS_TARGET_SYSTEM}")
set(CPACK_PACKAGE_VENDOR "ultralove")
set(CPACK_PACKAGE_CONTACT "staff@ultralove.io")
set(CPACK_PACKAGE_URL "https://github.com/ultralove/ultralove-nmcs")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "network media control system")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_GENERATOR "ZIP;TGZ")
set(CPACK_THREADS 0)
include(CPack)
