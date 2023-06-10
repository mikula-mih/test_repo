
# Simulating Actual Life in C

__References:__

- `Generalization of Conway's "Game of Life" to a continuous domain - SmoothLife` paper
- `Lenia - Biology of Artificial Life` paper
- [SmoothLife implementation][https://sourceforge.net/projects/smoothlife/]

# RayLib

- [https://www.raylib.com/index.html]

## Compiling RayLib

> compile with RayLib installed via pacman
```bash
cc main.c -lraylib
```
> comile with specific flags for RayLib
```bash
clang -O3 -Wall -Wextra `pkg-config --cflags raylib` main.c -o $BUILD/smoothlife_gpu -lm `pkg-config --libs raylib`
```
> compile with extra libs

* -ldl
* -lglfw
* -lpthread




