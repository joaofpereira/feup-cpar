#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include "papiData.h"
#include "matrixOps.h"

using namespace std;

#define RUN_THREADS 4

#define MIN_DIM 600
#define MAX_DIM 3000
#define SMALL_INTERVAL 400

#define BIG_MIN_DIM 4000
#define BIG_MAX_DIM 10000
#define BIG_INTERVAL 2000


void printMenu()
{
	cout << endl << "Manual Insert Mode:" << endl;
	cout << "1. Multiplication Single thread" << endl;
	cout << "2. Multiplication Multi thread (OpenMP)" << endl;
	cout << "3. Multiplication V2 Single thread" << endl;
	cout << "4. Multiplication V2 Multi thread (OpenMP)" << endl << endl;

	cout << "Automatic Mode:" << endl;
	cout << "5. Multiplication Single thread (" << MIN_DIM << "-" << MAX_DIM << ")" << endl;
	cout << "6. Multiplication Multi thread (OpenMP) (" << MIN_DIM << "-" << MAX_DIM << ")" << endl;
	cout << "7. Multiplication V2 Single thread (" << MIN_DIM << "-" << MAX_DIM << ")" << endl;
	cout << "8. Multiplication V2 Single thread (" << BIG_MIN_DIM << "-" << BIG_MAX_DIM << ")" << endl;
	cout << "9. Multiplication V2 Multi thread (OpenMP) (" << MIN_DIM << "-" << MAX_DIM << ")" << endl;
	cout << "10. All in batch mode (can be piped to a file)" << endl << endl;
	cout << "Option?: ";
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
	// matrix dimension (line & column)
	int matDimension;

	papiData.printHeader();

	for (matDimension = minDim; matDimension <= maxDim; matDimension += dimInc)
	{
		papiData.startPapi();

		switch (op) {
			case 1:
				// multiplication single thread
				matrixOps.OnMult(matDimension, matDimension);
				break;
			case 2:
				// multiplication multi thread (OpenMP)
				matrixOps.OnMult_OMP(matDimension, matDimension, threadsCount);
				break;
			case 3:
				// multiplication single thread v2
				matrixOps.OnMultLine(matDimension, matDimension);
				break;
			case 4:
				// multiplication single thread to big matrixes v2
				matrixOps.OnMultLine(matDimension, matDimension);
				break;
			case 5:
				// multiplication multi thread v2 (OpenMP)
				matrixOps.OnMultLine_OMP(matDimension, matDimension, threadsCount);
				break;
		}

		papiData.stopPapi();
		papiData.printPapiResults();
		papiData.resetPapi();
	}
}

void askForMatrixDimension(int option, MatrixOps &matrixOps, PapiData &papiData) {
	int lin, col, threads;

	cout << "Dimensions: lins cols ? ";
	cin >> lin >> col;

	if(option == 2 || option == 4) {
		cout << "How many threads ? ";
		cin >> threads;
	}

	papiData.printHeader();
	papiData.startPapi();

	switch(option) {
		case 1:
			matrixOps.OnMult(lin, col);
			break;
		case 2:
			matrixOps.OnMult_OMP(lin, col, threads);
			break;
		case 3:
			matrixOps.OnMultLine(lin, col);
			break;
		case 4:
			matrixOps.OnMultLine_OMP(lin, col, threads);
			break;
	}

	papiData.stopPapi();
	papiData.printPapiResults();
	papiData.resetPapi();
}

int main (int argc, char *argv[])
{
	// matrix operation type
	int op;

	// number of working threads
	int threadsCount = 1;

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

		if (op == 6 || op == 9)
			threadsCount = askForWorkingThreads(nthreads);

		switch (op) {
			case 1:
				// multiplication single thread - user friendly
				askForMatrixDimension(op, matrixOps, papiData);
				break;
			case 2:
				// multiplication multi thread (OpenMP) - user friendly
				askForMatrixDimension(op, matrixOps, papiData);
				break;
			case 3:
				// multiplication single thread v2 - user friendly
				askForMatrixDimension(op, matrixOps, papiData);
				break;
			case 4:
				// multiplication multi thread (OpenMP) - user friendly
				askForMatrixDimension(op, matrixOps, papiData);
				break;
			case 5:
				// multiplication single thread - range
				doMatrixMult(op, MIN_DIM, MAX_DIM, SMALL_INTERVAL, matrixOps, papiData, 1);
				break;
			case 6:
				// multiplication multi thread (OpenMP) - range
				doMatrixMult(op, MIN_DIM, MAX_DIM, SMALL_INTERVAL, matrixOps, papiData, threadsCount);
				break;
			case 7:
				// multiplication single thread v2 - range
				doMatrixMult(op, MIN_DIM, MAX_DIM, SMALL_INTERVAL, matrixOps, papiData, 1);
				break;
			case 8:
				// multiplication single thread v2 big matrixs - range
				doMatrixMult(op, BIG_MIN_DIM, BIG_MAX_DIM, BIG_INTERVAL, matrixOps, papiData, 1);
				break;
			case 9:
				// multiplication multi thread (OpenMP) - range
				doMatrixMult(op, MIN_DIM, MAX_DIM, SMALL_INTERVAL, matrixOps, papiData, threadsCount);
				break;
			case 10:
				// all in batch mode
				cout << endl << "============  Multiplication Single thread  ============" << endl;
				doMatrixMult(1, MIN_DIM, MAX_DIM, SMALL_INTERVAL, matrixOps, papiData, 1);

				for (threadsCount = 1; threadsCount <= RUN_THREADS; threadsCount++) {
					cout << endl << "============  Multiplication " << threadsCount << " thread(s) (OpenMP)  ============" << endl;
					doMatrixMult(2, MIN_DIM, MAX_DIM, SMALL_INTERVAL, matrixOps, papiData, threadsCount);
				}

				cout << endl << "============  Multiplication V2 Single thread  ============" << endl;
				doMatrixMult(3, MIN_DIM, MAX_DIM, SMALL_INTERVAL, matrixOps, papiData, 1);
				doMatrixMult(4, BIG_MIN_DIM, BIG_MAX_DIM, BIG_INTERVAL, matrixOps, papiData, 1);

				for (threadsCount = 1; threadsCount <= RUN_THREADS; threadsCount++) {
					cout << endl << "============  Multiplication V2 " << threadsCount << " thread(s) (OpenMP)  ============" << endl;
					doMatrixMult(5, MIN_DIM, MAX_DIM, SMALL_INTERVAL, matrixOps, papiData, threadsCount);
				}
				op = 0;
				break;
		}

	} while (op != 0);

	papiData.removeAndDestoyPapi();
}