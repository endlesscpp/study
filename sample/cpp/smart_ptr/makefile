CFLAGS = -g -Wall -O0 -std=c++11
# let the program find library under the same folder
#LDFLAGS=-Wl,-rpath='$$ORIGIN' -L.

a.out: test.o test_base.o
	g++ -o $@ $(CFLAGS) $^
test.o: test.cpp oak_memory.hpp oak_move.hpp
	g++ -o $@ -c $(CFLAGS) test.cpp
test_base.o: test_base.cpp
	g++ -o $@ -c $(CFLAGS) $^


.PHONY: clean
clean:
	$(RM) *.o a.out

