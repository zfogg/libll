#!/bin/bash


TESTS=linkedLists_tests

if [ ! -d ./bin ]; then
  mkdir ./bin
fi

if [ -f ./bin/$TESTS ]; then
  rm ./bin/$TESTS
fi

gcc -Wall -O2 "$TESTS.c" -o ./bin/$TESTS

./bin/$TESTS

