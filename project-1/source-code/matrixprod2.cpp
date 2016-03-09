#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <papi.h>

using namespace std;

#define SYSTEMTIME clock_t
#define SMALL_INTERVAL 400
#define BIG_INTERVAL 2000


void OnMult(int m_ar, int m_br) 
{
	SYSTEMTIME time1, time2;	// counting timers
	
	char st[100];				// Output print buffer
	double temp;				// Matrix prod temp
	int i, j, k;				// Matrix iterators

	double *pha, *phb, *phc;	// Matrix's
	
	// -----  Matrix's Inits ---------

	pha = (double *)malloc((m_ar * m_ar) * sizeof(double));		// Matrix A Mem Space Alloc
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));		// Matrix B Mem Space Alloc
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));		// Matrix C Mem Space Alloc

	for(i=0; i<m_ar; i++)					// Init Matrix A
		for(j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1.0;

	for(i=0; i<m_br; i++)					// Init Matrix B
		for(j=0; j<m_br; j++)
			phb[i*m_br + j] = (double)(i+1);

	// -------------------  Matrix Prod (A.B = C)  -------------------------------

	time1 = clock();		// Start Clock counting

	for(i=0; i<m_ar; i++) {
		for(j=0; j<m_br; j++) {
			temp = 0;
			for(k=0; k<m_ar; k++)
			{
				temp += pha[i*m_ar+k] * phb[k*m_br+j];
			}
			phc[i*m_ar+j]=temp;
		}
	}

	time2 = clock();		// Stop Clock counting
	
	// -------------------  Print Results  ---------------------------------------
	
	sprintf(st, "%3.3f\t", (double)(time2 - time1) / CLOCKS_PER_SEC);		// Print elapsed time
	cout << st;

	/*cout << "\tResult matrix: ";// << endl;
	for(i=0; i<1; i++) {
		for(j=0; j<min(10,m_br); j++)
			cout << phc[j] << " ";			// Print at most 10 elems of first line of Final Matrix
	}
	//cout << endl; */

	free(pha);		// Free Matrix A allocated Memory
	free(phb);		// Free Matrix B allocated Memory
	free(phc);		// Free Matrix C allocated Memory
}

void OnMult_OMP(int m_ar, int m_br, int threads) 
{
	double time1, time2;		// counting timers
	
	char st[100];				// Output print buffer
	double temp;				// Matrix prod temp
	int i, j, k;				// Matrix iterators

	double *pha, *phb, *phc;	// Matrix's

	omp_set_num_threads(threads);
	
	// -----  Matrix's Inits ---------

	pha = (double *)malloc((m_ar * m_ar) * sizeof(double));		// Matrix A Mem Space Alloc
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));		// Matrix B Mem Space Alloc
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));		// Matrix C Mem Space Alloc

	for(i=0; i<m_ar; i++)					// Init Matrix A
		for(j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1.0;

	for(i=0; i<m_br; i++)					// Init Matrix B
		for(j=0; j<m_br; j++)
			phb[i*m_br + j] = (double)(i+1);

	// -------------------  Matrix Prod (A.B = C)  -------------------------------

	time1 = omp_get_wtime();		// Start Clock counting

	for(i=0; i<m_ar; i++) {
		for(j=0; j<m_br; j++) {
			temp = 0;
			#pragma omp parallel for reduction(+:temp)
			for(k=0; k<m_ar; k++)
			{
				temp += pha[i*m_ar+k] * phb[k*m_br+j];
			}
			phc[i*m_ar+j]=temp;
		}
	}

	time2 = omp_get_wtime();		// Stop Clock counting
	
	// -------------------  Print Results  ---------------------------------------
	
	sprintf(st, "%3.3f\t", (double)(time2 - time1));		// Print elapsed time
	cout << st;

	/*cout << "\tResult matrix: ";// << endl;
	for(i=0; i<1; i++) {
		for(j=0; j<min(10,m_br); j++)
			cout << phc[j] << " ";			// Print at most 10 elems of first line of Final Matrix
	}
	//cout << endl; */

	free(pha);		// Free Matrix A allocated Memory
	free(phb);		// Free Matrix B allocated Memory
	free(phc);		// Free Matrix C allocated Memory
}

void OnMultLine(int m_ar, int m_br)
{
	SYSTEMTIME time1, time2;	// counting timers
	
	char st[100];				// Output print buffer
	int i, j, k;				// Matrix iterators

	double *pha, *phb, *phc;	// Matrix's
	
	// -----  Matrix's Inits ---------

	pha = (double *)malloc((m_ar * m_ar) * sizeof(double));		// Matrix A Mem Space Alloc
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));		// Matrix B Mem Space Alloc
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));		// Matrix C Mem Space Alloc

	for(i=0; i<m_ar; i++)					// Init Matrix A
		for(j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1.0;

	for(i=0; i<m_br; i++)					// Init Matrix B
		for(j=0; j<m_br; j++)
			phb[i*m_br + j] = (double)(i+1);

	// -------------------  Matrix Prod (A.B = C)  -------------------------------

	time1 = clock();		// Start Clock counting

	for(i=0; i<m_ar; i++) {
		for(j=0; j<m_br; j++) {
			for(k=0; k<m_ar; k++)
			{
				phc[i*m_ar+k] += pha[i*m_ar+j] * phb[j*m_br+k];
			}
		}
	}

	time2 = clock();		// Stop Clock counting
	
	// -------------------  Print Results  ---------------------------------------
	
	sprintf(st, "%3.3f\t", (double)(time2 - time1) / CLOCKS_PER_SEC);		// Print elapsed time
	cout << st;

	/*cout << "\tResult matrix: ";// << endl;
	for(i=0; i<1; i++) {
		for(j=0; j<min(10,m_br); j++)
			cout << phc[j] << " ";			// Print at most 10 elems of first line of Final Matrix
	}
	//cout << endl;*/

	free(pha);		// Free Matrix A allocated Memory
	free(phb);		// Free Matrix B allocated Memory
	free(phc);		// Free Matrix C allocated Memory
}

void OnMultLine_OMP(int m_ar, int m_br, int threads)
{
	double time1, time2;	// counting timers
	
	char st[100];				// Output print buffer
	int i, j, k;				// Matrix iterators

	double *pha, *phb, *phc;	// Matrix's

	omp_set_num_threads(threads);
	
	// -----  Matrix's Inits ---------

	pha = (double *)malloc((m_ar * m_ar) * sizeof(double));		// Matrix A Mem Space Alloc
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));		// Matrix B Mem Space Alloc
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));		// Matrix C Mem Space Alloc

	for(i=0; i<m_ar; i++)					// Init Matrix A
		for(j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1.0;

	for(i=0; i<m_br; i++)					// Init Matrix B
		for(j=0; j<m_br; j++)
			phb[i*m_br + j] = (double)(i+1);

	// -------------------  Matrix Prod (A.B = C)  -------------------------------

	time1 = omp_get_wtime();		// Start Clock counting

	#pragma omp parallel for
	for(i=0; i<m_ar; i++) {
		for(j=0; j<m_br; j++) {
			for(k=0; k<m_ar; k++)
			{
				phc[i*m_ar+k] += pha[i*m_ar+j] * phb[j*m_br+k];
			}
		}
	}

	time2 = omp_get_wtime();		// Stop Clock counting
	
	// -------------------  Print Results  ---------------------------------------
	
	sprintf(st, "%3.3f\t", (double)(time2 - time1));		// Print elapsed time
	cout << st;

	/*cout << "\tResult matrix: ";// << endl;
	for(i=0; i<1; i++) {
		for(j=0; j<min(10,m_br); j++)
			cout << phc[j] << " ";			// Print at most 10 elems of first line of Final Matrix
	}
	//cout << endl;*/

	free(pha);		// Free Matrix A allocated Memory
	free(phb);		// Free Matrix B allocated Memory
	free(phc);		// Free Matrix C allocated Memory

}

float produtoInterno(float *v1, float *v2, int col)
{
	int i;
	float soma = 0.0;	

	for(i=0; i<col; i++)
		soma += v1[i]*v2[i];
	
	return(soma);
}

void handle_error (int retval)
{
	printf("PAPI error %d: %s\n", retval, PAPI_strerror(retval));
	exit(1);
}

void init_papi()
{
	int retval = PAPI_library_init(PAPI_VER_CURRENT);
	
	if (retval != PAPI_VER_CURRENT && retval < 0) {
		printf("PAPI library version mismatch!\n");
		exit(1);
	}
	if (retval < 0)
		handle_error(retval);

	std::cout << "PAPI Version Number: MAJOR: " << PAPI_VERSION_MAJOR(retval)
			<< " MINOR: " << PAPI_VERSION_MINOR(retval)
			<< " REVISION: " << PAPI_VERSION_REVISION(retval) << "\n";
}

void printMenu()
{
	cout << endl << "1. Multiplication Single thread" << endl;
	cout << "2. Multiplication Multi thread (OpenMP)" << endl;
	cout << "3. Multiplication V2 Single thread" << endl;
	cout << "4. Multiplication V2 Multi thread (OpenMP)" << endl << endl;
	cout << "Selection?: ";
}


int main (int argc, char *argv[])
{
	char c;						// ?
	int nt = 1;					// ?
	int lin, col;				// Matrix sizes
	int op;						// Matrix operation type
	int threadsCount;			// Number of working threads
	
	int EventSet = PAPI_NULL;	// PAPI func arg (ref)
	long long values[2];		// L1 & L2 DCM
	int ret;					// PAPI func return val

	// ------  Some Infos  ------
	int nthreads = omp_get_max_threads();
	int ncpus = omp_get_num_procs();
	cout << nthreads << " Thread(s) available(s)." << endl;
	cout << ncpus << " CPU(s) available(s)." << endl;
	
	// ------  Start PAPI  ------
	init_papi();

	ret = PAPI_create_eventset(&EventSet);
	if (ret != PAPI_OK) cout << "ERRO: create eventset" << endl;

	ret = PAPI_add_event(EventSet,PAPI_L1_DCM);					// Capture L1 DCM
	if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_DCM" << endl;

	ret = PAPI_add_event(EventSet,PAPI_L2_DCM);					// Capture L2 DCM
	if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_DCM" << endl;

	/*
	op = 1;
	do {
		cout << endl << "1. Multiplication" << endl;
		cout << "2. Line Multiplication" << endl;
		cout << "Selection?: ";
		cin >>op;
		if (op == 0)
			break;
		printf("Dimensions: lins cols ? ");
   		cin >> lin >> col;

		// ------  Start counting  ------
		ret = PAPI_start(EventSet);
		if (ret != PAPI_OK) cout << "ERRO: Start PAPI" << endl;

		switch (op){
			case 1: 
				OnMult(lin, col);
				break;
			case 2:
				OnMultLine(lin, col);
				break;
		}

		// ------  Print PAPI Results  ------
		ret = PAPI_stop(EventSet, values);
		if (ret != PAPI_OK)
			cout << "ERRO: Stop PAPI" << endl;
		printf("L1 DCM: %lld \n",values[0]);
		printf("L2 DCM: %lld \n",values[1]);

		// ------  Reset PAPI Results  ------
		ret = PAPI_reset( EventSet );
		if ( ret != PAPI_OK )
			std::cout << "FAIL reset" << endl;

	} while (op != 0); */

	int matDimension;			// Matrix Dimension (line & column)
	int matDimInc = 400;		// Matrix Dimension increment

	do {
		printMenu();
		scanf("%d", &op);

		if (op == 0) break;

		switch (op) {
			case 1:
				cout << endl << "Dimension\t Time(s)\t L1_DCM\t L2_DCM\n";
				for (matDimension = 600; matDimension <= 3000; matDimension += matDimInc)
				{
					// ------  Start counting  ------
					ret = PAPI_start(EventSet);
						if (ret != PAPI_OK) cout << "ERRO: Start PAPI" << endl;

					cout << matDimension << "\t";

					OnMult(matDimension, matDimension);

					// ------  Print PAPI Results  ------
					ret = PAPI_stop(EventSet, values);
					if (ret != PAPI_OK)
						cout << "ERRO: Stop PAPI" << endl;
					printf("%lld\t", values[0]);		// L1 DCM:
					printf("%lld\n", values[1]);		// L2 DCM:

					// ------  Reset PAPI Results  ------
					ret = PAPI_reset( EventSet );
					if ( ret != PAPI_OK )
						std::cout << "FAIL reset" << endl;
				}
				break;
			case 2:
				cout << "How many working threads?: ";
				scanf("%d", &threadsCount);
				if(threadsCount < 1)
					threadsCount = 1;
				else if(threadsCount > nthreads)
					threadsCount = nthreads;
				cout << "Working threads: " << threadsCount << endl;
				cout << endl << "Dimension\t Time(s)\t L1_DCM\t L2_DCM\n";

				for (matDimension = 600; matDimension <= 3000; matDimension += matDimInc)
				{
					// ------  Start counting  ------
					ret = PAPI_start(EventSet);
						if (ret != PAPI_OK) cout << "ERRO: Start PAPI" << endl;

					cout << matDimension << "\t";

					OnMult_OMP(matDimension, matDimension, threadsCount);
					
					// ------  Print PAPI Results  ------
					ret = PAPI_stop(EventSet, values);
					if (ret != PAPI_OK)
						cout << "ERRO: Stop PAPI" << endl;
					printf("%lld\t", values[0]);		// L1 DCM:
					printf("%lld\n", values[1]);		// L2 DCM:

					// ------  Reset PAPI Results  ------
					ret = PAPI_reset( EventSet );
					if ( ret != PAPI_OK )
						std::cout << "FAIL reset" << endl;
				}
				break;
			case 3:
				cout << endl << "Dimension\t Time(s)\t L1_DCM\t L2_DCM\n";
				for (matDimension = 600; matDimension <= 3000; matDimension += matDimInc)
				{
					// ------  Start counting  ------
					ret = PAPI_start(EventSet);
						if (ret != PAPI_OK) cout << "ERRO: Start PAPI" << endl;

					cout << matDimension << "\t";

					OnMultLine(matDimension, matDimension);

					// ------  Print PAPI Results  ------
					ret = PAPI_stop(EventSet, values);
					if (ret != PAPI_OK)
						cout << "ERRO: Stop PAPI" << endl;
					printf("%lld\t", values[0]);		// L1 DCM:
					printf("%lld\n", values[1]);		// L2 DCM:

					// ------  Reset PAPI Results  ------
					ret = PAPI_reset( EventSet );
					if ( ret != PAPI_OK )
						std::cout << "FAIL reset" << endl;
				}
				break;
			case 4:
				cout << "How many working threads?: ";
				scanf("%d", &threadsCount);
				if(threadsCount < 1)
					threadsCount = 1;
				else if(threadsCount > nthreads)
					threadsCount = nthreads;
				cout << "Working threads: " << threadsCount << endl;
				cout << endl << "Dimension\t Time(s)\t L1_DCM\t L2_DCM\n";

				for (matDimension = 600; matDimension <= 3000; matDimension += matDimInc)
				{
					// ------  Start counting  ------
					ret = PAPI_start(EventSet);
						if (ret != PAPI_OK) cout << "ERRO: Start PAPI" << endl;

					cout << matDimension << "\t";

					OnMultLine_OMP(matDimension, matDimension, threadsCount);
					
					// ------  Print PAPI Results  ------
					ret = PAPI_stop(EventSet, values);
					if (ret != PAPI_OK)
						cout << "ERRO: Stop PAPI" << endl;
					printf("%lld\t", values[0]);		// L1 DCM:
					printf("%lld\n", values[1]);		// L2 DCM:

					// ------  Reset PAPI Results  ------
					ret = PAPI_reset( EventSet );
					if ( ret != PAPI_OK )
						std::cout << "FAIL reset" << endl;
				}
				break;
		}

	} while (op != 0);

	// ---------  Stop PAPI  --------
	ret = PAPI_remove_event( EventSet, PAPI_L1_DCM );
	if ( ret != PAPI_OK )
		std::cout << "FAIL remove event" << endl; 

	ret = PAPI_remove_event( EventSet, PAPI_L2_DCM );
	if ( ret != PAPI_OK )
		std::cout << "FAIL remove event" << endl; 

	ret = PAPI_destroy_eventset( &EventSet );
	if ( ret != PAPI_OK )
		std::cout << "FAIL destroy" << endl;

}