#!/bin/sh

set -xe

BUILD="debug"

if [ ! -d $BUILD ]; then 
  mkdir $BUILD
fi

clang -O3 -Wall -Wextra smoothlife_term.c -o $BUILD/smoothlife_term -lm
clang -O3 -Wall -Wextra `pkg-config --cflags raylib` main.c -o $BUILD/smoothlife_gpu -lm `pkg-config --libs raylib`

set +x
echo "\n================================="
echo   "=== Running SmoothLife_GPU... ==="
echo   "=================================\n"
./$BUILD/smoothlife_gpu
set -x

if [ -d $BUILD ]; then
  rm -r $BUILD
fi
