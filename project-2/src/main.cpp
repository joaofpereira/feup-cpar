#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <omp.h>

#define MIN 25
#define MAX 32

using namespace std;

static double singleCoreTime[2]; // start and end time
static double openMPTime[2]; // start and end time

void printPrimesList(const bool* list, unsigned long size) {
	ofstream out;
	out.open("primes-list.txt");

	for (unsigned long i = 0; i < size; i++)
		if (list[i])
			out << i << endl;

	out.clear();
}

void printList(const vector<bool>& list) {
	for (auto elem : list)
		cout << elem;
	cout << endl;
}

bool* newList(unsigned long n) {
	bool* list = (bool*) malloc(n * sizeof(bool));

	fill_n(list, n, true);

	return list;
}

int askForWorkingThreads(int maxThreads) {
	int threadsCount;

	cout << "MAX: " << maxThreads << endl;

	cout << "How many working threads?: ";
	cin >> threadsCount;
	if (threadsCount < 1)
		threadsCount = 1;
	else if (threadsCount > maxThreads)
		threadsCount = maxThreads;
	cout << "Working threads: " << threadsCount << endl;
	return threadsCount;
}

void sequencialSieve(bool* list, unsigned long size) {
	singleCoreTime[0] = clock();		// Start Clock counting

	list[0] = false;
	list[1] = false;

	for (unsigned long p = 2; pow(p, 2) < size;) {

		for (unsigned long i = pow(p, 2); i < size; i += p)
			list[i] = false;

		do {
			p++;
		} while (!list[p] && pow(p, 2) < size);

	}

	singleCoreTime[1] = clock();		// Stop Clock counting
}

void openMPSieve(bool* list, unsigned long size, int& threads) {

	omp_set_num_threads(threads);	// Apply working threads

	openMPTime[0] = omp_get_wtime();		// Start Clock counting

	list[0] = false;
	list[1] = false;

	for (unsigned long p = 2; pow(p, 2) < size;) {
#pragma omp parallel for
		for (unsigned long i = pow(p, 2); i < size; i += p)
			list[i] = false;

		do {
			p++;
		} while (!list[p] && pow(p, 2) < size);

	}

	openMPTime[1] = omp_get_wtime();		// Stop Clock counting
}

void sequentialMode(bool automatic) {

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

			sequencialSieve(list, size);

			out << i << ";"
					<< (double) (singleCoreTime[1] - singleCoreTime[0])
							/ CLOCKS_PER_SEC << endl;

			free(list);
		}
	}

	else {

		cout << "Insert a number to find the primes: ";
		cin >> size;

		size++;

		list = newList(size);

		sequencialSieve(list, size);

		out << (double) (singleCoreTime[1] - singleCoreTime[0]) / CLOCKS_PER_SEC
				<< ";";

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

			openMPSieve(list, size, threadsCount);

			out << i << ";" << (double) (openMPTime[1] - openMPTime[0]) << endl;

			free(list);
		}
	}

	else {
		cout << "Insert a number to find the primes: ";
		cin >> size;

		size++;

		list = newList(size);

		openMPSieve(list, size, threadsCount);

		out << (double) (openMPTime[1] - openMPTime[0]) << ";";

		printPrimesList(list, size);

		free(list);
	}

	out.close();
}

void printSingleCoreMenu() {
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
			sequentialMode(false);
			break;

		case 2:
			sequentialMode(true);
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
	cout << "  4. MPI - shared memory system" << endl;
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
			printSingleCoreMenu();
			break;

		case 2:
			cout << endl;
			openMPMode(true);
			break;

		case 3:
			cout << endl;
			cout << "MPI - distributed memory system" << endl;
			break;

		case 4:
			cout << endl;
			cout << "MPI - shared memory system" << endl;
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
