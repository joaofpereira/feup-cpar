#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

void sieve(vector<bool>& list) {
	list[0] = false;
	list[1] = false;

	for (unsigned int p = 2; pow(p, 2) < list.size();) {

		for (unsigned int i = 2; i * p < list.size(); i++)
			list[i * p] = false;

		do {
			p++;
		} while (!list[p] && pow(p, 2) < list.size());

	}
}

vector<bool> newList(unsigned int n) {
	return vector<bool>(n, true);
}

void printList(const vector<bool>& list) {
	for (auto elem : list)
		cout << elem;
	cout << endl;
}

void sequentialMode() {
	unsigned int n;

	cout << "Insert a number to find the primes: ";
	cin >> n;

	vector<bool> list = newList(n);

	sieve(list);

	printList(list);
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
			cout << endl;
			cout << "---------------" << endl;
			cout << "Single CPU-core" << endl;
			cout << "---------------" << endl;
			cout << endl;

			sequentialMode();

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
