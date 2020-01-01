CC=g++
CFLAGS = -g -O0 -fPIC
LDFLAGS=-Wl,-rpath='$$ORIGIN'

export LD_LIBRARY_PATH=.

run: main
	./$^

main: main.o libhello.so
	$(CC) $(LDFLAGS) -o $@ main.o -L. -lhello

main.o: main.cpp
	$(CC) -c $(CFLAGS) -o $@ $^

libhello.so: hello.o
	$(CC) -shared -fPIC -o $@ hello.o

hello.o: hello.c
	$(CC) -c $(CFLAGS) -o $@ $^

clean:
	$(RM) libhello.so *.o main

