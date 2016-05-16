all: Sieve SieveMPI

Sieve:
	mpic++ -std=c++11 -o Sieve Main.cpp Utils.h Utils.cpp SequentialSieve.h SequentialSieve.cpp OpenMPSieve.h OpenMPSieve.cpp -O3 -fopenmp -Wall

SieveMPI:
	mpic++ -std=c++11 -o SieveMPI OpenMPISieve.cpp OpenMPISieve.h Utils.cpp Utils.h -O3 -fopenmp -Wall

clean:
	rm -r Sieve SieveMPI