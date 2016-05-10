#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <mpi.h>

using namespace std;

int countPrimes(map<unsigned int, bool> list) {
	int counter = 0;
	auto it = list.begin();

	for(it; it != list.end(); it++)
		if(!it->second)
			counter++;

	return counter;
}

void printFullList(map<unsigned int, bool> list)
{
	ofstream out;
	out.open ("full-list.txt");

	out << "Range: " << list.size() << endl << endl;

	for(auto it = list.begin(); it != list.end(); it++)
		out << it->first << endl;


	out.close();
}

void printPrimesList(map<unsigned int, bool> list)
{
	ofstream out;
	out.open ("results.txt");

	out << "Range: " << list.size() << endl;
	out << "Total of Primes: " << countPrimes(list) << endl << endl;

	for(auto it = list.begin(); it != list.end(); it++)
		if(!it->second)
			out << it->first << endl;

	out.close();
}

map<unsigned int, bool> buildList(unsigned int size)
{
	map<unsigned int, bool> list;

	for (unsigned int i = 2; i <= size; i++)
		list.insert ( std::pair<unsigned int, bool>(i, false) );

	return list;
}

void processList(map<unsigned int, bool>& list)
{
	// starting with minimum prime 2
	unsigned int min = 2;

	// repeat process until min^2 < N
	while (pow(min, 2) <= list.size())
	{
		// get the index of the square of the current minimum value and mark it
		auto it = list.find(pow(min, 2));

		for(it; it != list.end(); it++)
			if(it->first % min == 0)
				it->second = true;

		it = list.find(min + 1);
		for(it; it != list.end(); it++)
		{
			if(!it->second)
			{
				min = it->first;
				break;
			}

		}
	}
}

void sequencialMode()
{
	unsigned int N;

	cout << "Insert a number to find the primes: ";
	cin >> N;

	map<unsigned int, bool> list = buildList(N);

	//printFullList(list);

	processList(list);

	printPrimesList(list);
}

void printMenu()
{
	cout << endl << "Sequencial Mode:" << endl;
	cout << "1. Single CPU-core" << endl << endl;

	cout << "Parallel Mode:" << endl;
	cout << "2. OpenMP - shared memory system"<< endl;
	cout << "3. MPI - distributed memory system" << endl;
	cout << "4. MPI - shared memory system" << endl << endl;

	cout << "0 Exit" << endl << endl;
	cout << "Option: ";
}

int main(int argc, char **argv)
{
	int option;

	do {
		printMenu();
		cin >> option;

		switch (option) {
			case 0:
				break;
			case 1:
				cout << "\nSingle CPU-core\n";
				sequencialMode();
				break;
			case 2:
				cout << "\nOpenMP -  shared memory system\n";
				break;
			case 3:
				cout << "\nMPI - distributed memory system\n";
				break;
			case 4:
				cout << "\nMPI - shared memory system\n";
				break;
			default:
				cout << "\nInvalid option! Try again...\n";
				break;
		}

	} while (option != 0);

	return 0;
}
