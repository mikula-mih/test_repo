#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ==================
 * Symbolic Constants
 * ================== */

#define WIDTH 100
#define HEIGHT 100

char level[] = " ._=coaA@#";
#define level_count (sizeof(level)/sizeof(level[0]) - 1)

float grid[HEIGHT][WIDTH] = { {.0f} };
float ra = 21.0f;

/* ===================
 * Function Prototypes
 * =================== */

float rand_float(void);
void set_grid_rand(float *);
void display_grid(void);

/* =============
 * Main Function
 * ============= */

int main(void)
{
  int now;
  srand(now = time(0));
  printf("Time now = %d\n", now);
  
  printf("%p\n", grid);
  set_grid_rand(&grid[0][0]);
  printf("%p\n", grid);

  display_grid();

  int now_f = time(0);
  printf("Time now = %d\nSpend = %d sec\n", now_f, now_f - now);
  puts("Howdy, neighbour!");

  return EXIT_SUCCESS;
}

/* ====================
 * Function Definitions
 * ==================== */

float rand_float(void)
{
  return (float) rand() / (float) RAND_MAX;
}

void set_grid_rand(float *ptr_grid)
{
  for (size_t i = 0; i < HEIGHT*WIDTH; ++i)
    *ptr_grid++ = rand_float();
}

void display_grid(void)
{
  for (size_t i = 0; i < HEIGHT; ++i) {
    for (size_t j = 0; j < WIDTH; ++j) {
      //printf("%5.3f ", grid[i][j] = rand_float());
      char c = level[ (int) (grid[i][j] * (level_count - 1)) ];
      printf("%c", c);
    }
    puts("");
  }
}
