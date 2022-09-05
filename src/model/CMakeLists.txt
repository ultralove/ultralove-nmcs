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

set (NMCS_MODEL_INCLUDES
  modelcommon.h
)

set(NMCS_MODEL_SOURCES
  model.cpp
  modelfabric.cpp
)

set(NMCS_MODEL_DEPENDENCIES
  nmcsruntime
)

add_library(nmcsmodel ${NMCS_MODEL_INCLUDES} ${NMCS_MODEL_SOURCES})

add_dependencies(nmcsmodel ${NMCS_MODEL_DEPENDENCIES})
target_link_libraries(nmcsmodel ${NMCS_MODEL_DEPENDENCIES})

set_target_properties(nmcsmodel PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(nmcsmodel PROPERTIES SOVERSION ${PROJECT_VERSION})
set_target_properties(nmcsmodel PROPERTIES OUTPUT_NAME "nmcs-model")

target_precompile_headers(nmcsmodel PRIVATE
  ${NMCS_INCLUDE_DIRECTORY}/nmcs/common.h
  ${NMCS_INCLUDE_DIRECTORY}/nmcs/platform.h
  ${NMCS_INCLUDE_DIRECTORY}/nmcs/runtime.h
  modelcommon.h
)
