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
target_precompile_headers(nmcsc REUSE_FROM nmcsprecomp)
