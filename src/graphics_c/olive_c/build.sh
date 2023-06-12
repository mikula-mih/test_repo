#!/bin/sh

set -xe

mkdir -p ./bin/
mkdir -p ./imgs/
cc -Wall -Wextra -ggdb -o ./bin/example example.c
./bin/example
