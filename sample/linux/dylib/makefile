#CFLAGS = -Wall -dynamiclib
CFLAGS = -g -Wall -fPIC
# let the program find library under the same folder
LDFLAGS=-Wl,-rpath='$$ORIGIN' -L.

libdemo.so: mod1.o mod2.o mod3.o
	gcc -shared -o $@ $^ -ldl
mod1.o: mod1.c
	gcc -o $@ -c $(CFLAGS) $^
mod2.o: mod2.c
	gcc -o $@ -c $(CFLAGS) $^
mod3.o: mod3.c
	gcc -o $@ -c $(CFLAGS) $^

prog: prog.o
	gcc $(LDFLAGS) -o $@ $^ -l demo
prog.o: prog.c
	gcc -o $@ -c $(CFLAGS) $^


.PHONY: clean
clean:
	$(RM) *.o prog *.so

