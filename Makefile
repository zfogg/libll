#!/usr/bin/make -f


SRC_DIR = lib

OUT_DIR = build

BIN_DIR = bin


CLANG = clang -std=c99 -Wextra -O2

TESTS = $(BIN_DIR)/ll_tests


export LD_LIBRARY_PATH=$(OUT_DIR)


all: directories $(OUT_DIR)/libll.so

clean:
	rm -rf $(OUT_DIR) $(BIN_DIR)

test: $(TESTS)
	$(TESTS)


directories: $(OUT_DIR)/ $(BIN_DIR)/


$(OUT_DIR)/%.o:
	$(CLANG) -c -fpic $(SRC_DIR)/$(*F).c -o $(OUT_DIR)/$(*F).o

$(OUT_DIR)/%.so: $(OUT_DIR)/ll.o
	$(CLANG) -shared -o $(OUT_DIR)/$(*F).so $<

$(TESTS): all
	$(CLANG) ./test/ll_tests.c -o $(TESTS) -L$(OUT_DIR) -lll


%/:
	mkdir -p $@

