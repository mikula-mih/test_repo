#ifndef NN_TESTS_
#define NN_TESTS_

#define NN_IMPLEMENTATION
#include "../nn.h"

// supplementary functions
void create_testing_data_struct(void);
// TEST funxtions 
void test_matrix_operations(void);
void test_xor_nn(void);

#endif // NN_TESTS_

#ifdef NN_TESTS_IMPL

void create_testing_data_struct(void)
{
  return (void) (0);
}

void test_matrix_operations(void)
{
  Mat w1 = mat_alloc(1, 2);
  mat_rand(w1, 0, 1);

  MAT_PRINT(w1);
  /*
  MAT_PRINT(w1);
  MAT_PRINT(b1);
  MAT_PRINT(w2);
  MAT_PRINT(b2);
  */
}

void test_xor_nn(void)
{
  return (void) (0);
}

#endif // NN_TESTS_IMPL
