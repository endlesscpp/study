# show how to debug stackoverflow
## we can see the ret_address after the ebp is overwrite after input a very long string.
## (gdb) x/20xg $rbp
## (gdb) x/20s $rbp
## The ebp of each frame are chained, the ret address is following it in output. (stack addr from high to low)

