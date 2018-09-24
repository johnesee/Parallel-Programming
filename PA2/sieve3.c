#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"

int main(int argc, char **argv) {

	long N  = 100;
	long B = 10;
	long size, rootSize;
	char *mark;
	int *primes;
   
   
   long   curr, k, a;
   long   i, j, n;
   long   count;
   long LOW, HI, value, square, start;

	long blockStart, blockSize, blockEnd;
	long numPrimes;

   /* Time */

   double time;

	if ( argc > 2 ){
		N  = atoi(argv[1]);
		B = atoi(argv[2]);
	} 
   
	long maxIndex = (N-3)/2;
	printf("maxIndex %ld\n", maxIndex);
	long rootN = (long) sqrt(N);
	printf("rootN %ld\n", rootN);
	long maxRootIndex = (rootN-3)/2;
	printf("maxRootIndex %ld\n", maxRootIndex);
	
	blockSize = B/2;

   /* Start Timer */

	initialize_timer ();
	start_timer();

	size = (maxIndex+1)*sizeof(char);
	mark = (char *)malloc(size);
	rootSize = (maxRootIndex+1)*sizeof(int);
	primes = (int *)malloc(rootSize);
	
	for (i=0; i<=maxIndex; i++){
		mark[i]=0;
	}
	for (i=0; i<=maxRootIndex; i++){
		primes[i]=-1;
	}
	curr = 0;
    //Starting prime
	k = a = 3;
	
	//Mark primes less than sqrt(N)
	while (k*k<=rootN) {
		for (i=curr+k; i<=maxRootIndex; i+=k) {
			mark[i]=1;
		}
		while (mark[++curr]);
		k = a + 2 * curr;

   }
    long temp = 0;
	//Create witness array
	numPrimes = -1;

	for ( i=0 ; i <= maxRootIndex; ++i) {
		if (mark[i]==0){
			++numPrimes;
			temp = a + 2 * i;
			primes[numPrimes] = temp;
		}
   }
	value = 0;
	blockStart = maxRootIndex +1;

	//Loop through blocks
	for (i = blockStart; i <= maxIndex; i += blockSize){
		printf("I: start:%ld end:%ld incr:%ld\n", i, maxIndex, blockSize);
		//Loop through witnesses
		for (j=0; j<=numPrimes; ++j){
			//printf("	J: start:%ld end:%ld incr:%ld\n", j, numPrimes, 1);
			value = primes[j];
			square = value*value;
			HI = a + 2 * (i + blockSize);
			LOW = a + 2 * i;
			//HI < Square
			if(square >= HI){
				break;
			}
			//LOW =< Square < HIGH
			else if (square >= LOW && square < HI){
				start = square;
			}
			//Square < LOW
			else {
				start = LOW - (LOW % value);
				//Start is odd
				if (start % 2){
					start += 2*value;
				} //Start even
				else {
					start += value;
				}
			}	
			start = (start - a)/2;
			blockEnd = ((start + blockSize) < maxIndex) ? (start + blockSize) : maxIndex;
			//printf("K: start:%ld end:%ld incr:%ld\n", k, blockEnd, value);
			
			for (k=start; k<=blockEnd; k+=value){
				//printf("		K: start:%ld end:%ld incr:%ld\n", k, blockEnd, value);
				mark[k]=1;		
			}
			
		}
	}
	
   /* stop timer */
   stop_timer();
   time=elapsed_time ();

   /*number of primes*/
   count = 1;
   for(i = 0; i <= maxIndex; i++){
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
   for ( i=0 ; i <= maxIndex && j < 3; ++i) {
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
   free(primes);
   
   return 0;
}


