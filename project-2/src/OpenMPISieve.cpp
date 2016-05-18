#include "OpenMPISieve.h"

void openMPISieve(unsigned long n, ofstream& out) {
	int rank, size;
	double openMPITime = 0;
	bool* list;
	unsigned long startBlockValue, counter = 0, primes = 0;

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// calculate the lower and higher values of each process and its offset
	unsigned long blockSize = BLOCK_SIZE(rank, n - 1, size);
	unsigned long lowValue = BLOCK_LOW(rank, n - 1, size) + 2;
	unsigned long highValue = BLOCK_HIGH(rank, n - 1, size) + 2;

	// initializes the list
	list = newList(blockSize);

	MPI_Barrier (MPI_COMM_WORLD);

	if(rank == 0) {
		openMPITime = -MPI_Wtime();
		out << size << ";" << n << ";";
	}

	for (unsigned long p = 2; pow(p, 2) <= n;) {
		// calculate the start block value to each process
		if (pow(p, 2) < lowValue) {
			lowValue % p == 0 ?
					startBlockValue = lowValue :
					startBlockValue = lowValue + (p - (lowValue % p));
		} else {
			startBlockValue = pow(p, 2);
		}

		// mark the multiples of each prime
		for (unsigned long i = startBlockValue; i <= highValue; i += p)
			list[i - lowValue] = false;

		// get the next prime to broadcast it to the other processes
		if (rank == 0) {
			do {
				p++;
			} while (!list[p - lowValue] && pow(p, 2) < highValue);
		}

		MPI_Bcast(&p, 1, MPI_LONG, 0, MPI_COMM_WORLD);
	}

	if(rank == 0) {
		openMPITime += MPI_Wtime();
		out << openMPITime << ";";
	}

	// count all the primes
	for (unsigned long i = 0; i < blockSize; i++)
		if (list[i])
			counter++;

	// reduce the counter to multiple processes
	if (size > 1)
		MPI_Reduce(&counter, &primes, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
	else
		primes = counter;

	if(rank == 0)
		out << primes << endl;

	free(list);
}

int main(int argc, char** argv) {
	ofstream out;
  	out.open ("openmpi.csv", ios::app);

	MPI_Init(&argc, &argv);

	unsigned long n = pow(2, (unsigned long) atol(argv[1]));

	openMPISieve(n, out);

	MPI_Finalize();

	return 0;
}
