# show how to debug stackoverflow
## we can see the ret_address after the ebp is overwrite after input a very long string.
## (gdb) x/20xg $rbp
## (gdb) x/20s $rbp
## The ebp of each frame are chained, the ret address is following it in output. (stack addr from high to low)


# AddressSanitizer
```shell
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer -g -O0")
#set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer -g -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fstack-protector-all -g -O0")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fstack-protector-all -g -O0")
set(CMAKE_SHARED_LINKER_FLAGS "-fsanitize=address")
# set(CMAKE_EXE_LINKER_FLAGS "-fsanitize=address")
# set(CMAKE_MODULE_LINKER_FLAGS "-fsanitize=address")
```shell

