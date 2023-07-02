#!/bin/sh

set -xe

cc -Wall -Wextra -o voronoi_ppm src/voronoi_ppm.c
cc -Wall -Wextra -o voronoi_opengl src/voronoi_opengl.c -lglfw -lGL -lm
#./voronoi_opengl

