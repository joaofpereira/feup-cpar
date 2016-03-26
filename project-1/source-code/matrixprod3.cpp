#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include "papiData.h"
#include "matrixOps.h"

using namespace std;

#define MIN_DIM 600
#define MAX_DIM 3000
#define SMALL_INTERVAL 400

#define BIG_MIN_DIM 4000
#define BIG_MAX_DIM 10000
#define BIG_INTERVAL 2000


void printMenu()
{
	cout << endl << "1. Multiplication Single thread (" << MIN_DIM << "-" << MAX_DIM << ")" << endl;
	cout << "2. Multiplication Multi thread (OpenMP) (" << MIN_DIM << "-" << MAX_DIM << ")" << endl;
	cout << "3. Multiplication V2 Single thread (" << MIN_DIM << "-" << MAX_DIM << ")" << endl;
	cout << "4. Multiplication V2 Single thread (" << BIG_MIN_DIM << "-" << BIG_MAX_DIM << ")" << endl;
	cout << "5. Multiplication V2 Multi thread (OpenMP) (" << MIN_DIM << "-" << MAX_DIM << ")" << endl;
	cout << "6. All in batch mode (can be piped to a file)" << endl << endl;
	cout << "Selection?: ";
}

int askForWorkingThreads(int maxThreads)
{
	int threadsCount;
	
	cout << "How many working threads?: ";
	scanf("%d", &threadsCount);
	if(threadsCount < 1)
		threadsCount = 1;
	else if(threadsCount > maxThreads)
		threadsCount = maxThreads;
	cout << "Working threads: " << threadsCount << endl;
	return threadsCount;
}

void doMatrixMult(int op, int minDim, int maxDim, int dimInc, MatrixOps &matrixOps, PapiData &papiData, int threadsCount)
{
	int matDimension;			// Matrix Dimension (line & column)
	
	papiData.printHeader();
	
	for (matDimension = minDim; matDimension <= maxDim; matDimension += dimInc)
	{
		papiData.startPapi();

		switch (op) {
			case 1:				// Multiplication Single thread
				matrixOps.OnMult(matDimension, matDimension);
				break;
			case 2:				// Multiplication Multi thread (OpenMP)
				matrixOps.OnMult_OMP(matDimension, matDimension, threadsCount);
				break;
			case 3:				// Multiplication V2 Single thread
				matrixOps.OnMultLine(matDimension, matDimension);
				break;
			case 4:				// Multiplication V2 Single thread Big matrixs
				matrixOps.OnMultLine(matDimension, matDimension);
				break;
			case 5:				// Multiplication V2 Multi thread (OpenMP)
				matrixOps.OnMultLine_OMP(matDimension, matDimension, threadsCount);
				break;
		}

		papiData.stopPapi();
		papiData.printPapiResults();
		papiData.resetPapi();
	}
}

int main (int argc, char *argv[])
{
	int op;						// Matrix operation type
	int threadsCount = 1;		// Number of working threads
	
	PapiData papiData;
	MatrixOps matrixOps;

	// ------  Some Infos  ------
	int nthreads = omp_get_max_threads();
	int ncpus = omp_get_num_procs();
	cout << nthreads << " Thread(s) available(s)." << endl;
	cout << ncpus << " CPU(s) available(s)." << endl;
	
	// ------  Init PAPI  ------
	papiData.initPapi();
	papiData.setPapiEvents();

	do {
		printMenu();
		scanf("%d", &op);

		if (op == 0) break;
		
		if (op == 2 || op == 5)
			threadsCount = askForWorkingThreads(nthreads);
		
		//papiData.printHeader();

		switch (op) {
			case 1:				// Multiplication Single thread
				doMatrixMult(op, MIN_DIM, MAX_DIM, SMALL_INTERVAL, matrixOps, papiData, 1);
				break;
			case 2:				// Multiplication Multi thread (OpenMP)
				doMatrixMult(op, MIN_DIM, MAX_DIM, SMALL_INTERVAL, matrixOps, papiData, threadsCount);
				break;
			case 3:				// Multiplication V2 Single thread
				doMatrixMult(op, MIN_DIM, MAX_DIM, SMALL_INTERVAL, matrixOps, papiData, 1);
				break;
			case 4:				// Multiplication V2 Single thread Big matrixs
				doMatrixMult(op, BIG_MIN_DIM, BIG_MAX_DIM, BIG_INTERVAL, matrixOps, papiData, 1);
				break;
			case 5:				// Multiplication V2 Multi thread (OpenMP)
				doMatrixMult(op, MIN_DIM, MAX_DIM, SMALL_INTERVAL, matrixOps, papiData, threadsCount);
				break;
			case 6:				// All in batch mode
				cout << endl << "============  Multiplication Single thread  ============" << endl;
				doMatrixMult(1, MIN_DIM, MAX_DIM, SMALL_INTERVAL, matrixOps, papiData, 1);
				
				for (threadsCount = 1; threadsCount <= nthreads; threadsCount++) {
					cout << endl << "============  Multiplication " << threadsCount << " thread(s) (OpenMP)  ============" << endl;
					doMatrixMult(2, MIN_DIM, MAX_DIM, SMALL_INTERVAL, matrixOps, papiData, threadsCount);
				}
				
				cout << endl << "============  Multiplication V2 Single thread  ============" << endl;
				doMatrixMult(3, MIN_DIM, MAX_DIM, SMALL_INTERVAL, matrixOps, papiData, 1);
				doMatrixMult(4, BIG_MIN_DIM, BIG_MAX_DIM, BIG_INTERVAL, matrixOps, papiData, 1);
				
				for (threadsCount = 1; threadsCount <= nthreads; threadsCount++) {
					cout << endl << "============  Multiplication V2 " << threadsCount << " thread(s) (OpenMP)  ============" << endl;
					doMatrixMult(5, MIN_DIM, MAX_DIM, SMALL_INTERVAL, matrixOps, papiData, threadsCount);
				}
				op = 0;
				break;
		}

	} while (op != 0);

	papiData.removeAndDestoyPapi();
}