#!/bin/sh

set -xe

CC=clang
CFLAG="-Wall -Wextra"

$CC $CFALGS -o png main.c
