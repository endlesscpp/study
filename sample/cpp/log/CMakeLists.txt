cmake_minimum_required(VERSION 3.5)
project(LOG C CXX)
#enable_testing()

#set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(src)
INCLUDE_DIRECTORIES(include)
add_definitions(-DSPDLOG_FMT_PRINTF)

set(SRC_LIST src/main.cpp)

#message(STATUS "This is BINARY dir " ${BOOTCAMP_BINARY_DIR})
#message(STATUS "This is SOURCE dir " ${BOOTCAMP_SOURCE_DIR})

add_executable(log ${SRC_LIST})

#add_subdirectory(test)
