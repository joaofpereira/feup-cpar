#include "OpenMPSieve.h"

double openMPSieve(bool* list, unsigned long size, int& threads) {
	double openMPTime;

	omp_set_num_threads(threads);	// Apply working threads

	openMPTime = -omp_get_wtime();		// Start Clock counting

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

	openMPTime += omp_get_wtime();		// Stop Clock counting

	return openMPTime;
}
