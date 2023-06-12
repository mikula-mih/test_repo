#ifndef NN_H_
#define NN_H_

// float d[] = {0, 1, 0, 1};
// Mat m = { .rows = 2, .cols = 2, .es = d };

typedef struct {
  size_t rows;
  size_t cols;
  float *es;
} Mat;

Mat mat_alloc(size_t rows, size_t cols);

#endif // NN_H_

#ifdef NN_IMPLEMENTATION


#endif // NN_IMPLEMENTATION
