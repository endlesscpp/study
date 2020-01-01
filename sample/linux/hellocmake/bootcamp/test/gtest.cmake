cmake_minimum_required(VERSION 2.8.2)

#project(googletest-download NONE)

include(ExternalProject)
  #BUILD_COMMAND     ""
  #CONFIGURE_COMMAND "${CMAKE_COMMAND}" ../googletest-src
MESSAGE(STATUS "make_cmd = ${MAKE_COMMAND}")
ExternalProject_Add(googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           master
  SOURCE_DIR        "${CMAKE_CURRENT_BINARY_DIR}/googletest-src"
  BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/googletest-build"
  CONFIGURE_COMMAND "${CMAKE_COMMAND}" "${CMAKE_CURRENT_BINARY_DIR}/googletest-src"
  CMAKE_ARGS        "-Dgtest_force_shared_crt=ON
                     -DBUILD_GTEST=ON"
  BUILD_COMMAND     "${CMAKE_COMMAND}" --build .
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Get_Property(googletest source_dir)
set(GTEST_INCLUDE_DIR ${source_dir}/googletest/include)

ExternalProject_Get_Property(googletest binary_dir)
set(GTEST_LIBS_DIR ${binary_dir}/lib/)
