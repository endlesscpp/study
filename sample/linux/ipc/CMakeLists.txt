cmake_minimum_required(VERSION 3.15)
project(ipc)

set(CMAKE_CXX_STANDARD 14)

add_executable(ipc main.cpp sem_v5.cpp sem_v5.h)