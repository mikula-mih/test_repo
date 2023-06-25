#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NN_IMPLEMENTATION
#include "nn.h"

int main(void)
{
  srand(time(0));

  Mat w1 = mat_alloc(2, 2);
  Mat b1 = mat_alloc(1, 2);
  Mat w2 = mat_alloc(2, 1);
  Mat b2 = mat_alloc(1, 1);

  mat_rand(w1, 0, 1);
  mat_rand(b1, 0, 1);
  mat_rand(w2, 0, 1);
  mat_rand(b2, 0, 1);

  mat_print(w1, "w1");
  mat_print(b1, "b1");
  mat_print(w2, "w2");
  mat_print(b2, "b2");

  return EXIT_SUCCESS;
}
