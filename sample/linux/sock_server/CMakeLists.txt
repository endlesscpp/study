cmake_minimum_required(VERSION 3.5)
project(SOCKSRV C CXX)
#enable_testing()

#set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

#INCLUDE_DIRECTORIES(src)
#INCLUDE_DIRECTORIES(3rd)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
  EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
  )
ENDIF()

set(SRC_LIST epoll_srv.cpp)


add_executable(socksrv ${SRC_LIST})
add_executable(sockcli epoll_client.cpp)
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#add_subdirectory(test)

