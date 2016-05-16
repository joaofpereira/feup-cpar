#ifndef OPENMPISIEVE_H
#define OPENMPISIEVE_H

#include <iostream>
#include <mpi.h>
#include <cmath>
#include <cstdlib>

#include "Utils.h"

#define BLOCK_LOW(i, n, p) ((i) * (n) / (p))
#define BLOCK_HIGH(i, n, p) (BLOCK_LOW((i) + 1, n, p) - 1)
#define BLOCK_SIZE(i, n, p) (BLOCK_LOW((i) + 1, n, p) - BLOCK_LOW(i, n, p))
#define BLOCK_OWNER(index, n, p) ((((p) * (index) + 1) - 1) / (n))

using namespace std;

double openMPISieve(bool* list, unsigned long size);

#endif
