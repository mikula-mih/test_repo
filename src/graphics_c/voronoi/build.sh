#!/bin/sh

set -xe

cc -Wall -Wextra -o voronoi_ppm voronoi_ppm.c
cc -Wall -Wextra -o voronoi_opengl voronoi_opengl.c -lglfw
./voronoi_opengl

