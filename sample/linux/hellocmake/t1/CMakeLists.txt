cmake_minimum_required(VERSION 3.9)
project(HELLO C)

set(CMAKE_C_STANDARD 99)

set(SRC_LIST main.c)

message(STATUS "This is BINARY dir " ${HELLO_BINARY_DIR})
message(STATUS "This is SOURCE dir " ${HELLO_SOURCE_DIR})

add_executable(hello ${SRC_LIST})