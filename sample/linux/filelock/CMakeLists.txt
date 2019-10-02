cmake_minimum_required(VERSION 3.14)
project(filelock)

set(CMAKE_CXX_STANDARD 14)

add_executable(filelock main.cpp)
target_link_libraries(filelock pthread rt)