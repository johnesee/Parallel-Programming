#!/bin/bash
export OMP_NUM_THREADS=$t
for t in {1..6}
	do
		export OMP_NUM_THREADS=$t
		echo "Threads: $t"
		for i in {1..5}
		do
			echo "Test $i"
			echo "stencil_1D_SEQ"
			./stencil_1D_SEQ 4000 200000
			echo "stencil_1D"
			./stencil_1D 4000 200000
		done
		for i in {1..5}
		do
			echo "Test $i"
			echo "stencil_2D_SEQ"
			./stencil_2D_SEQ 800 2000
			echo "stencil_2D"
			./stencil_2D 800 2000
		done
		for i in {1..5}
		do
			echo "Test $i"
			echo "mat_vec_SEQ"
			./mat_vec_SEQ 25000 10000
			echo "mat_vec"
			./mat_vec 25000 10000
		done
done
exit 0