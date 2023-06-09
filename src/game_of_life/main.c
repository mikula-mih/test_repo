#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* ==================
 * Symbolic Constants
 * ================== */

#define WIDTH 50
#define HEIGHT 50

const char level[] = " ._=coaA@#";
#define level_count (sizeof(level)/sizeof(level[0]) - 1)

/*
typedef struct {
  float value;
  float diff;
} Cell;

Cell diff_grid[HEIGHT][WIDTH] = { { (Cell) {.0f, .0f} } };
*/

float grid[HEIGHT][WIDTH] = { {.0f} };
float grid_diff[HEIGHT][WIDTH] = { {.0f} };
const float ra = 21.0f; // ring outer
const float ri = ra/3; // ring inner
const float alpha = 0.028f; // alpha_n
// const float alpha_m = 0.147f;
const float b1 = 0.278f;
const float b2 = 0.368f;
const float d1 = 0.267f;
const float d2 = 0.445f;
const float dt = .1f;

/* ===================
 * Function Prototypes
 * =================== */

// grid setup
float rand_float(void);
void set_grid_rand(float *);
void display_grid(void);
// computation functions
int emod(int, int);
float sigma_1(float, float);
float sigma_2(float, float, float);
float sigma_m(float, float, float);
float s(float, float);

/* =============
 * Main Function
 * ============= */

void compute_grid_diff(void)
{
  for (int cy = 0; cy < HEIGHT; ++cy) {
    for (int cx = 0; cx < WIDTH; ++cx) {
      float m = 0, M = 0; // uppercase normalization value
      float n = 0, N = 0; // == area of circle

      for (int dy = -(ra - 1); dy <= (ra - 1); ++dy) {
        for (int dx = -(ra - 1); dx <= (ra - 1); ++dx) {
          // making sure (x, y) within the boundaries
          int x = emod(cx + dx, WIDTH); // wraps if exceeds
          int y = emod(cy + dy, HEIGHT);
          if (dx*dx + dy*dy <= ri*ri) {
            m += grid[y][x];
            M++;
          } else if (dx*dx + dy*dy <= ra*ra) {
            n += grid[y][x];
            N++;
          }
        }
      }
      n /= N;
      m /= M;
      float q = s(n, m);
      grid_diff[cy][cx] = 2*q - 1;
    }
  }
}

void display_grid_diff_(float grid[HEIGHT][WIDTH])
{
  for (size_t i = 0; i < HEIGHT; ++i) {
    for (size_t j = 0; j < WIDTH; ++j) {
      printf("%5f ", grid[i][j]);
    }
    puts("");
  }
}

void display_grid_diff(void)
{
  for (size_t y = 0; y < HEIGHT; ++y) {
    for (size_t x = 0; x < WIDTH; ++x) {
      printf("%e ", grid_diff[y][x]);

      grid[x][y] += dt * grid_diff[y][x];
    }
    puts("");
  }
}

int main(void)
{
  int now;
  srand(now = time(0));
  printf("Time now = %d\n", now);
  
  // printf("%p\n", grid);
  set_grid_rand(&grid[0][0]);
  // printf("%p\n", grid);

  display_grid();
  display_grid_diff_(grid);
  // display_diff_grid(grid);
  compute_grid_diff();
  display_grid_diff();

  display_grid();
  display_grid_diff_(grid);

  // TEST CODE ====================

  int cx = 0;
  int cy = 0;
  float m = 0, M = 0; // uppercase normalization value
  float n = 0, N = 0; // == area of circle

  for (int dy = -(ra - 1); dy <= (ra - 1); ++dy) {
    for (int dx = -(ra - 1); dx <= (ra - 1); ++dx) {
      // making sure (x, y) within the boundaries
      int x = emod(cx + dx, WIDTH); // wraps if exceeds
      int y = emod(cy + dy, HEIGHT);
      if (dx*dx + dy*dy <= ri*ri) {
        m += grid[y][x];
        M++;
      } else if (dx*dx + dy*dy <= ra*ra) {
        n += grid[y][x];
        N++;
      }
    }
  }

  printf("m = %f, n = %f, M = %f, N = %f\n", m, n, M, N);
  printf("m/M = %f, n/N = %f\n", m/M, n/N);

  n /= N;
  m /= M;

  printf("s(n, m) = %e\n", s(n, m));

  // TEST END =====================

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

int emod(int a, int b)
{
  // mod wrapping both positive and negative numbers
  return (a%b + b)%b;
}

float sigma_1(float x, float a)
{
  return 1.0f/(1.0f + expf(-(x - a)*4/alpha));
}

float sigma_2(float x, float a, float b)
{
  return sigma_1(x, a)*(1 - sigma_1(x, b));
}

float sigma_m(float x, float y, float m)
{
  // return x*(1 - sigma_1(m, 0.5f)) + y*(sigma_1(m, 0.5f));
  return sigma_1(m, 0.5f)*(y - x) + x;
}

float s(float n, float m)
{
  // transition function
  // [b1, b2]; [d1, d2] -- birth and death intervals
  return sigma_2(n, sigma_m(b1, d1, m), sigma_m(b2, d2, m));
}

