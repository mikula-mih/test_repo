#!/bin/sh

set -xe

cc -Wall -Wextra -o voronoi_ppm voronoi_ppm.c
cc -Wall -Wextra -o example example.c
