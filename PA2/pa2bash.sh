#!/bin/bash
echo "	Test: Sieve_2 Multicore"

		echo "Sieve3"
		./sieve3 100 10
		./sieve3 1000 100
		./sieve3 10000 1000
		./sieve3 100000 10000
		./sieve3 1000000 100000
		./sieve3 10000000 1000000
		./sieve3 100000000 10000000

		echo "Sieve1"
		./sieve1 100
		./sieve1 1000
		./sieve1 10000
		./sieve1 100000
		./sieve1 1000000
		./sieve1 10000000
		./sieve1 100000000

exit 0