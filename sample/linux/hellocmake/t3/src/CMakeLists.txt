INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)

# 这个命令很少用，并且需要放在target之前
LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/lib)
ADD_EXECUTABLE(hellomain main.c)
# can use hello / hello.a / hello.so
TARGET_LINK_LIBRARIES(hellomain hello)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

#  下面是有静态库就优先使用静态库的方法
# FIND_LIBRARY(SLibrarys libhello.a)
# FIND_LIBRARY(DLibrarys libhello.so)
# IF(SLibrarys)
#     TARGET_LINK_LIBRARIES(main ${SLibrarys})
# ELSE(SLibrarys)
#     TARGET_LINK_LIBRARIES(main ${DLibrarys})
# ENDIF(SLibrarys)