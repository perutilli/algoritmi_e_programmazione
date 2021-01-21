#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>

#define MAX_R 50
#define MAX_C 50
#define NOME_FILE "input.txt"

typedef struct {
	int base, altezza;
	int riga, colonna;
}Rett;

void leggiMatrice(int mat[][MAX_C], int n_max_righe, int* num_righe, int* num_colonne);
int riconosciRegione(int mat[][MAX_C], int nr, int nc, int r, int c, int* base, int* altezza);
void init_rett(Rett* r, int base, int altezza, int riga, int colonna);

int main() {
	int nr, nc, b, h;
	int matrice[MAX_R][MAX_C];
	Rett max_base = { 0, 0, 0, 0 }, max_altezza = { 0, 0, 0, 0 }, max_area = { 0, 0, 0, 0 };

	leggiMatrice(matrice, MAX_R, &nr, &nc);

	for (int r = 0; r < nr; r++) {
		for (int c = 0; c < nc; c++) {
			if (riconosciRegione(matrice, nr, nc, r, c, &b, &h)) {
				if (b > max_base.base) {
					init_rett(&max_base, b, h, r, c);
				}
				if (h > max_altezza.altezza) {
					init_rett(&max_altezza, b, h, r, c);
				}
				if ((b * h) > (max_area.base * max_area.altezza)) {
					init_rett(&max_area, b, h, r, c);
				}
			}
		}
	}

	printf("Max Base: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", max_base.riga, max_base.colonna, max_base.base, max_base.altezza, (max_base.base * max_base.altezza));
	printf("Max Altezza: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", max_altezza.riga, max_altezza.colonna, max_altezza.base, max_altezza.altezza, (max_altezza.base * max_altezza.altezza));
	printf("Max Area: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", max_area.riga, max_area.colonna, max_area.base, max_area.altezza, (max_area.base * max_area.altezza));
}

int riconosciRegione(int mat[][MAX_C], int nr, int nc, int r, int c, int* base, int* altezza)
{
	int est_sup, i;
	*base = *altezza = 0;
	est_sup = (((r - 1) < 0) || (mat[r - 1][c] == 0)) && (((c - 1) < 0) || (mat[r][c - 1] == 0));
	if (est_sup) {
		i = 0;
		while ((r + i < nr) && mat[r + i][c] == 1) {
			(*altezza)++;
			i++;
		}
		i = 0;
		while ((c + i < nc) && mat[r][c + i] == 1) {
			(*base)++;
			i++;
		}

	}
	return est_sup;
}

void init_rett(Rett* r, int base, int altezza, int riga, int colonna) {
	r->base = base;
	r->altezza = altezza;
	r->riga = riga;
	r->colonna = colonna;
}

void leggiMatrice(int mat[][MAX_C], int n_max_righe, int* num_righe, int* num_colonne) {
	FILE* input;
	input = fopen(NOME_FILE, "r");
	fscanf(input, "%d %d", num_righe, num_colonne);
	if (*num_righe < n_max_righe && *num_colonne < MAX_C) {
		for (int i = 0; i < *num_righe; i++) {
			for (int j = 0; j < *num_colonne; j++) {
				fscanf(input, "%d", &mat[i][j]);
			}
		}
	}
	fclose(input);
}
