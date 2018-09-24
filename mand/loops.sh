#!/bin/bash
export OMP_NUM_THREADS=$t
for t in {1..8}
	do
		export OMP_NUM_THREADS=$t
		echo "Threads: $t"
		for i in {1..2}
		do
			echo "Test $i"
			./mandSEQ 1000
			./mandOMP 1000
		done
done
exit 0