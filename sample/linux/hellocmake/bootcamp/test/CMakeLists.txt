set(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rd/gtest/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/test)

set(SRC_LIST ${PROJECT_SOURCE_DIR}/src/add.c test_add.cpp)
set(LIBS_LIST ${PROJECT_SOURCE_DIR}/3rd/gtest/lib/libgtest.a)


add_executable(testbootcamp ${SRC_LIST})
TARGET_LINK_LIBRARIES(testbootcamp ${LIBS_LIST} pthread)
