cmake_minimum_required(VERSION 3.5)
project(BOOTCAMP C CXX)
enable_testing()

#set(CMAKE_C_STANDARD 99)

INCLUDE_DIRECTORIES(src)
INCLUDE_DIRECTORIES(3rd)

set(SRC_LIST src/main.c
    src/add.c)

#message(STATUS "This is BINARY dir " ${BOOTCAMP_BINARY_DIR})
#message(STATUS "This is SOURCE dir " ${BOOTCAMP_SOURCE_DIR})

add_executable(bootcamp ${SRC_LIST})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#add_subdirectory(test)
add_subdirectory(catch_test)

# if DESTINATION path start with '/', it absolute path; else its relative path
# to ${CMAKE_INSTALL_PREFIX}
# RUNTIME / ARCHIVE / LIBRARY
INSTALL(TARGETS bootcamp
    RUNTIME DESTINATION bin
    )

INSTALL(FILES ./README.md 
    DESTINATION doc
    )

# pay attention to the 'EXCLUDE' pattern
INSTALL(DIRECTORY include/
    DESTINATION include
    PATTERN "*.toexclude" EXCLUDE
    )

# install the script
INSTALL(PROGRAMS run_bootcamp.sh
    DESTINATION bin
    )
