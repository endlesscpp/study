#detect memory leak
#S1: use valgrind
valgrind --leak-check=full ./main
