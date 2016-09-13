#include "Constants.h"
#include "MPItest.h"
#include <stdio.h>

void reduction(int rank, int size) {
  // Setup variables
  loop arraySize = 400;
  int chunkSize = (arraySize / size);

  MPI_Status status;

  real sum, mysum;
  vec data(arraySize);

  int tag1 = 2;
  int tag2 = 1;
  int offset;
  // Master only
  if (rank == 0) {
    // Initialize the array
    sum = 0;
    for (loop i = 0; i != arraySize; ++i) {
      data[i] = i * 1.0;
      sum = sum + data[i];
    }

    // Send Data to workers
    offset = chunkSize;
    for (loop dest = 1; dest != size; ++dest) {
      MPI_Send(&offset, 1, MPI_INT, dest, tag1, MPI_COMM_WORLD);
      MPI_Send(&data[offset], chunkSize, MPI_FLOAT, dest, tag2, MPI_COMM_WORLD);
      offset += chunkSize;
    }

    offset = 0;
    // Do Work
    for (loop i = offset; i != offset + chunkSize; ++i) {
      data[i] = data[i] + i * 1.0;
      mysum = mysum + data[i];
    }

    // RECV Data from Workers
    for (loop i = 1; i != size; ++i) {
      MPI_Recv(&offset, 1, MPI_INT, i, tag1, MPI_COMM_WORLD, &status);
      MPI_Recv(&data[offset], chunkSize, MPI_FLOAT, i, tag2, MPI_COMM_WORLD,
               &status);
    }

    // Get final sum
    MPI_Reduce(&mysum, &sum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    printf("*** Final sum= %e ***\n", sum);
  } // end master

  if (rank != 0) {

    // RECV from Master
    MPI_Recv(&offset, 1, MPI_INT, 0, tag1, MPI_COMM_WORLD, &status);
    MPI_Recv(&data[offset], chunkSize, MPI_FLOAT, 0, tag2, MPI_COMM_WORLD,
             &status);

    // Do Work
    for (loop i = offset; i != offset + chunkSize; ++i) {
      data[i] = data[i] + i * 1.0;
      mysum = mysum + data[i];
    }

    // SEND to Master
    MPI_Send(&offset, 1, MPI_INT, 0, tag1, MPI_COMM_WORLD);
    MPI_Send(&data[offset], chunkSize, MPI_FLOAT, 0, tag2, MPI_COMM_WORLD);

    MPI_Reduce(&mysum, &sum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

  } // end workers
}

void testWorking(int argc, char **argv, int *rank, int *size) {
  MPI_Comm_rank(MPI_COMM_WORLD, rank);
  MPI_Comm_size(MPI_COMM_WORLD, size);
  printf("Hello world from process %d of %d\n", *rank, *size);
}

void testMPI(int argc, char **argv) {
  int rank, size;
  MPI_Init(&argc, &argv);

  testWorking(argc, argv, &rank, &size);
  reduction(rank, size);

  MPI_Finalize();

  return;
}
