#!/bin/make


GCC      =gcc -Wall -Werror -O2

LL_O     =build/ll.o

LIBLL_SO =build/libll.so

TESTS    =bin/tests


all: $(LIBLL_SO)

test: $(TESTS)
	export LD_LIBRARY_PATH=${PWD}/build; \
	$(TESTS)

clean:
	rm -r build bin


bin/:
	mkdir bin

build/:
	mkdir build

$(LL_O):
	$(GCC) -c -fpic lib/ll.c -o $(LL_O)

$(LIBLL_SO): build/ $(LL_O)
	$(GCC) -shared -o $(LIBLL_SO) $(LL_O)

$(TESTS): bin/ $(LIBLL_SO)
	$(GCC) test/ll_tests.c -o $(TESTS) -L./build -lll

