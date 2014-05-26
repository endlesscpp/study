CFLAGS = -g -Wall
all: scan.o util.o main.o
	gcc -o tiny.exe main.o scan.o util.o
main.o: main.c
	gcc $(CFLAGS) -c $<
scan.o: scan.c scan.h
	gcc $(CFLAGS) -c $<
util.o: util.c util.h
	gcc $(CFLAGS) -c $<
clean:
	rm *.o *.exe

