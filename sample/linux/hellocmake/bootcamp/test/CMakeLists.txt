include(gtest.cmake)
set(PROJECT_TEST_NAME test_${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 11)


INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/test)

set(SRC_LIST ${PROJECT_SOURCE_DIR}/src/add.c test_add.cpp)
#set(LIBS_LIST ${PROJECT_SOURCE_DIR}/3rd/gtest/lib/libgtest.a)

LINK_DIRECTORIES(${GTEST_LIBS_DIR})


add_executable(${PROJECT_TEST_NAME} ${SRC_LIST})
add_dependencies(${PROJECT_TEST_NAME} googletest)
TARGET_LINK_LIBRARIES(${PROJECT_TEST_NAME} libgtest.a pthread)

add_test(NAME example_test COMMAND ${PROJECT_TEST_NAME})

