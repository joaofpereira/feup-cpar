all: Sieve SieveMPI SieveMPI_OMP

Sieve:
	mpic++ -std=c++11 -o Sieve Main.cpp Utils.h Utils.cpp SequentialSieve.h SequentialSieve.cpp OpenMPSieve.h OpenMPSieve.cpp -O3 -fopenmp -Wall

SieveMPI:
	mpic++ -std=c++11 -o SieveMPI OpenMPISieve.cpp OpenMPISieve.h Utils.cpp Utils.h -O2 -fopenmp -Wall

SieveMPI_OMP:
	mpic++ -std=c++11 -o SieveMPI_OMP OpenMPI_OMPSieve.cpp OpenMPI_OMPSieve.h Utils.cpp Utils.h -O2 -fopenmp -Wall

clean:
	rm -r Sieve SieveMPI SieveMPI_OMP

pc1:
	for p in 4; do \
		for n in 25 26 27 28 29 30 31 32; do \
			mpirun --hostfile hostfile1 -np $$p SieveMPI $$n ; \
		done; \
	done; \

pc2:
	for p in 2 3 4 5 6 7 8; do \
		for n in 25 26 27 28 29 30 31 32; do \
			mpirun --hostfile hostfile2 -np $$p SieveMPI $$n ; \
		done; \
	done; \

pc3:
	for p in 4 5 6 7 8 9 10 11 12 13 14 15 16; do \
		for n in 25 26 27 28 29 30 31 32; do \
			mpirun --hostfile hostfile3 -np $$p SieveMPI $$n ; \
		done; \
	done; \

pc4:
	for p in 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32; do \
		for n in 25 26 27 28 29 30 31 32; do \
			mpirun --hostfile hostfile4 -np $$p SieveMPI $$n ; \
		done; \
	done; \

opc1:
	for t in 1 2 3 4 5 6 7 8; do \
		for p in 4; do \
			for n in 25 26 27 28 29 30 31 32; do \
				mpirun --hostfile hostfile1 -np $$p SieveMPI_OMP $$n $$t; \
			done; \
		done; \
	done; \

opc2:
	for t in 1 2 3 4 5 6 7 8; do \
		for p in 2 3 4 5 6 7 8; do \
			for n in 25 26 27 28 29 30 31 32; do \
				mpirun --hostfile hostfile2 -np $$p SieveMPI_OMP $$n $$t; \
			done; \
		done; \
	done; \

opc3:
	for t in 1 2 3 4 5 6 7 8; do \
		for p in 4 5 6 7 8 9 10 11 12 13 14 15 16; do \
			for n in 25 26 27 28 29 30 31 32; do \
				mpirun --hostfile hostfile3 -np $$p SieveMPI_OMP $$n $$t; \
			done; \
		done; \
	done; \

opc4:
	for t in 1 2 3 4 5 6 7 8; do \
		for p in 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32; do \
			for n in 25 26 27 28 29 30 31 32; do \
				mpirun --hostfile hostfile4 -np $$p SieveMPI_OMP $$n $$t; \
			done; \
		done; \
	done; \
