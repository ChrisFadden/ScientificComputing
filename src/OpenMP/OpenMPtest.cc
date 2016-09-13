#include "Constants.h"
#include "OpenMP.h"
#include <stdio.h>

void reduction() {
  vec a(100);
  vec b(100);
  real sum;

  /* Some initializations */
  loop n = 100;
  for (loop i = 0; i < n; ++i)
    a[i] = b[i] = i * 1.0;
  sum = 0.0;

#pragma omp parallel for reduction(+ : sum)
  for (loop i = 0; i < n; ++i)
    sum = sum + (a[i] * b[i]);

  printf("Sum = %f\n", sum);
}

void testWorking() {
#pragma omp parallel
  printf("Hello from thread %d, nthreads %d\n", omp_get_thread_num(),
         omp_get_num_threads());
}

void testOpenMP() {
  testWorking();
  reduction();

  return;
}
