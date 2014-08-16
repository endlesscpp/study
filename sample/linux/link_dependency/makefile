CFLAGS = -O2 -fPIC

export LD_LIBRARY_PATH=.

run: main
	./$^

main: main.o libhello.so
	$(CC) -o $@ main.o -L. -lhello

libhello.so: hello.o libworld.so
	$(CC) -shared -o $@ hello.o -L. -lworld

libworld.so: world.o
	$(CC) -shared -o $@ $^

clean:
	$(RM) libhello.so libworld.so *.o main

