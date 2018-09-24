#!/bin/bash

echo "		jac"
./jac 12000 1200

for t in {1..6}
	do
		export OMP_NUM_THREADS=$t
		echo "		jacOMP with $t threads"
		./jacOMP 12000 1200
done

for t in {1..6}
	do
		# export OMP_NUM_THREADS=$t
		# echo "		jacOMP with $t threads"
    # ./jacOMP 120000 12000
done

# mpirun _np 2 __hostfile h2 jacMPI n m


exit 0
