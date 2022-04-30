################################################################################
#
# Copyright (c) Ultralove NMCS Contributors (https://github.com/ultralove)
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

if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

FetchContent_Declare(CLI11
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
  GIT_TAG v2.2.0
)
FetchContent_GetProperties(cli11)
if(NOT cli11_POPULATED)
  FetchContent_Populate(cli11)
  add_subdirectory(${cli11_SOURCE_DIR} ${cli11_BINARY_DIR})
  set(CLI11_INCLUDES ${cli11_SOURCE_DIR}/include)
endif()

include_directories(${CLI11_INCLUDES})

set(NMCS_COMPILER_INCLUDES
    compilerast.h
    compilerdriver.h
    compileremittertype.h
)

set(NMCS_COMPILER_SOURCES
    compiler.cpp
    compilerast.cpp
    compilerdriver.cpp
)

set(NMCS_COMPILER_DEPENDENCIES
  nmcsmodel
)

add_executable(nmcsc ${NMCS_COMPILER_INCLUDES} ${NMCS_COMPILER_SOURCES})
add_dependencies(nmcsc ${NMCS_COMPILER_DEPENDENCIES})
target_link_libraries(nmcsc ${NMCS_COMPILER_DEPENDENCIES})
set_target_properties(nmcsc PROPERTIES VERSION ${PROJECT_VERSION})
