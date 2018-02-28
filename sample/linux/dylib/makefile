#CFLAGS = -Wall -dynamiclib
CFLAGS = -Wall -fPIC
# let the program find library under the same folder
LDFLAGS=-Wl,-rpath='$$ORIGIN'

prog: prog.o libdemo.so
	gcc $(LDFLAGS) -o $@ $^
libdemo.so: mod1.o mod2.o mod3.o
	gcc -shared -o $@ $^
prog.o: prog.c
	gcc -o $@ -c $(CFLAGS) $^
mod1.o: mod1.c
	gcc -o $@ -c $(CFLAGS) $^
mod2.o: mod2.c
	gcc -o $@ -c $(CFLAGS) $^
mod3.o: mod3.c
	gcc -o $@ -c $(CFLAGS) $^

.PHONY: clean
clean:
	$(RM) *.o prog *.so

