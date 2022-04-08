################################################################################
#
# Copyright (c) The Ultralove contributors (https://github.com/ultralove)
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

cmake_minimum_required(VERSION 3.19)

project(nmcs
  VERSION 1.0.0
  DESCRIPTION "Network Media Control System"
  LANGUAGES ASM C CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_CXX_EXTENSIONS OFF)
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
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
  message(FATAL_ERROR "Supported platforms are Windows, macOS and Ubuntu Linux")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON  CACHE INTERNAL  "")
set(CMAKE_WARN_DEPRECATED           OFF CACHE INTERNAL "")

if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  add_compile_options(-Wno-delete-abstract-non-virtual-dtor)
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
    message(FATAL_ERROR "Darwin builds require clang.")
endif()

message(STATUS "NMCS_TARGET_SYSTEM = " ${NMCS_TARGET_SYSTEM})
include(cmake/${NMCS_TARGET_SYSTEM}.cmake)

set(NMCS_INCLUDE_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/include")
include_directories(${NMCS_INCLUDE_DIRECTORY})

add_subdirectory("src/runtime")
# add_subdirectory("src/model")
# add_subdirectory("src/framework")
