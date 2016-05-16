#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <sstream>

#include "Utils.h"
#include "SequentialSieve.h"
#include "OpenMPSieve.h"

#define MIN 25
#define MAX 32

using namespace std;

void sequencialMode(bool automatic) {

	bool* list;
	unsigned long size;

	cout << endl;
	cout << "---------------" << endl;
	cout << "Single CPU-core" << endl;
	cout << "---------------" << endl;
	cout << endl;

	ofstream out;
	out.open("single-core.txt");

	if (automatic) {
		for (unsigned int i = MIN; i <= MAX; i++) {
			size = pow(2, i);

			size++;

			list = newList(size);

			out << i << ";"
					<< (double) sequencialSieve(list, size) / CLOCKS_PER_SEC
					<< endl;

			free(list);
		}
	}

	else {

		cout << "Insert a number to find the primes: ";
		cin >> size;

		size++;

		list = newList(size);

		out << (double) sequencialSieve(list, size) / CLOCKS_PER_SEC << ";";

		printPrimesList(list, size);

		free(list);
	}

	out.close();
}

void openMPMode(bool automatic) {

	bool* list;
	unsigned long size;

	cout << endl;
	cout << "---------------" << endl;
	cout << "OpenMP Mode" << endl;
	cout << "---------------" << endl;
	cout << endl;

	// ------  Some Infos  ------
	int nthreads = omp_get_max_threads();
	int ncpus = omp_get_num_procs();
	cout << nthreads << " Thread(s) available(s)." << endl;
	cout << ncpus << " CPU(s) available(s)." << endl;

	int threadsCount = askForWorkingThreads(nthreads);

	ofstream out;
	out.open("openmp.txt");

	if (automatic) {
		for (unsigned int i = MIN; i <= MAX; i++) {
			size = pow(2, i);

			size++;

			list = newList(size);

			out << i << ";" << (double) openMPSieve(list, size, threadsCount)
					<< endl;

			free(list);
		}
	}

	else {
		cout << "Insert a number to find the primes: ";
		cin >> size;

		size++;

		list = newList(size);

		out << (double) openMPSieve(list, size, threadsCount) << ";";

		//printPrimesList(list, size);

		free(list);
	}

	out.close();
}

void openMPIMode(bool automatic) {

	unsigned long size;
	unsigned int numProc;
	stringstream mpirun;

	cout << endl;
	cout << "---------------" << endl;
	cout << "OpenMPI Mode" << endl;
	cout << "---------------" << endl;
	cout << endl;

	cout << endl << "MPI number of processes: ";
	cin >> numProc;

	while (numProc != 1 && numProc != 2 && numProc != 3 && numProc != 4) {
		cout << endl
				<< "MPI number of processes wrong, please enter again in the range (1-4)\n";
		cout << endl << "MPI number of processes: ";
		cin >> numProc;
	}

	if (automatic) {
		for (unsigned int i = MIN; i <= MAX; i++) {
			size = pow(2, i);

			cout << "Numbers: " << size << endl;

			mpirun << "mpirun -np ";
			mpirun << numProc;
			mpirun << " SieveMPI ";
			mpirun << size;

			cout << "String: " << mpirun.str() << endl;

			cout << endl << "Results For 2^" << i << " Numbers: " << endl;

			system(mpirun.str().c_str());

			mpirun.clear();
			mpirun.str("");
		}
	} else {
		cout << "Insert a number to find the primes: ";
		cin >> size;

		mpirun << "mpirun -np ";
		mpirun << numProc;
		mpirun << " SieveMPI ";
		mpirun << size;

		system(mpirun.str().c_str());
	}
}

void openMPI_OMPMode(bool automatic) {

	unsigned long size;
	unsigned int numProc;
	stringstream mpirun;
	int nthreads, ncpus, threadsCount;

	cout << endl;
	cout << "---------------" << endl;
	cout << "OpenMPI & OpenMP Mode" << endl;
	cout << "---------------" << endl;
	cout << endl;

	// asking for the number of threads
	nthreads = omp_get_max_threads();
	ncpus = omp_get_num_procs();
	cout << nthreads << " Thread(s) available(s)." << endl;
	cout << ncpus << " CPU(s) available(s)." << endl;

	threadsCount = askForWorkingThreads(nthreads);

	// asking for the number of processes
	cout << endl << "MPI number of processes: ";
	cin >> numProc;

	while (numProc != 1 && numProc != 2 && numProc != 3 && numProc != 4) {
		cout << endl
				<< "MPI number of processes wrong, please enter again in the range (1-4)\n";
		cout << endl << "MPI number of processes: ";
		cin >> numProc;
	}

	if (automatic) {
		for (unsigned int i = MIN; i <= MAX; i++) {
			size = pow(2, i);

			mpirun << "mpirun -np ";
			mpirun << numProc;
			mpirun << " SieveMPI_OMP ";
			mpirun << size << " ";
			mpirun << threadsCount;

			cout << endl << "Results For 2^" << i << " Numbers: " << endl;

			system(mpirun.str().c_str());

			mpirun.clear();
			mpirun.str("");
		}
	} else {
		cout << "Insert a number to find the primes: ";
		cin >> size;

		mpirun << "mpirun -np ";
		mpirun << numProc;
		mpirun << " SieveMPI_OMP ";
		mpirun << size << " ";
		mpirun << threadsCount;

		system(mpirun.str().c_str());
	}
}

void openMPI_OMPMenu() {
	int option;

	do {
		cout << endl;
		cout << "OPENMPI & OPENMP Mode:" << endl;
		cout << "  1. Manually" << endl;
		cout << "  2. Automatic" << endl;
		cout << endl;

		cout << "  0. Exit" << endl;
		cout << endl;

		cout << "Option: ";

		cin >> option;

		switch (option) {
		case 0:
			break;
		case 1:
			openMPI_OMPMode(false);
			break;

		case 2:
			openMPI_OMPMode(true);
			break;

		default:
			cout << endl;
			cout << "Invalid option! Try again..." << endl;
			break;
		}

	} while (option != 0);
}

void openMPIMenu() {
	int option;

	do {
		cout << endl;
		cout << "OPENMPI Mode:" << endl;
		cout << "  1. Manually" << endl;
		cout << "  2. Automatic" << endl;
		cout << endl;

		cout << "  0. Exit" << endl;
		cout << endl;

		cout << "Option: ";

		cin >> option;

		switch (option) {
		case 0:
			break;
		case 1:
			openMPIMode(false);
			break;

		case 2:
			openMPIMode(true);
			break;

		default:
			cout << endl;
			cout << "Invalid option! Try again..." << endl;
			break;
		}

	} while (option != 0);
}

void openMPMenu() {
	int option;

	do {
		cout << endl;
		cout << "OPENMP Mode:" << endl;
		cout << "  1. Manually" << endl;
		cout << "  2. Automatic" << endl;
		cout << endl;

		cout << "  0. Exit" << endl;
		cout << endl;

		cout << "Option: ";

		cin >> option;

		switch (option) {
		case 0:
			break;
		case 1:
			openMPMode(false);
			break;

		case 2:
			openMPMode(true);
			break;

		default:
			cout << endl;
			cout << "Invalid option! Try again..." << endl;
			break;
		}

	} while (option != 0);
}

void sequentialMenu() {
	int option;

	do {
		cout << endl;
		cout << "Single Core Mode:" << endl;
		cout << "  1. Manually" << endl;
		cout << "  2. Automatic" << endl;
		cout << endl;

		cout << "  0. Exit" << endl;
		cout << endl;

		cout << "Option: ";

		cin >> option;

		switch (option) {
		case 0:
			break;
		case 1:
			sequencialMode(false);
			break;

		case 2:
			sequencialMode(true);
			break;

		default:
			cout << endl;
			cout << "Invalid option! Try again..." << endl;
			break;
		}

	} while (option != 0);
}

void printMenu() {
	cout << endl;
	cout << "Sequential Mode:" << endl;
	cout << "  1. Single CPU-core" << endl;
	cout << endl;

	cout << "Parallel Mode:" << endl;
	cout << "  2. OpenMP - shared memory system" << endl;
	cout << "  3. MPI - distributed memory system" << endl;
	cout << "  4. MPI and OpenMP - shared memory system" << endl;
	cout << endl;

	cout << "0. Exit" << endl;
	cout << endl;

	cout << "Option: ";
}

int main() {
	int option;

	do {
		printMenu();
		cin >> option;

		switch (option) {
		case 0:
			break;

		case 1:
			sequentialMenu();
			break;

		case 2:
			cout << endl;
			openMPMenu();
			break;

		case 3:
			cout << endl;
			openMPIMenu();
			break;

		case 4:
			cout << endl;
			openMPI_OMPMenu();
			break;

		default:
			cout << endl;
			cout << "Invalid option! Try again..." << endl;
			break;
		}

	} while (option != 0);

	cout << endl;
	cout << "- All done. -" << endl;
	cout << endl;

	return 0;
}
