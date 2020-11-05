#CFLAGS = -Wall -dynamiclib
CFLAGS = -g -Wall -fPIC
# let the program find library under the same folder
LDFLAGS=-Wl,-rpath='$$ORIGIN' -L.

libdemo.so: mod1.o mod2.o mod3.o
	gcc -shared -o $@ $^ -ldl
%.o: %.c
	gcc -o $@ -c $(CFLAGS) $^

prog: prog.o
	gcc $(LDFLAGS) -o $@ $^ -l demo


.PHONY: clean
clean:
	$(RM) *.o prog *.so

# all .o depends on the .c with same name
# %.o: %.c
# .c.o:
# gcc -c $<

