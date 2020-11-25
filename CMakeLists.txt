# To build everything using this file:
#
#   mkdir build
#   cd build
#   cmake ..
#   make
#
# To run tests, after the above run
#
#   ctest .

cmake_minimum_required(VERSION 3.10)
project(rpctest VERSION 0.1.0)

#set(CMAKE_VERBOSE_MAKEFILE ON)

include(CTest)
enable_testing()

# Use standard C++17 for C++ files.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

# Use C11 standard for C files
set(CMAKE_C_STANDARD 11)

# Set compiler-specific options.
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wno-unused-variable -Wno-pointer-sign -Wno-incompatible-pointer-types)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wno-unused-variable)
endif()

# This has been tested with rpcgen on Linux and on macOS.
find_program(RPCGEN rpcgen)
add_custom_command(
    OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/square_clnt.c"
           "${CMAKE_CURRENT_SOURCE_DIR}/square_svc.c"
	   "${CMAKE_CURRENT_SOURCE_DIR}/square_xdr.c"
	   "${CMAKE_CURRENT_SOURCE_DIR}/square.h"
    COMMAND "${RPCGEN}" -C square.x
    MAIN_DEPENDENCY square.x
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_library(xdrlib OBJECT square_xdr.c)

add_executable(square_svc
    square_svc.c
    square_proc_1_svc.c
    $<TARGET_OBJECTS:xdrlib>
)

add_executable(square_clnt
    square_clnt.c
    square_clnt_main.c
    $<TARGET_OBJECTS:xdrlib>
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
