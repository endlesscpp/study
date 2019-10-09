cmake_minimum_required(VERSION 3.15)
project(gen_core C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(gen_core
        main.c)
