#!/bin/sh

set -xe

BUILD="build"

if [ ! -d $BUILD ]; then 
  mkdir $BUILD
fi

clang -O3 -Wall -Wextra main.c -o build/main -lm
./build/main

if [ -d $BUILD ]; then
  rm -r $BUILD
fi
