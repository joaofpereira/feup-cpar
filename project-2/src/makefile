all: Sieve SieveMPI SieveMPI_OMP

Sieve:
	mpic++ -std=c++11 -o Sieve Main.cpp Utils.h Utils.cpp SequentialSieve.h SequentialSieve.cpp OpenMPSieve.h OpenMPSieve.cpp -O3 -fopenmp -Wall

SieveMPI:
	mpic++ -std=c++11 -o SieveMPI OpenMPISieve.cpp OpenMPISieve.h Utils.cpp Utils.h -O2 -fopenmp -Wall

SieveMPI_OMP:
	mpic++ -std=c++11 -o SieveMPI_OMP OpenMPI_OMPSieve.cpp OpenMPI_OMPSieve.h Utils.cpp Utils.h -O2 -fopenmp -Wall

clean:
	rm -r Sieve SieveMPI SieveMPI_OMP