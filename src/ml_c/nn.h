#ifndef NN_H_
#define NN_H_

#include <stddef.h>
#include <stdio.h>

#ifndef NN_MALLOC
#include <stdlib.h>
#define NN_MALLOC malloc
#endif  // NN_MALLOC

#ifndef NN_ASSERT
#include <assert.h>
#define NN_ASSERT assert 
#endif  // NN_ASSERT

// float d[] = {0, 1, 0, 1};
// Mat m = { .rows = 2, .cols = 2, .es = d };

typedef struct {
  size_t rows;
  size_t cols;
  float *es;
} Mat;

#define MAT_AT(m, i, j) (m).es[(i)*(m).cols + (j)]

float rand_float(void);

Mat mat_alloc(const size_t rows, const size_t cols);
void mat_rand(const Mat, const float low, const float high);
Mat mat_dot(const Mat, const Mat);
Mat mat_sum(Mat, const Mat);
void mat_print(const Mat, const char*);

#endif // NN_H_

#ifdef NN_IMPLEMENTATION

float rand_float(void)
{
  return (float) rand() / (float) RAND_MAX;
}

Mat mat_alloc(const size_t rows, const size_t cols)
{
  Mat m = {
    .rows = rows,
    .cols = cols,
    .es = NN_MALLOC(sizeof(*m.es)*rows*cols)
  };

  NN_ASSERT(m.es != NULL);

  return m;
}

Mat mat_dot(const Mat a, const Mat b)
{
  NN_ASSERT(a.cols == b.rows);
  size_t n = a.cols;

  Mat dst = mat_alloc(a.rows, b.cols);

  for (size_t i = 0; i < dst.rows; ++i) {
    for (size_t j = 0; j < dst.cols; ++j) {
      MAT_AT(dst, i, j) = 0;
      for (size_t k = 0; k < n; ++k) {
        MAT_AT(dst, i, j) += MAT_AT(a, i, k) * MAT_AT(b, k, j);
      }
    }
  }
  return dst;
}

Mat mat_sum(Mat dst, const Mat a)
{
  NN_ASSERT(dst.rows == a.rows && dst.cols == a.cols); 

  size_t all_matrix_cells = dst.rows*dst.cols;
  float* dst_ptr = dst.es;
  float* sum_ptr = a.es;

  while (all_matrix_cells--)
    *dst_ptr++ += *sum_ptr++; 

  return dst;
}

void mat_print(const Mat m, const char* tag_name)
{
  printf("%s = [\n", tag_name);
  for (size_t i = 0; i < m.rows; ++i) {
    for (size_t j = 0; j < m.cols; ++j) {
      printf("    %f ", MAT_AT(m, i, j));
    }
    puts("");
  }
  puts("]");
}

void mat_rand(const Mat m, const float low, const float high)
{
  /*
   * insted of creating `mat_fill` function
   * set float low and float high to a same value
   */
  size_t all_matrix_cells = m.rows*m.cols;
  float* matrix_cell_ptr = m.es;

  while (all_matrix_cells--)
    *matrix_cell_ptr++ = rand_float()*(high - low) + low;
}

#endif // NN_IMPLEMENTATION
