#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include "matrixOps.h"
#include "papiData.h"

using namespace std;

MatrixOps::MatrixOps() {}

MatrixOps::~MatrixOps() {
	return;
}

void MatrixOps::printElapsedTime(int omp)
{
	if(omp == 1)
		sprintf(st, "%3.3f;", (double)(time4 - time3));		// Print elapsed time for OMP version
	else
		sprintf(st, "%3.3f;", (double)(time2 - time1) / CLOCKS_PER_SEC);		// Print elapsed time
	cout << st;
}

void MatrixOps::printMatrix(double *matrix, int dim)
{
	/* int i, j;
	cout << "\tResult matrix: ";// << endl;
	for(i=0; i<1; i++) {
		for(j=0; j<min(10, dim); j++)
			cout << matrix[j] << " ";			// Print at most 10 elems of first line of Final Matrix
	}
	//cout << endl;*/
}

void MatrixOps::printStats(double *matrix, int dim, int omp)
{
	cout << dim << ";";
	printElapsedTime(omp);
	printMatrix(matrix, dim);
}

float MatrixOps::produtoInterno(float *v1, float *v2, int col)
{
	int i;
	float soma = 0.0;

	for(i=0; i<col; i++)
		soma += v1[i]*v2[i];

	return(soma);
}

void MatrixOps::allocAllMatrix(int m_ar, int m_br)
{
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
}

void MatrixOps::freeAllMatrix()
{
	free(pha);		// Free Matrix A allocated Memory
	free(phb);		// Free Matrix B allocated Memory
	free(phc);		// Free Matrix C allocated Memory
}

void MatrixOps::OnMult(int m_ar, int m_br)
{
	allocAllMatrix(m_ar, m_br);

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
	printStats(phc, m_br, 0);

	freeAllMatrix();
}

void MatrixOps::OnMult_OMP(int m_ar, int m_br, int threads)
{
	int i, j, k;
	double temp;

	allocAllMatrix(m_ar, m_br);

	omp_set_num_threads(threads);	// Apply working threads

	// -------------------  Matrix Prod (A.B = C)  -------------------------------

	time3 = omp_get_wtime();		// Start Clock counting

	for(i=0; i<m_ar; i++) {
		for(j=0; j<m_br; j++) {
			temp = 0;
			#pragma omp parallel for reduction(+:temp)		// Parallel Computing
			for(k=0; k<m_ar; k++)
			{
				temp += pha[i*m_ar+k] * phb[k*m_br+j];
			}
			phc[i*m_ar+j]=temp;
		}
	}

	time4 = omp_get_wtime();		// Stop Clock counting

	// -------------------  Print Results  ---------------------------------------
	printStats(phc, m_br, 1);

	freeAllMatrix();
}

void MatrixOps::OnMultLine(int m_ar, int m_br)
{
	allocAllMatrix(m_ar, m_br);

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
	printStats(phc, m_br, 0);

	freeAllMatrix();
}

void MatrixOps::OnMultLine_OMP(int m_ar, int m_br, int threads)
{
	int i, j, k;

	allocAllMatrix(m_ar, m_br);

	omp_set_num_threads(threads);	// Apply working threads

	// -------------------  Matrix Prod (A.B = C)  -------------------------------

	time3 = omp_get_wtime();		// Start Clock counting

	#pragma omp parallel for		// Parallel Computing
	for(i=0; i<m_ar; i++) {
		for(j=0; j<m_br; j++) {
			for(k=0; k<m_ar; k++)
			{
				phc[i*m_ar+k] += pha[i*m_ar+j] * phb[j*m_br+k];
			}
		}
	}

	time4 = omp_get_wtime();		// Stop Clock counting

	// -------------------  Print Results  ---------------------------------------
	printStats(phc, m_br, 1);

	freeAllMatrix();
}