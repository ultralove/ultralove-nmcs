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

find_package(BISON REQUIRED)
if(BISON_FOUND)
    set(NMCS_BISON_COMPILE_FLAGS "--feature=caret")
    message(STATUS "NMCS_BISON_COMPILE_FLAGS = ${NMCS_BISON_COMPILE_FLAGS}")
    BISON_TARGET(compilerparser
        compilerparser.ypp
        ${CMAKE_CURRENT_BINARY_DIR}/compilerparser.cpp
        DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/compilerparser.h
        COMPILE_FLAGS ${NMCS_BISON_COMPILE_FLAGS})
endif()

find_package(FLEX REQUIRED)
if(FLEX_FOUND)
    if(WIN32)
        set(NMCS_FLEX_COMPILE_FLAGS "--batch --yylineno --wincompat")
    else()
        set(NMCS_FLEX_COMPILE_FLAGS "--batch --yylineno")
    endif()
    message(STATUS "NMCS_FLEX_COMPILE_FLAGS = ${NMCS_FLEX_COMPILE_FLAGS}")
    FLEX_TARGET(compilerscanner
        compilerscanner.lpp
        ${CMAKE_CURRENT_BINARY_DIR}/compilerscanner.cpp
        DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/compilerscanner.h
        COMPILE_FLAGS ${NMCS_FLEX_COMPILE_FLAGS})
endif()

add_flex_bison_dependency(compilerscanner compilerparser)

# include generated parser and scanner
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(NMCS_COMPILER_INCLUDES
    compilerast.h
    compilercommon.h
    compilerdriver.h
    compileremittertype.h
)

set(NMCS_COMPILER_SOURCES
    compiler.cpp
    compilerast.cpp
    compilerdriver.cpp
)

add_executable(nmcsc
    ${NMCS_COMPILER_INCLUDES}
    ${NMCS_COMPILER_SOURCES}
    ${BISON_compilerparser_OUTPUTS}
    ${FLEX_compilerscanner_OUTPUTS})

if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    target_link_libraries(nmcsc rpcrt4.lib)
endif()
