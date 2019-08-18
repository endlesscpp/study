use MALOC_CHECK_ to debug memory related problem

$ env MALLOC_CHECK=1 ./a.out

or
valgrind --tool=memcheck --leak-check=yes ./a.out

valgrind --leak-check=full ./a.out


# check memory usage
ps -aux | grep 'a.out'
top -p $PID
or
cat /proc/$PID/status
check the VMRss

# tools
smem
apt update
apt install smem
