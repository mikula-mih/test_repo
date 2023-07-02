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

float dcost(float w) // using derivatives
{
  float result = 0.0f;
  size_t n = train_count;
  for (size_t i = 0; i < n; ++i) {
    float x = train[i][0];
    float y = train[i][1];
    result += 2*(x*w - y)*x;
  }
  result /= n;
  return result;
}

int main()
{
  srand(time(0));
  float w = rand_float()*10.0f;

  float rate = 1e-3;

  printf("err: %f\n", dcost(w));
  for (size_t i = 0; i < 5000; i++) {
    float dw = dcost(w); 
    w -= rate*dw;
    printf("cost: %f, w = %f\n", dcost(w), w);
  }

  printf("-------------------------------------------\n");
  printf("w = %f\n", w);

  return 0;
}
