#ifndef OPENMPSIEVE_H
#define OPENMPSIEVE_H

#include <iostream>
#include <omp.h>
#include <cmath>

using namespace std;

double openMPSieve(bool* list, unsigned long size, int& threads);

#endif
