/*
* jacobi.c
* WimBo
*/

#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include <mpi.h>

int main(int argc, char **argv) {

  int size, rank;
  int iter = 2000;
  int array_size, buffer_size, block_size, temp_array_size;
  double *prev, *curr, *temp;
  double *local_prev, *local_curr;
  double *local_big_prev, *local_big_curr;
  // Tiiterer
  double time;

  // temporary variables
  int i, j, r, t;
  int v = 0; //verbose
  int vp = 0;

  // Check commandline args.
  if ( argc > 1 ) {
    //problem (array) size n
   arraySize = atoi(argv[1]);
  } else {
    printf("Usage : %s [N]\n", argv[0]);
    exit(1);
  }
  if ( argc > 2 ) {
    //number of iterations m
   iter = atoi(argv[2]);
  }
  if ( argc > 3 ) {
    //buffer size k
    buffer_size = atoi(argv[3]);
  } else {
    buffer_size = 1;
  }
  if ( argc > 4 ) {
    v = 1;
    vp = atoi(argv[4]);
  }
  curr[0] = 0;
  curr[array_size-1] = array_size-1;

  MPI_Init( &argc &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank )
  MPI_Comm_size( MPI_COMM_WORLD, &size )
  block_size = array_size / size;

  if (rank == 0) {
    // Memory allocation for data array.
    prev  = (double *) malloc( sizeof(double) * array_size);
    curr  = (double *) malloc( sizeof(double) * array_size);

    if ( prev == NULL || cur == NULL ) {
      printf("[ERROR] : Fail to allocate memory.\n");
      exit(1);
    }
    // Initialization
    for ( i = 0 ; i < array_size ; i++ ) {
      prev[i] = i;
    }

    curr[0] = 0;
    curr[array_size - 1] = array_size - 1;
  }

  local_prev = (double *) malloc( sizeof(double) * block_size);
  local_curr = (double *) malloc( sizeof(double) * block_size);

  if(rank == 0 || rank == size-1){
    temp_array_size = block_size + buffer_size;
  } else {
    temp_array_size = block_size + (buffer_size * 2);
  }

  local_big_prev = (double *) malloc( sizeof(double) * (temp_array_size);
  local_big_curr = (double *) malloc( sizeof(double) * (temp_array_size);

  initialize_timer();
  start_timer();

  r = 0;
  while (r < iter/buffer_size){
    MPI_Scatter(prev, block_size, MPI_DOUBLE, local_prev, block_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
      //Rank 0
    if(rank == 0){
      //send
      MPI_Send(&local_prev[block_size-buffer_size], buffer_size, MPI_DOUBLE, rank+1, MPI_ANY_TAG, MPI_COMM_WORLD);
      //receive
      tail_prev = (double *) malloc( sizeof(double) * buffer_size);
      MPI_Recv(&tail_prev, buffer_size, MPI_DOUBLE, rank+1, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      MPI_Barrier(MPI_COMM_WORLD);

      //calculate
      memcpy(local_big_prev, local_prev, block_size*sizeof(double));
      memcpy(local_big_prev + block_size, tail_prev, buffer_size*sizeof(double));

      t=1;
      while (t <= bufferSize){
        for ( i = 1 ; i < temp_array_size - t; i++ ) {
          local_big_curr[i] = (local_big_prev[i-1]+local_big_prev[i]+local_big_prev[i+1])/3;
        }
        temp = local_big_prev;
        local_big_prev = local_big_curr;
        local_big_curr  = temp;
        t++;
      }
      MPI_Barrier(MPI_COMM_WORLD);
      memcpy(local_curr, local_big_prev, block_size*sizeof(double));
      //Rank Size-1
    } else if (rank == (size-1)){
      //receive
      head_prev = (double *) malloc( sizeof(double) * buffer_size);
      MPI_Recv(&head_prev, buffer_size, MPI_DOUBLE, rank-1, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      //send
      MPI_Send(&local_prev[0], buffer_size, MPI_DOUBLE, rank-1, MPI_ANY_TAG, MPI_COMM_WORLD);
      MPI_Barrier(MPI_COMM_WORLD);

      //calculate
      memcpy(local_big_prev, head_prev, buffer_size*sizeof(double));
      memcpy(local_big_prev + buffer_size, local_prev, block_size*sizeof(double));

      t=1;
      while (t <= bufferSize){
        for ( i = t ; i < temp_array_size - 1; i++ ) {
          local_big_curr[i] = (local_big_prev[i-1]+local_big_prev[i]+local_big_prev[i+1])/3;
        }
        temp = local_big_prev;
        local_big_prev = local_big_curr;
        local_big_curr  = temp;
        t++;
      }
      memcpy(local_curr, local_big_prev + buffer_size, block_size*sizeof(double));
      MPI_Barrier(MPI_COMM_WORLD);
      //All other Ranks
    } else {
      //receive previous
      head_prev = (double *) malloc( sizeof(double) * buffer_size);
      MPI_Recv(&head_prev, buffer_size, MPI_DOUBLE, rank-1, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      //send
      MPI_Send(&local_prev[0], buffer_size, MPI_DOUBLE, rank-1, MPI_ANY_TAG, MPI_COMM_WORLD);
      //send
      MPI_Send(&local_prev[block_size-buffer_size], buffer_size, MPI_DOUBLE, rank+1, MPI_ANY_TAG, MPI_COMM_WORLD);
      //receive
      tail_prev = (double *) malloc( sizeof(double) * buffer_size);
      MPI_Recv(&tail_prev, buffer_size, MPI_DOUBLE, rank+1, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      MPI_Barrier(MPI_COMM_WORLD);

      //calculate
      memcpy(local_big_prev, head_prev, buffer_size*sizeof(double));
      memcpy(local_big_prev + buffer_size, local_prev, block_size*sizeof(double));
      memcpy(local_big_prev + buffer_size + block_size , tail_prev, buffer_size*sizeof(double));

      t=1;
      while (t =< bufferSize){
        for ( i = t ; i < temp_array_size - t; i++ ) {
          local_big_curr[i] = (local_big_prev[i-1]+local_big_prev[i]+local_big_prev[i+1])/3;
        }
        temp = local_big_prev;
        local_big_prev = local_big_curr;
        local_big_curr  = temp;
        t++;
      }
      memcpy(local_curr, local_big_prev + buffer_size, block_size*sizeof(double));
      MPI_Barrier(MPI_COMM_WORLD);
    }
    MPI_Gather(local_curr, block_size, MPI_DOUBLE, curr, block_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    r++;
  }

  MPI_Finalize();
  stop_timer();
  time = elapsed_time();

  if(v){
    for(i=0;i<array_size;i++) printf("%f ",prev[i]);
    printf("\n");
  } else {
    printf("first, mid, last: %f %f %f\n",prev[0], prev[n/2-1], prev[n-1]);
  }
  printf("Data size : %d  , #iterations : %d , time : %lf sec\n", array_size, iter, time);

  free(prev);
  free(curr);
  free(local_prev);
  free(local_curr);
  free(local_big_prev);
  free(local_big_curr);

}
