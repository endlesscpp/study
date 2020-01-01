cmake_minimum_required(VERSION 3.15)
project(testgperf)

set(CMAKE_CXX_STANDARD 11)

add_executable(testgperf main.cpp)
target_link_libraries(testgperf tcmalloc)