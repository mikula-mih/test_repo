#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 10
#define HEIGHT 10

char level[] = " ._=coaA@#";
#define level_count (sizeof(level)/sizeof(level[0]) - 1)

float grid[HEIGHT][WIDTH] = { {.0f} };

float rand_float(void)
{
  return (float) rand() / (float) RAND_MAX;
}

int main(void)
{
  int now;
  srand(now = time(0));
  printf("Time now = %d\n", now);
  
  float *ptr_grid = &grid[0][0];

  for (size_t i = 0; i < HEIGHT*WIDTH; ++i) {
    *ptr_grid++ = rand_float();
  }

  for (size_t i = 0; i < HEIGHT; ++i) {
    for (size_t j = 0; j < WIDTH; ++j) {
      //printf("%5.3f ", grid[i][j] = rand_float());
      char c = level[ (int) (grid[i][j] * (level_count - 1)) ];
      printf("%c ", c);
    }
    puts("");
  }
  
  int now_f = time(0);
  printf("Time now = %d\nSpend = %d sec\n", now_f, now_f - now);
  puts("Howdy, neighbour!");

  return EXIT_SUCCESS;
}
  
