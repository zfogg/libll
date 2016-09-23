#!/usr/bin/make -f


CC        := clang
CXX       := clang++
CFLAGS    := -std=c99 -Wextra -O2


SRC_D     := src
OUT_D     := build
BIN_D     := bin
TEST_D    := test


OBJECTS   := $(patsubst $(SRC_D)/%.c, $(OUT_D)/%.o, $(wildcard $(SRC_D)/*.c))
OBJECTS_T := $(patsubst $(TEST_D)/%.c, $(OUT_D)/%.o, $(wildcard $(TEST_D)/*.c))
HEADERS   := $(wildcard $(SRC_D)/*.h)
HEADERS_T := $(wildcard $(TEST_D)/*.h)


LIB       := ll
TARGET    := $(OUT_D)/lib$(LIB).so
TESTS     := $(BIN_D)/ll_tests

LIBFLAGS  := -L$(OUT_D) -l$(LIB)


export LD_LIBRARY_PATH=$(OUT_D)


.PHONY: all clean test


default: $(TARGET)

all: default

clean:
	@echo 'cleaning...'
	@find $(OUT_D) $(BIN_D) -mindepth 1 -not -iname '.gitignore' -delete -print
	@echo 'done!

tests: all $(TESTS)
test: tests
	./$(TESTS)


$(OBJECTS): $(OUT_D)/%.o: $(SRC_D)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ -c -fpic $<

$(OUT_D)/%.so: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ -shared $^

$(OBJECTS_T): $(OUT_D)/%.o: $(TEST_D)/%.c $(HEADERS_T)
	$(CC) $(CFLAGS) -o $@ -c -fpic $<

$(TESTS): $(OBJECTS_T)
	$(CC) $(CFLAGS) -o $@ $(LIBFLAGS) $^
