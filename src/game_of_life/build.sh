#!/bin/sh

set -xe

BUILD="build"

if [ ! -d $BUILD ]; then 
  mkdir $BUILD
fi

clang -Wall -Wextra main.c -o build/main
./build/main

if [ -d $BUILD ]; then
  rm -r $BUILD
fi
