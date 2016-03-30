#ifndef MATRIXOPS_H
#define MATRIXOPS_H

class MatrixOps {
private:
	clock_t time1, time2;		// counting timers
	double time3, time4;		// counting timers for OMP version
	
	char st[100];				// Output print buffer
	double temp;				// Matrix prod temp (Not OMP version)
	int i, j, k;				// Matrix iterators

	double *pha, *phb, *phc;	// Matrix's
	
	
	void printElapsedTime(int omp);							// Display elapsed time for the matrix multiplication
	void printMatrix(double *matrix, int dim);				// Display a matrix content
	void printStats(double *matrix, int dim, int omp);		// Display Matrix Dim, elapsed time & PAPI results in one line
	float produtoInterno(float *v1, float *v2, int col);	// Produto Interno
	void allocAllMatrix(int m_ar, int m_br);				// Allocate memory and define initial values of matrixs
	void freeAllMatrix();									// Release allocated memory of matrixs

public:
	MatrixOps();
	~MatrixOps();

	// --------- Matrix Multiplication (A.B = C) routines -----------------
	void OnMult(int m_ar, int m_br);						// Matrix Line by Col multiplication
	void OnMult_OMP(int m_ar, int m_br, int threads);		// Matrix Line by col multiplication (Parallel Computing Version)
	void OnMultLine(int m_ar, int m_br);					// Matrix Line multiplication
	void OnMultLine_OMP(int m_ar, int m_br, int threads);	// Matrix Line multiplication (Parallel Computing Version)
};

#endif