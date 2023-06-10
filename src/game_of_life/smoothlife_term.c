#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* ==================
 * Symbolic Constants
 * ================== */

#define WIDTH 100
#define HEIGHT 100

const char level[] = " ._=coaA@#";
#define level_count (sizeof(level)/sizeof(level[0]) - 1)

float grid[HEIGHT][WIDTH] = { {.0f} };
float grid_diff[HEIGHT][WIDTH] = { {.0f} };
const float ra = 9.0f; // ring outer
const float ri = ra/3; // ring inner
const float alpha = 0.028f; // alpha_n
// const float alpha_m = 0.147f;
const float b1 = 0.278f;
const float b2 = 0.368f;
const float d1 = 0.267f;
const float d2 = 0.445f;
const float dt = 0.05f;

/* ===================
 * Function Prototypes
 * =================== */

// grid setup
float rand_float(void);
void set_grid_rand(void);
void display_grid(void);
void display_grid_diff(float grid[HEIGHT][WIDTH]);
// computation functions
int emod(int, int);
float sigma_1(float, float);
float sigma_2(float, float, float);
float sigma_m(float, float, float);
float s(float, float);
void clamp(float *, float, float);
// simulation functions
void compute_grid_diff(void);

/* =============
 * Main Function
 * ============= */

int main(void)
{
  srand(time(0));
  
  set_grid_rand();
  
  display_grid();
  // Simulation Loop
  for (;;) {
    compute_grid_diff();
    for (size_t y = 0; y < HEIGHT; ++y) {
      for (size_t x = 0; x < WIDTH; ++x) {
        grid[y][x] += dt * grid_diff[y][x];
        clamp(&grid[y][x], 0, 1);
      }
    }
    display_grid();
  }

  return EXIT_SUCCESS;
}

/* ====================
 * Function Definitions
 * ==================== */

float rand_float(void)
{
  return (float) rand() / (float) RAND_MAX;
}

void set_grid_rand(void)
{
  size_t h = HEIGHT/3;
  size_t w = WIDTH/3;
  for (size_t dy = 0; dy < h; ++dy) {
    for (size_t dx = 0; dx < w; ++dx) {
      size_t x = dx + WIDTH/2 - w/2;
      size_t y = dy + HEIGHT/2 - h/2;
      grid[y][x] = rand_float();
    }
  }
}

void display_grid(void)
{
  for (size_t i = 0; i < HEIGHT; ++i) {
    for (size_t j = 0; j < WIDTH; ++j) {
      char c = level[ (int) (grid[i][j] * (level_count - 1)) ];
      fputc(c, stdout);
    }
    fputc('\n', stdout);
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

void display_grid_diff(float grid[HEIGHT][WIDTH])
{
  for (size_t i = 0; i < HEIGHT; ++i) {
    for (size_t j = 0; j < WIDTH; ++j) {
      printf("%e ", grid[i][j]);
    }
    puts("");
  }
}

void clamp(float *x, float lower, float higher)
{
  if (*x < lower) *x = lower; 
  if (*x > higher) *x = higher; 
}

