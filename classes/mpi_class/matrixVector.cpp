#include <stdio.h>
#include "mpi.h"

float produtoInterno(float *v1, float *v2, int col) {
	int i;
	float soma = 0.0;

	for (i = 0; i < col; i++)
		soma += v1[i] * v2[i];

	return (soma);

}

void preencheMatriz(float *v, int nlin, int ncol, int tlin) {
	int i, j;

	// matriz identidade
	for (i = 0; i < nlin; i++) {
		for (j = 0; j < ncol; j++)
			v[i * ncol + j] = 0.0;
		v[i * ncol + i] = 1.0;
	}

	for (i = nlin; i < tlin; i++) {
		for (j = 0; j < ncol; j++)
			v[i * ncol + j] = 0.0;
	}

}

int main(int argc, char **argv) {
	int rank, size, erro;
	float *v1, *v2, *sv1, *my_r, *r;
	int k, nlinhas, my_lin, maisum;
	int lin, col;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		printf("Dimensoes: lins cols ? ");
		scanf("%d %d", &lin, &col);
		maisum = (lin % size) == 0 ? 0 : 1;
		nlinhas = ((lin / size) + maisum) * size;
		v1 = new float[nlinhas * col];
		v2 = new float[col];
		r = new float[nlinhas];             // vector resultado
		preencheMatriz(v1, lin, col, nlinhas);
		// preenche vector
		for (k = 0; k < col; k++)
			v2[k] = k;
	}

	// broadcast de lin, col a todos os processos
	//
	//

	// reservar espaco para os dados, o ultimo processador podera ficar com zeros no fim
	maisum = (lin % size) == 0 ? 0 : 1;
	my_lin = (lin / size) + maisum;
	sv1 = new float[my_lin * col];

	if (rank > 0)
		v2 = new float[col];

	// distribui a matriz
	//erro =
	printf("processo %d recebeu %d elementos, erro=%d\n", rank, my_lin * col,
			erro);

	// distribui vector
	//erro =
	printf("processo %d recebeu vector de %d elementos, erro=%d\n", rank, col,
			erro);

	// calcula produto matrix-vector
	my_r = new float[my_lin];

	for (k = 0; k < my_lin; k++)
		my_r[k] = produtoInterno(&sv1[k * col], v2, col);

	// processo 0 obtem resultado
	//erro =

	if (rank == 0) {
		printf("Vector Resultado\n");
		for (k = 0; k < lin; k++)
			printf("%.1f ", r[k]);
		printf("\n");
	}

	MPI_Finalize();

	delete[] v1;
	delete[] v2;
	delete[] sv1;
	delete[] my_r;
	if (r != NULL)
		delete[] r;

	return 0;
}
