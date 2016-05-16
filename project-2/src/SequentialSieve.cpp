#include "SequentialSieve.h"

double sequencialSieve(bool* list, unsigned long size) {
	double sequencialTime;

	sequencialTime = -clock();		// Start Clock counting

	list[0] = false;
	list[1] = false;

	for (unsigned long p = 2; pow(p, 2) < size;) {

		for (unsigned long i = pow(p, 2); i < size; i += p)
			list[i] = false;

		do {
			p++;
		} while (!list[p] && pow(p, 2) < size);

	}

	sequencialTime += clock();		// Stop Clock counting

	return sequencialTime;
}
