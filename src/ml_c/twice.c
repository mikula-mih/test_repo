#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float train[][2] = {
  {0, 0},
  {1, 2},
  {2, 4},
  {3, 6},
  {4, 8},
};

#define train_count (sizeof(train)/sizeof(train[0]))


float rand_float(void)
{
  // give us a random number from 0 to 1
  return (float) rand() / (float) RAND_MAX;
}

// improving cost function
float cost(float w, float b)
{
  float result = 0.0f;

  for (size_t i = 0; i < train_count; i++) {
    float x = train[i][0];
    float y = x*w + b;
    // printf("actual: %f, expected: %f\n", y, train[i][1]);
    float err = y - train[i][1];
    result += err*err;
  }

  result /= train_count;

  return result;
}

int main()
{
  // srand(time(0));
  srand(69);
  // y = x*w;
  float w = rand_float()*10.0f;
  float b = rand_float()*5.0f;

  printf("%f %f\n", w, b);
  printf("%zu\n", train_count);

  float eps = 1e-3;
  float rate = 1e-3;

  printf("err: %f\n", cost(w, b));
  for (size_t i = 0; i < 5000; i++) {
    float dcost = (cost(w + eps, b) - cost(w, b))/eps;
    float bcost = (cost(w, b + eps) - cost(w, b))/eps;
    w -= rate*dcost;
    b -= rate*bcost;
    printf("cost: %f, w = %f, b = %f\n", cost(w, b), w, b);
  }

  printf("-------------------------------------------\n");
  printf("w = %f, b = %f\n", w, b);

  return 0;
}
