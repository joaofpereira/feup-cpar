#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <omp.h>

#define MIN 2
#define MAX 5

using namespace std;

static int singleCoreTime[2]; // start and end time
static int openMPTime[2]; // start and end time

void sieve(vector<bool>& list) {
	list[0] = false;
	list[1] = false;

	singleCoreTime[0] = clock();		// Start Clock counting

	for (unsigned int p = 2; pow(p, 2) < list.size();) {

		for (unsigned int i = 2; i * p < list.size(); i++)
			list[i * p] = false;

		do {
			p++;
		} while (!list[p] && pow(p, 2) < list.size());

	}

	singleCoreTime[1] = clock();		// Start Clock counting
}

vector<bool> newList(unsigned int n) {
	return vector<bool>(n, true);
}

void printList(const vector<bool>& list) {
	for (auto elem : list)
		cout << elem;
	cout << endl;
}

void sequentialMode(bool automatic) {

	cout << endl;
	cout << "---------------" << endl;
	cout << "Single CPU-core" << endl;
	cout << "---------------" << endl;
	cout << endl;

	ofstream out;
	out.open("single-core.txt");

	if (automatic) {
		for (unsigned int i = MIN; i <= MAX; i++) {
			vector<bool> list = newList(pow(2, i));
			sieve(list);

			out << i << ";" << (double) (singleCoreTime[1] - singleCoreTime[0]) / CLOCKS_PER_SEC << endl;
		}
	}

	else {
		unsigned int n;

		cout << "Insert a number to find the primes: ";
		cin >> n;

		vector<bool> list = newList(n);

		sieve(list);

		out << (double) (singleCoreTime[1] - singleCoreTime[0]) / CLOCKS_PER_SEC << ";";
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

int main(int argc, char **argv) {
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
			cout << "OpenMP -  shared memory system" << endl;
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
