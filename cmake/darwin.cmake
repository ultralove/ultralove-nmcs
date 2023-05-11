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

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set(FETCHCONTENT_QUIET                ON)
set(FETCHCONTENT_VERBOSE              OFF)

FetchContent_Declare(cli11
  GIT_REPOSITORY "https://github.com/CLIUtils/CLI11.git"
  GIT_SHALLOW  ON
  GIT_PROGRESS ON
  GIT_TAG ${LIBCLI11_VERSION_TAG}
)
FetchContent_GetProperties(cli11)
if(NOT cli11_POPULATED)
  FetchContent_Populate(cli11)
  set(LIBCLI11_INCLUDE_PATH  ${cli11_SOURCE_DIR}/include)
  set(BUILD_SHARED_LIBS_SAVE ${BUILD_SHARED_LIBS})
  set(BUILD_SHARED_LIBS      OFF)
  set(CLI11_SINGLE_FILE      OFF)
  set(CLI11_BUILD_DOCS       OFF)
  set(CLI11_BUILD_TESTS      OFF)
  set(CLI11_BUILD_EXAMPLES   OFF)
  add_subdirectory(${cli11_SOURCE_DIR} ${cli11_BINARY_DIR})
  set(BUILD_SHARED_LIBS      ${BUILD_SHARED_LIBS_SAVE})
endif()

set(LIBZ_LIBRARY libz)
FetchContent_Declare(libz
  GIT_REPOSITORY https://github.com/madler/zlib.git
  GIT_SHALLOW  ON
  GIT_PROGRESS OFF
  GIT_TAG ${LIBZ_VERSION_TAG}
)
FetchContent_GetProperties(libz)
if(NOT libz_POPULATED)
  FetchContent_Populate(libz)
  set(LIBZ_INCLUDE_PATH      ${libz_BINARY_DIR} ${libz_SOURCE_DIR} ${libz_SOURCE_DIR}/contrib/minizip)
  set(LIBZ_LIBRARY_PATH      ${libz_BINARY_DIR}/libz.a)
  set(LIBZ_SOURCE_PATH       ${libz_SOURCE_DIR})
  set(BUILD_SHARED_LIBS_SAVE ${BUILD_SHARED_LIBS})
  set(BUILD_SHARED_LIBS      OFF)
  set(SKIP_INSTALL_ALL       ON)
  add_subdirectory(${libz_SOURCE_DIR} ${libz_BINARY_DIR})
  set(BUILD_SHARED_LIBS      ${BUILD_SHARED_LIBS_SAVE})
endif()

set(LIBCURL_LIBRARY libcurl)
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
    set(LIBCURL_LIBRARY_PATH ${libcurl_BINARY_DIR}/lib/libcurl-d.a)
  else()
    set(LIBCURL_LIBRARY_PATH ${libcurl_BINARY_DIR}/lib/libcurl.a)
  endif()
  set(BUILD_SHARED_LIBS_SAVE ${BUILD_SHARED_LIBS})
  set(BUILD_SHARED_LIBS      OFF)
  set(BUILD_CURL_EXE         OFF)
  set(BUILD_BINDINGS         OFF)
  set(BUILD_TESTING          OFF)
  set(CURL_ENABLE_SSL        ON)
  set(CURL_USE_SECTRANSP     ON)
  set(CURL_CA_PATH           auto)
  set(CURL_DISABLE_LDAP      ON)
  set(CURL_DISABLE_LDAPS     ON)
  set(CURL_DISABLE_NTLM      ON)
  set(CURL_DISABLE_ALTSVC    ON)
  set(ENABLE_IPV6            ON)
  set(ENABLE_MANUAL          OFF)
  set(HTTP_ONLY              ON)
  set(USE_UNIX_SOCKETS       OFF)
  add_subdirectory(${libcurl_SOURCE_DIR} ${libcurl_BINARY_DIR})
  set(BUILD_SHARED_LIBS      ${BUILD_SHARED_LIBS_SAVE})
endif()

set(LIBXML2_LIBRARY LibXml2)
FetchContent_Declare(libxml2
  GIT_REPOSITORY https://github.com/GNOME/libxml2.git
  GIT_SHALLOW  ON
  GIT_PROGRESS OFF
  GIT_TAG ${LIBXML2_VERSION_TAG}
)
FetchContent_GetProperties(libxml2)
if(NOT libxml2_POPULATED)
  FetchContent_Populate(libxml2)
  set(LIBXML2_INCLUDE_PATH   ${libxml2_SOURCE_DIR})
  set(LIBXML2_LIBRARY_PATH   ${libxml2_BINARY_DIR}/libxml2.a)
  set(BUILD_SHARED_LIBS_SAVE ${BUILD_SHARED_LIBS})
  set(BUILD_SHARED_LIBS      OFF)
  set(LIBXML2_WITH_LEGACY    OFF)
  set(LIBXML2_WITH_LZMA      OFF)
  set(LIBXML2_WITH_PROGRAMS  OFF)
  set(LIBXML2_WITH_PYTHON    OFF)
  set(LIBXML2_WITH_TESTS     OFF)
  set(LIBXML2_WITH_DEBUG     OFF)
  add_subdirectory(${libxml2_SOURCE_DIR} ${libxml2_BINARY_DIR})
  set(BUILD_SHARED_LIBS      ${BUILD_SHARED_LIBS_SAVE})
endif()

set(LIBSIMDJSON_LIBRARY simdjson)
FetchContent_Declare(simdjson
  GIT_REPOSITORY https://github.com/simdjson/simdjson.git
  GIT_SHALLOW  ON
  GIT_PROGRESS OFF
  GIT_TAG ${LIBSIMDJSON_VERSION_TAG}
)
FetchContent_GetProperties(simdjson)
if(NOT simdjson_POPULATED)
  FetchContent_Populate(simdjson)
  set(LIBSIMDJSON_INCLUDE_PATH        ${simdjson_SOURCE_DIR}/include)
  set(LIBSIMDJSON_LIBRARY_PATH        ${simdjson_BINARY_DIR}/libsimdjson.a)
  set(BUILD_SHARED_LIBS_SAVE          ${BUILD_SHARED_LIBS})
  set(BUILD_SHARED_LIBS               OFF)
  set(SIMDJSON_DEVELOPER_MODE         OFF)
  set(SIMDJSON_DISABLE_DEPRECATED_API OFF)
  set(SIMDJSON_ALLOW_DOWNLOADS        OFF)
  set(SIMDJSON_ENABLE_FUZZING         OFF)
  add_subdirectory(${simdjson_SOURCE_DIR} ${simdjson_BINARY_DIR})
  set(BUILD_SHARED_LIBS               ${BUILD_SHARED_LIBS_SAVE})
endif()

set(LIBSPDLOG_LIBRARY spdlog)
FetchContent_Declare(spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_SHALLOW  ON
  GIT_PROGRESS OFF
  GIT_TAG ${LIBSPDLOG_VERSION_TAG}
)
FetchContent_GetProperties(spdlog)
if(NOT spdlog_POPULATED)
  FetchContent_Populate(spdlog)
  set(LIBSPDLOG_INCLUDE_PATH ${spdlog_SOURCE_DIR}/include)
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(LIBSPDLOG_LIBRARY_PATH ${spdlog_BINARY_DIR}/libspdlogd.a)
  else()
    set(LIBSPDLOG_LIBRARY_PATH ${spdlog_BINARY_DIR}/libspdlog.a)
  endif()
  set(BUILD_SHARED_LIBS_SAVE ${BUILD_SHARED_LIBS})
  set(BUILD_SHARED_LIBS      OFF)
  set(SPDLOG_BUILD_EXAMPLE   OFF)
  add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
  set(BUILD_SHARED_LIBS      ${BUILD_SHARED_LIBS_SAVE})
endif()

set(LIBSIMDUTF_LIBRARY simdutf)
FetchContent_Declare(simdutf
  GIT_REPOSITORY https://github.com/simdutf/simdutf.git
  GIT_SHALLOW  ON
  GIT_PROGRESS OFF
  GIT_TAG ${LIBSIMDUTF_VERSION_TAG}
)
FetchContent_GetProperties(simdutf)
if(NOT simdutf_POPULATED)
  FetchContent_Populate(simdutf)
  set(LIBSIMDUTF_INCLUDE_PATH ${simdutf_SOURCE_DIR}/include)
  set(LIBSIMDUTF_LIBRARY_PATH ${simdutf_BINARY_DIR}/src/libsimdutf.a)
  set(BUILD_SHARED_LIBS_SAVE  ${BUILD_SHARED_LIBS})
  set(BUILD_SHARED_LIBS       OFF)
  set(SIMDUTF_TESTS           OFF)
  set(SIMDUTF_BENCHMARKS      OFF)
  set(SIMDUTF_TOOLS           OFF)
  set(SIMDUTF_ICONV           OFF)
  add_subdirectory(${simdutf_SOURCE_DIR} ${simdutf_BINARY_DIR})
  set(BUILD_SHARED_LIBS       ${BUILD_SHARED_LIBS_SAVE})
endif()

set(LIBWHISPER_LIBRARY whisper.cpp)
FetchContent_Declare(whisper.cpp
  GIT_REPOSITORY https://github.com/ggerganov/whisper.cpp.git
  GIT_SHALLOW  ON
  GIT_PROGRESS OFF
  GIT_TAG ${LIBWHISPER_VERSION_TAG}
)
FetchContent_GetProperties(whisper.cpp)
if(NOT whisper.cpp_POPULATED)
  FetchContent_Populate(whisper.cpp)
  set(LIBWHISPER_INCLUDE_PATH        ${whisper.cpp_SOURCE_DIR})
  set(LIBWHISPER_LIBRARY_PATH        ${whisper.cpp_BINARY_DIR}/libwhisper.a)
  set(BUILD_SHARED_LIBS_SAVE         ${BUILD_SHARED_LIBS})
  set(BUILD_SHARED_LIBS              OFF)
  set(WHISPER_ALL_WARNINGS           OFF)
  set(WHISPER_ALL_WARNINGS_3RD_PARTY OFF)
  set(WHISPER_BUILD_TESTS            OFF)
  set(WHISPER_BUILD_EXAMPLES         OFF)
  set(WHISPER_PERF                   OFF)
  add_subdirectory(${whisper.cpp_SOURCE_DIR} ${whisper.cpp_BINARY_DIR})
  set(BUILD_SHARED_LIBS              ${BUILD_SHARED_LIBS_SAVE})
endif()

# set(LIBGRPC_LIBRARY grpc)
# FetchContent_Declare(grpc
#   GIT_REPOSITORY https://github.com/grpc/grpc.git
#   GIT_SHALLOW  ON
#   GIT_PROGRESS OFF
#   GIT_TAG ${LIBGRPC_VERSION_TAG}
# )
# FetchContent_GetProperties(grpc)
# if(NOT grpc_POPULATED)
#   FetchContent_Populate(grpc)
#   set(LIBGRPC_INCLUDE_PATH      ${grpc_BINARY_DIR} ${grpc_SOURCE_DIR})
#   set(LIBGRPC_LIBRARY_PATH      ${grpc_BINARY_DIR}/libgrpc.a)
#   set(BUILD_SHARED_LIBS_SAVE ${BUILD_SHARED_LIBS})
#   set(BUILD_SHARED_LIBS      OFF)
#   set(SKIP_INSTALL_ALL       ON)
#   add_subdirectory(${grpc_SOURCE_DIR} ${grpc_BINARY_DIR})
#   set(BUILD_SHARED_LIBS      ${BUILD_SHARED_LIBS_SAVE})
# endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

message(STATUS "CHECKPOINT_1")
