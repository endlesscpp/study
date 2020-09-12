set(PROJECT_TEST_NAME test_${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 11)



include_directories(${PROJECT_SOURCE_DIR}/3rd/catch2)

add_library(test_base OBJECT test_base.cpp)
#target_include_directories(test_base PRIVATE ${PROJECT_SOURCE_DIR}/3rd/catch2)



set(SRC_LIST ${PROJECT_SOURCE_DIR}/src/add.c test_add.cpp)
add_executable(${PROJECT_TEST_NAME} ${SRC_LIST})
add_dependencies(${PROJECT_TEST_NAME} test_base)
#TARGET_INCLUDE_DIRECTORIES(${PROJECT_TEST_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/3rd/catch2)
TARGET_LINK_LIBRARIES(${PROJECT_TEST_NAME} $<TARGET_OBJECTS:test_base> pthread)


set(SRC_LIST ${PROJECT_SOURCE_DIR}/src/add.c test_add2.cpp)
add_executable(test2 ${SRC_LIST})
add_dependencies(test2 test_base)
TARGET_LINK_LIBRARIES(test2 $<TARGET_OBJECTS:test_base> pthread)

add_test(NAME example1_test COMMAND ${PROJECT_TEST_NAME} --use-colour yes)
add_test(NAME example2_test COMMAND test2 --use-colour yes)
#add_test(NAME example_test COMMAND ${PROJECT_TEST_NAME})

