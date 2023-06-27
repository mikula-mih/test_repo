#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NN_IMPLEMENTATION
#include "nn.h"

typedef struct {
  size_t count;
  Mat *ws;
  Mat *bs;
  Mat *as; // The amount of activations is count+1
} NN;

#define ARRAY_LEN(xs) sizeof((xs))/sizeof((xs)[0])

// size_t arch[] = {2, 2, 1};
// NN nn = nn_alloc(arch, ARRAY_LEN(arch));

NN nn_alloc(size_t *arch, size_t arch_count)
{
  NN_ASSERT(arch_count > 0);

  NN nn;
  nn.count = arch_count - 1;

  nn.ws = NN_MALLOC(sizeof(*nn.ws)*nn.count);
  NN_ASSERT(nn.ws != NULL);
  nn.bs = NN_MALLOC(sizeof(*nn.bs)*nn.count);
  NN_ASSERT(nn.bs != NULL);
  nn.as = NN_MALLOC(sizeof(*nn.as)*(nn.count + 1));
  NN_ASSERT(nn.as != NULL);

  nn.as[0] = mat_alloc(1, arch[0]);
  for (size_t i = 1; i < arch_count; ++i) {
    nn.ws[i-1] = mat_alloc(nn.as[i-1].cols, arch[i]);
    nn.bs[i-1] = mat_alloc(1, arch[i]);
    nn.as[i] = mat_alloc(1, arch[i]);
  }

  return m;
}

float cost(const Xor m, const Mat ti, const Mat to);
float forward_xor(Xor m);

float cost(const Xor m, const Mat ti, const Mat to)
{
  assert(ti.rows == to.rows);
  assert(to.cols == m.a2.cols);
  size_t n = ti.rows;

  float c = 0.0;
  for (size_t i = 0; i < n; ++i) {
    Mat x = mat_row(ti, i);
    Mat y = mat_row(to, i);
    
    mat_copy(m.x, x);
    (void) forward_xor(m);

    size_t q = to.cols;
    for (size_t j = 0; j < q; ++j) {
      float d = MAT_AT(m.a2, 0, j) - MAT_AT(y, 0, j);
      c += d*d;
    }
  }
  return c/n;
}

float forward_xor(Xor m)
{
  // sigmoidf(x*w1 + b1)
  m.a1 = mat_dot(m.x, m.w1);
  (void) mat_sum(m.a1, m.b1);
  mat_sig(m.a1);

  m.a1 = mat_dot(m.a1, m.w2);
  (void) mat_sum(m.a2, m.b2);
  mat_sig(m.a2);

  return *m.a2.es;
}

void finite_diff(Xor m, Xor g, float eps, Mat ti, Mat to)
{
  float saved;
  float c = cost(m, ti, to);

  for (size_t i = 0; i < m.w1.rows; ++i) {
    for (size_t j = 0; j < m.w1.cols; ++j) {
      saved = MAT_AT(m.w1, i, j);
      MAT_AT(m.w1, i, j) += eps;
      MAT_AT(g.w1, i, j) = (cost(m, ti, to) - c)/eps;
      MAT_AT(m.w1, i, j) = saved;
    }
  }
 
  for (size_t i = 0; i < m.b1.rows; ++i) {
    for (size_t j = 0; j < m.b1.cols; ++j) {
      saved = MAT_AT(m.b1, i, j);
      MAT_AT(m.b1, i, j) += eps;
      MAT_AT(g.b1, i, j) = (cost(m, ti, to) - c)/eps;
      MAT_AT(m.b1, i, j) = saved;
    }
  }
 
  for (size_t i = 0; i < m.w2.rows; ++i) {
    for (size_t j = 0; j < m.w2.cols; ++j) {
      saved = MAT_AT(m.w2, i, j);
      MAT_AT(m.w2, i, j) += eps;
      MAT_AT(g.w2, i, j) = (cost(m, ti, to) - c)/eps;
      MAT_AT(m.w2, i, j) = saved;
    }
  }
 
  for (size_t i = 0; i < m.b2.rows; ++i) {
    for (size_t j = 0; j < m.b2.cols; ++j) {
      saved = MAT_AT(m.b2, i, j);
      MAT_AT(m.b2, i, j) += eps;
      MAT_AT(g.b2, i, j) = (cost(m, ti, to) - c)/eps;
      MAT_AT(m.b2, i, j) = saved;
    }
  }

}

void xor_learn(Xor m, Xor g, float rate)
{

  for (size_t i = 0; i < m.w1.rows; ++i) {
    for (size_t j = 0; j < m.w1.cols; ++j) {
      MAT_AT(m.w1, i, j) -= rate*MAT_AT(g.w1, i, j);
    }
  }
 
  for (size_t i = 0; i < m.b1.rows; ++i) {
    for (size_t j = 0; j < m.b1.cols; ++j) {
      MAT_AT(m.b1, i, j) -= rate*MAT_AT(g.b1, i, j);
    }
  }
 
  for (size_t i = 0; i < m.w2.rows; ++i) {
    for (size_t j = 0; j < m.w2.cols; ++j) {
      MAT_AT(m.w2, i, j) -= rate*MAT_AT(g.w2, i, j);
    }
  }
 
  for (size_t i = 0; i < m.b2.rows; ++i) {
    for (size_t j = 0; j < m.b2.cols; ++j) {
      MAT_AT(m.b2, i, j) -= rate*MAT_AT(g.b2, i, j);
    }
  }

}

float td[] = {
  0, 0, 0,
  0, 1, 1,
  1, 0, 1,
  1, 1, 0,
};

int main(void)
{
  srand(time(0));

  size_t stride = 3;
  size_t n = sizeof(td)/sizeof(td[0])/stride;
  Mat ti = {
    .rows = n,
    .cols = 2,
    .stride = stride,
    .es = td,
  };

  Mat to = {
    .rows = n,
    .cols = 1,
    .stride = stride,
    .es = td + 2,
  };

  MAT_PRINT(ti);
  MAT_PRINT(to);

  Xor m = xor_alloc();
  Xor g = xor_alloc();

  mat_rand(m.w1, 0, 1);
  mat_rand(m.b1, 0, 1);
  mat_rand(m.w2, 0, 1);
  mat_rand(m.b2, 0, 1);

  float eps = 1e-1;
  float rate = 1e-1;

  printf("cost = %f\n", cost(m, ti, to));
  for (size_t i = 0; i < 1000; ++i) {
    finite_diff(m, g, eps, ti, to);
    xor_learn(m, g, rate);
    printf("%zu: cost = %f\n", i, cost(m, ti, to));
  }

  puts("-------------------------------------");
#if 1
  for (size_t i = 0; i < 2; ++i) {
    for (size_t j = 0; j < 2; ++j) {
      MAT_AT(m.x, 0, 0) = i;
      MAT_AT(m.x, 0, 1) = j;
      float y = forward_xor(m);

      printf("%zu ^ %zu = %f\n", i, j, y);
    }
  }
#endif

  return EXIT_SUCCESS;
}
