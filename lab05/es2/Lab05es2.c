#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>

// non libero la matrice

#define NOME_FILE "matrice.txt"

int** malloc2dR(int nr, int nc);
void separa(int** mat, int nr, int nc, int** nere, int** bianche, int* l_nere, int* l_bianche);

int main() {
	int** mat, nr, nc, *nere, *bianche, l_nere, l_bianche;
	FILE* input;

	input = fopen(NOME_FILE, "r");
	fscanf(input, "%d %d", &nr, &nc);
	mat = malloc2dR(nr, nc);
	for (int i = 0; i < nr; i++) {
		for (int j = 0; j < nc; j++) {
			fscanf(input, "%d", &mat[i][j]);
		}
	}
	fclose(input);

	separa(mat, nr, nc, &nere, &bianche, &l_nere, &l_bianche);

	printf("Contenuti caselle nere: ");
	for (int i = 0; i < l_nere; i++) {
		printf("%d ", nere[i]);
	}
	printf("\n");

	printf("Contenuti caselle bianche: ");
	for (int i = 0; i < l_bianche; i++) {
		printf("%d ", bianche[i]);
	}
	printf("\n");

	free(nere);
	free(bianche);
}

int** malloc2dR(int nr, int nc) {
	int** mat;
	mat = (int**)malloc(nr * sizeof(int*));
	for (int i = 0; i < nc; i++) {
		mat[i] = (int*)malloc(nc * sizeof(int));
	}
	return mat;
}

void separa(int** mat, int nr, int nc, int** nere, int** bianche, int *l_nere, int *l_bianche) {
	int dim = nr * nc;
	if (dim % 2 == 0) {
		*l_nere = *l_bianche = dim / 2;
	}
	else {
		*l_nere = (dim + 1) / 2;
		*l_bianche = (dim - 1) / 2;
	}
	*nere = (int*)malloc((*l_nere) * sizeof(int));
	*bianche = (int*)malloc((*l_bianche) * sizeof(int));

	for (int i = 0; i < dim; i++) {
		if (i % 2 == 0) {
			(*nere)[i / 2] = mat[i / nc][i % nc];
		}
		else {
			(*bianche)[(i - 1) / 2] = mat[i / nc][i % nc];
		}
	}
}