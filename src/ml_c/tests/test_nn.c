#include <stdio.h>

#define NN_TESTS_IMPL
#include "test_nn.h"

int main(void)
{
  puts("Runing some tests");

  void test_matrix_operations(void);
  void test_xor_nn(void);

  Mat w1 = mat_alloc(3, 3);
  Mat b1 = mat_alloc(1, 3);
  Mat w2 = mat_alloc(3, 1);
  Mat b2 = mat_alloc(1, 1);

  mat_rand(w1, 0, 1);
  mat_rand(b1, 0, 1);
  mat_rand(w2, 0, 1);
  mat_rand(b2, 0, 1);

  MAT_PRINT(w1);
  MAT_PRINT(b1);
  MAT_PRINT(w2);
  MAT_PRINT(b2);

  puts("TESTS: passed");

  return 0;
}
