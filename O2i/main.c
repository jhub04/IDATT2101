#include <math.h>
#include <stdio.h>
#include <time.h>

typedef double (*func_ptr)(double, int);

double recOne(double x, int n);
double recTwo(double x, int n);
double execTiming(func_ptr f, double x, int n);

int main(void) {
  double x = 5.0;
  int n_values[] = {100, 1000, 10000, 50000, 100000};
  int num_tests = sizeof(n_values) / sizeof(n_values[0]);

  double result_recOne = recOne(5.0, 11);
  printf("Method 1: 5^11 = %f\n", result_recOne);

  double result_recTwo = recTwo(5.0, 11);
  printf("Method 2: 5^11 = %f\n", result_recTwo);

  printf("\n");

  for (int i = 0; i<num_tests; i++) {
    int n = n_values[i];
    printf("-----n = %d-----\n", n);

    // Time information for recOne
    double time_recOne = execTiming(recOne, x, n);
    printf("Method 1: %f ms\n", time_recOne);

    // Time information for recTwo
    double time_recTwo = execTiming(recTwo, x, n);
    printf("Method 2: %f ms\n", time_recTwo);

    // Time information for pow method
    double time_pow = execTiming(pow, x, n);
    printf("pow-method: %f ms\n", time_pow);

    printf("\n");
  }

  return 0;
}

// Recursion method 1
double recOne(double x, int n) {
  if (n==1) {
    return x;
  }
  return (x * recOne(x, n-1));
}

// Recursion method 2
double recTwo(double x, int n) {
  if (n==1) {
    return x;
  }
  if (n%2==0) {
    return recTwo(x*x, n/2);
  }

  return x * recTwo(x*x, (n-1)/2);
}

// Method to execute the timing of a method
double execTiming(func_ptr f, double x, int n) {
  int repetitions = 10000;

  clock_t t0 = clock();
  // To estimate the average exec time better
  for (int i = 0; i<repetitions; i++) {
    f(x, n);
  }
  clock_t t1 = clock();
  return ((double) (t1-t0) * 1000) / CLOCKS_PER_SEC / repetitions;
}

