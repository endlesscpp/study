cmake_minimum_required(VERSION 3.5.1)
project(HELLO C)

set(CMAKE_C_STANDARD 99)

message(STATUS "This is BINARY dir " ${HELLO_BINARY_DIR})
message(STATUS "This is SOURCE dir " ${HELLO_SOURCE_DIR})

add_subdirectory(src bin)

install(FILES COPYRIGHT README DESTINATION share/doc/hellocmake/t2)
install(PROGRAMS runhello.sh DESTINATION bin)
install(DIRECTORY doc/ DESTINATION share/doc/hellocmake/t2)