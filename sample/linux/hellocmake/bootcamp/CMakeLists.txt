cmake_minimum_required(VERSION 3.5)
project(BOOTCAMP C CXX)
enable_testing()

#set(CMAKE_C_STANDARD 99)

INCLUDE_DIRECTORIES(src)
INCLUDE_DIRECTORIES(3rd)

set(SRC_LIST src/main.c
    src/add.c)

#message(STATUS "This is BINARY dir " ${BOOTCAMP_BINARY_DIR})
#message(STATUS "This is SOURCE dir " ${BOOTCAMP_SOURCE_DIR})

add_executable(bootcamp ${SRC_LIST})

add_subdirectory(test)
