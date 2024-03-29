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

include(FetchContent)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
add_compile_definitions("_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS")

set(FETCHCONTENT_QUIET   ON)
set(FETCHCONTENT_VERBOSE OFF)

FetchContent_Declare(libcli11
  GIT_REPOSITORY "https://github.com/CLIUtils/CLI11.git"
  GIT_SHALLOW  ON
  GIT_PROGRESS OFF
  GIT_TAG ${LIBCLI11_VERSION_TAG}
)
FetchContent_GetProperties(libcli11)
if(NOT libcli11_POPULATED)
  FetchContent_Populate(libcli11)
  set(LIBCLI11_INCLUDE_PATH ${libcli11_SOURCE_DIR}/include)
  set(BUILD_SHARED_LIBS     OFF CACHE INTERNAL "")
  set(CLI11_SINGLE_FILE     OFF CACHE INTERNAL "")
  set(CLI11_BUILD_DOCS      OFF CACHE INTERNAL "")
  set(CLI11_BUILD_TESTS     OFF CACHE INTERNAL "")
  set(CLI11_BUILD_EXAMPLES  OFF CACHE INTERNAL "")
  add_subdirectory(${libcli11_SOURCE_DIR} ${libcli11_BINARY_DIR})
endif()

FetchContent_Declare(libz
  GIT_REPOSITORY https://github.com/madler/zlib.git
  GIT_SHALLOW  ON
  GIT_PROGRESS OFF
  GIT_TAG ${LIBZ_VERSION_TAG}
)
FetchContent_GetProperties(libz)
if(NOT libz_POPULATED)
  FetchContent_Populate(libz)
  set(LIBZ_INCLUDE_PATH ${libz_BINARY_DIR} ${libz_SOURCE_DIR} ${libz_SOURCE_DIR}/contrib/minizip)
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(LIBZ_LIBRARY_PATH ${libz_BINARY_DIR}/zlibstaticd.lib)
  else()
    set(LIBZ_LIBRARY_PATH ${libz_BINARY_DIR}/zlibstatic.lib)
  endif()
  set(LIBZ_SOURCE_PATH  ${libz_SOURCE_DIR})
  set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
  set(SKIP_INSTALL_ALL  ON CACHE INTERNAL "")
  add_subdirectory(${libz_SOURCE_DIR} ${libz_BINARY_DIR})
endif()

FetchContent_Declare(libcurl
  GIT_REPOSITORY https://github.com/curl/curl.git
  GIT_SHALLOW  ON
  GIT_PROGRESS OFF
  GIT_TAG ${LIBCURL_VERSION_TAG}
)
FetchContent_GetProperties(libcurl)
if(NOT libcurl_POPULATED)
  FetchContent_Populate(libcurl)
  set(LIBCURL_INCLUDE_PATH ${libcurl_SOURCE_DIR}/include)
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(LIBCURL_LIBRARY_PATH ${libcurl_BINARY_DIR}/lib/libcurl-d.lib)
  else()
    set(LIBCURL_LIBRARY_PATH ${libcurl_BINARY_DIR}/lib/libcurl.lib)
  endif()
  set(BUILD_SHARED_LIBS   OFF CACHE INTERNAL "")
  set(BUILD_CURL_EXE      OFF CACHE INTERNAL "")
  set(BUILD_BINDINGS      OFF CACHE INTERNAL "")
  set(BUILD_TESTING       OFF CACHE INTERNAL "")
  set(ENABLE_MANUAL       OFF CACHE INTERNAL "")
  set(HTTP_ONLY           ON CACHE INTERNAL "")
  set(CURL_USE_SCHANNEL   ON CACHE INTERNAL "")
  add_subdirectory(${libcurl_SOURCE_DIR} ${libcurl_BINARY_DIR})
endif()

FetchContent_Declare(libxml2
  GIT_REPOSITORY https://github.com/GNOME/libxml2.git
  GIT_SHALLOW  ON
  GIT_PROGRESS OFF
  GIT_TAG ${LIBXML2_VERSION_TAG}
)
FetchContent_GetProperties(libxml2)
if(NOT libxml2_POPULATED)
  FetchContent_Populate(libxml2)
  set(LIBXML2_INCLUDE_PATH  ${libxml2_SOURCE_DIR})
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(LIBXML2_LIBRARY_PATH ${libxml2_BINARY_DIR}/libxml2sd.lib)
  else()
    set(LIBXML2_LIBRARY_PATH ${libxml2_BINARY_DIR}/libxml2s.lib)
  endif()
  set(BUILD_SHARED_LIBS     OFF CACHE INTERNAL "")
  set(LIBXML2_WITH_ICONV    OFF CACHE INTERNAL "")
  set(LIBXML2_WITH_ICU      OFF CACHE INTERNAL "")
  set(LIBXML2_WITH_LEGACY   OFF CACHE INTERNAL "")
  set(LIBXML2_WITH_LZMA     OFF CACHE INTERNAL "")
  set(LIBXML2_WITH_PROGRAMS OFF CACHE INTERNAL "")
  set(LIBXML2_WITH_PYTHON   OFF CACHE INTERNAL "")
  set(LIBXML2_WITH_TESTS    OFF CACHE INTERNAL "")
  set(LIBXML2_WITH_DEBUG    OFF CACHE INTERNAL "")
  set(LIBXML2_WITH_ZLIB     OFF CACHE INTERNAL "")
  add_subdirectory(${libxml2_SOURCE_DIR} ${libxml2_BINARY_DIR})
endif()

FetchContent_Declare(libsimdutf
  GIT_REPOSITORY https://github.com/simdutf/simdutf.git
  GIT_SHALLOW  ON
  GIT_PROGRESS OFF
  GIT_TAG ${LIBSIMDUTF_VERSION_TAG}
)
FetchContent_GetProperties(libsimdutf)
if(NOT libsimdutf_POPULATED)
  FetchContent_Populate(libsimdutf)
  set(LIBSIMDUTF_INCLUDE_PATH ${libsimdutf_SOURCE_DIR}/include)
  set(LIBSIMDUTF_LIBRARY_PATH ${libsimdutf_BINARY_DIR}/src/simdutf.lib)
  set(BUILD_SHARED_LIBS       OFF CACHE INTERNAL "")
  set(SIMDUTF_TESTS           OFF CACHE INTERNAL "")
  set(SIMDUTF_BENCHMARKS      OFF CACHE INTERNAL "")
  set(SIMDUTF_TOOLS           OFF CACHE INTERNAL "")
  set(SIMDUTF_ICONV           OFF CACHE INTERNAL "")
  add_subdirectory(${libsimdutf_SOURCE_DIR} ${libsimdutf_BINARY_DIR})
endif()

FetchContent_Declare(libsimdjson
  GIT_REPOSITORY https://github.com/simdjson/simdjson.git
  GIT_SHALLOW  ON
  GIT_PROGRESS OFF
  GIT_TAG ${LIBSIMDJSON_VERSION_TAG}
)
FetchContent_GetProperties(libsimdjson)
if(NOT libsimdjson_POPULATED)
  FetchContent_Populate(libsimdjson)
  set(LIBSIMDJSON_INCLUDE_PATH        ${libsimdjson_SOURCE_DIR}/include)
  set(LIBSIMDJSON_LIBRARY_PATH        ${libsimdjson_BINARY_DIR}/simdjson.lib)
  set(BUILD_SHARED_LIBS               OFF CACHE INTERNAL "")
  set(SIMDJSON_DEVELOPER_MODE         OFF CACHE INTERNAL "")
  set(SIMDJSON_DISABLE_DEPRECATED_API OFF CACHE INTERNAL "")
  set(SIMDJSON_ALLOW_DOWNLOADS        OFF CACHE INTERNAL "")
  set(SIMDJSON_ENABLE_FUZZING         OFF CACHE INTERNAL "")
  add_subdirectory(${libsimdjson_SOURCE_DIR} ${libsimdjson_BINARY_DIR})
endif()

FetchContent_Declare(libspdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_SHALLOW  ON
  GIT_PROGRESS OFF
  GIT_TAG ${LIBSPDLOG_VERSION_TAG}
)
FetchContent_GetProperties(libspdlog)
if(NOT libspdlog_POPULATED)
  FetchContent_Populate(libspdlog)
  set(LIBSPDLOG_INCLUDE_PATH ${libspdlog_SOURCE_DIR}/include)
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(LIBSPDLOG_LIBRARY_PATH ${libspdlog_BINARY_DIR}/spdlogd.lib)
  else()
    set(LIBSPDLOG_LIBRARY_PATH ${libspdlog_BINARY_DIR}/spdlog.lib)
  endif()
  set(BUILD_SHARED_LIBS    OFF CACHE INTERNAL "")
  set(SPDLOG_BUILD_EXAMPLE OFF CACHE INTERNAL "")
  add_subdirectory(${libspdlog_SOURCE_DIR} ${libspdlog_BINARY_DIR})
endif()

FetchContent_Declare(libwhisper
  GIT_REPOSITORY https://github.com/ggerganov/whisper.cpp.git
  GIT_SHALLOW  ON
  GIT_PROGRESS OFF
  GIT_TAG ${LIBWHISPER_VERSION_TAG}
)
FetchContent_GetProperties(libwhisper)
if(NOT libwhisper_POPULATED)
  FetchContent_Populate(libwhisper)
  set(LIBWHISPER_INCLUDE_PATH        ${libwhisper_SOURCE_DIR})
  set(LIBWHISPER_LIBRARY_PATH        ${libwhisper_BINARY_DIR}/whisper.lib)
  set(WHISPER_ALL_WARNINGS           OFF CACHE INTERNAL "")
  set(WHISPER_ALL_WARNINGS_3RD_PARTY OFF CACHE INTERNAL "")
  set(WHISPER_BUILD_TESTS            OFF CACHE INTERNAL "")
  set(WHISPER_BUILD_EXAMPLES         OFF CACHE INTERNAL "")
  set(WHISPER_PERF                   OFF CACHE INTERNAL "")
  add_subdirectory(${libwhisper_SOURCE_DIR} ${libwhisper_BINARY_DIR})
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
