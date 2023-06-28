#!/bin/sh

set -xe

mkdir -p debug
cc -Wall -Werror -std=c11 -pedantic -ggdb -o ./debug/trie trie.c
./debug/trie dot > ./debug/trie.dot
dot -Tsvg ./debug/trie.dot > ./debug/trie.svg
