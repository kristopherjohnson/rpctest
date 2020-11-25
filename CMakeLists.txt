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

set(CMAKE_VERBOSE_MAKEFILE ON)

include(CTest)
enable_testing()

# Use standard C++17 for C++ files.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

# Use C11 standard for C files
set(CMAKE_C_STANDARD 11)

# Set compiler-specific options.
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wno-pointer-sign)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall)
endif()

find_program(RPCGEN rpcgen)
add_custom_command(OUTPUT square_clnt.c square_svc.c square_xdr.c square.h
    COMMAND ${RPCGEN} -C "${CMAKE_CURRENT_SOURCE_DIR}/square.x"
    MAIN_DEPENDENCY square.x
)
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_executable(square_svc
    square_svc.c
    square_xdr.c
    square_proc_1_svc.c
)

add_executable(square_client
    square_clnt.c
    square_xdr.c
    square_client_main.c
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
