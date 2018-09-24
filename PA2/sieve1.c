#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"

int main(int argc, char **argv) {

   long N  = 100;
   
   char *mark;

   long   size;
   long   curr, k, a;
   long   i, j, n;
   long   count;

   /* Time */

   double time;

   if ( argc > 1 ) N  = atoi(argv[1]);
   
   long maxIndex = (N-3)/2;

   /* Start Timer */

   initialize_timer ();
   start_timer();

   size = (maxIndex+1)*sizeof(char);
   mark = (char *)malloc(size);
//Parallelize
	#pragma omp parallel for
	for (i=0; i<=maxIndex; i++){
		mark[i]=0;
	}

	curr = 0;
       /*first prime*/
	k = a = 3;
	while (k*k<=N) {
//Parallelize 
		#pragma omp parallel for
		for (i=curr+k; i<=maxIndex; i+=k) {
			mark[i]=1;
		}
		while (mark[++curr]); /* do nothing */
   /* now index has the first unmarked number, so the next prime */
		k = a + 2 * curr;
   }

   /* stop timer */
   stop_timer();
   time=elapsed_time ();

   /*number of primes*/
   count = 1;
   for(i = 0; i <=maxIndex; i++){
        if((mark[i]==0)) {
        	++count;
        	printf("%ld,%ld,%ld\n", i, count, a + 2 * i);
        }
   }
   printf("There are %ld primes less than or equal to %ld\n", count, N);
   /* print results */
   printf("First three primes:");
   j = 1;
   printf("%d ", 2);
   for ( i=0 ; i <= maxIndex && j < 3; i+=1 ) {
      if (mark[i]==0){
            printf("%ld ", a + 2 * i);
            ++j;
      }
   }
   printf("\n");

   printf("Last three primes:");
   j = 0;
   n=(N%2?N:N-1);
   for (i = maxIndex; i > 0 && j < 3; i-=1){
     if (mark[i]==0){
		printf("%ld ", a + 2 * i);
		j++;
     }
   }
   printf("\n");


   printf("elapsed time = %lf (sec)\n", time);

   free(mark);
   return 0;
}


