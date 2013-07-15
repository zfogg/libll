#!/bin/make


GCC=gcc -Wall -Werror -O2


all: bin/libll.so

clean:
	rm bin/libll.so
	rm bin/tests

test: bin/tests
	export LD_LIBRARY_PATH=${PWD}/bin; \
	bin/tests


bin/:
	if [ ! -d ./bin ]; then \
		mkdir bin; \
	fi

ll.o:
	$(GCC) -c -fpic lib/ll.c

bin/libll.so: bin/ ll.o
	$(GCC) -shared -o bin/libll.so ll.o
	rm ll.o

bin/tests: bin/libll.so
	$(GCC) test/ll_tests.c -o bin/tests -L./bin -lll

