#include "Utils.h"

void printPrimesList(const bool* list, unsigned long size) {
	ofstream out;
	out.open("primes-list.txt");

	for (unsigned long i = 0; i < size; i++)
		if (list[i])
			out << i << endl;

	out.clear();
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
