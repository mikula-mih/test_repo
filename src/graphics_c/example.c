#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include "olive.c"

#define WIDTH 800
#define HEIGHT 600

#define COLS 8
#define ROWS 6
#define CELL_WIDTH  (WIDTH/COLS)
#define CELL_HEIGHT (HEIGHT/ROWS)

#define BACKGROUND_COLOR 0xFF202020

static uint32_t pixels[HEIGHT*WIDTH];
 
int main()
{
  printf("Howdy, neighbor!\n");

  olivec_fill(pixels, WIDTH, HEIGHT, BACKGROUND_COLOR);

  for (int y = 0; y < ROWS; ++y) {
    for (int x = 0; x < COLS; ++x) {
      uint32_t color = BACKGROUND_COLOR;
      if ((x + y)%2 == 0) {
        color = 0xFF2020FF;
      }
      olivec_fill_rect(pixels, WIDTH, HEIGHT, 
                        x*CELL_WIDTH, y*CELL_HEIGHT,
                        CELL_WIDTH, CELL_HEIGHT,
                        color);
    }
  }

  const char *file_path = "checker_example.ppm";
  Errno err = olivec_save_to_ppm_file(pixels, WIDTH, HEIGHT, file_path);
  if (err) {
    fprintf(stderr, "ERROR: could not save file %s: %s\n", file_path, strerror(errno));
    return 1;
  }

  return 0;
}
