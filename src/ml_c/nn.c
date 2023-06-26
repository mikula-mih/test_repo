#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NN_IMPLEMENTATION
#include "nn.h"

typedef struct {
  Mat x;
  Mat w1, b1, a1;
  Mat w2, b2, a2;
} Xor;

float forward_xor(Xor m, const float x1, const float x2)
{
  MAT_AT(m.x, 0, 0) = x1;
  MAT_AT(m.x, 0, 1) = x2;

  // sigmoidf(x*w1 + b1)
  m.a1 = mat_dot(m.x, m.w1);
  (void) mat_sum(m.a1, m.b1);
  mat_sig(m.a1);

  m.a1 = mat_dot(m.a1, m.w2);
  (void) mat_sum(m.a2, m.b2);
  mat_sig(m.a2);

  return *m.a2.es;
}

int main(void)
{
  srand(time(0));

  Xor m;

  m.x = mat_alloc(1, 2);
  m.w1 = mat_alloc(2, 2);
  m.b1 = mat_alloc(1, 2);
  m.a1 = mat_alloc(1, 2);
  m.w2 = mat_alloc(2, 1);
  m.b2 = mat_alloc(1, 1);
  m.a2 = mat_alloc(1, 1);

  mat_rand(m.w1, 0, 1);
  mat_rand(m.b1, 0, 1);
  mat_rand(m.w2, 0, 1);
  mat_rand(m.b2, 0, 1);

  for (size_t i = 0; i < 2; ++i) {
    for (size_t j = 0; j < 2; ++j) {
      printf("%zu ^ %zu = %f\n", i, j, forward_xor(m, i, j));
    }
  }

  return EXIT_SUCCESS;
}
