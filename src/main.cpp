#include "MPItest.h"
#include "OpenMP.h"
#include <iostream>
int main(int argc, char **argv) {

  testOpenMP();
  testMPI(argc, argv);
  std::cout << "Hello World" << std::endl;

  return 0;
}
