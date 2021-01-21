#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>

#define MAX_R 50
#define MAX_C 50
#define NOME_FILE "input.txt"

typedef struct {
	int base, altezza;
	int riga, colonna;
	int area;
}Rett;

void copyRett(Rett *dest, Rett *orig);

int main() {
	FILE* input;
	int nr, nc;
	int matrice[MAX_R][MAX_C];
	Rett max_base = { 0, 0, 0, 0, 0 }, max_altezza = { 0, 0, 0, 0, 0 }, max_area = { 0, 0, 0, 0, 0 }, temp;
	const Rett zero = { 0, 0, 0, 0, 0 };

	input = fopen(NOME_FILE, "r");
	fscanf(input, "%d %d", &nr, &nc);
	for (int i = 0; i < nr; i++) {
		for (int j = 0; j < nc; j++) {
			fscanf(input, "%d", &matrice[i][j]);
		}
	}
	fclose(input);

	for (int i = 0; i < nr; i++) {

		copyRett(&temp, &zero);

		for (int j = 0; j < nc; j++) {

			switch (matrice[i][j]) {
			case 0:

				temp.area = temp.base * temp.altezza;

				if (temp.altezza > max_altezza.altezza) {
					copyRett(&max_altezza, &temp);
				}
				if (temp.base > max_base.base) {
					copyRett(&max_base, &temp);
				}
				if (temp.area > max_area.area) {
					copyRett(&max_area, &temp);
				}

				copyRett(&temp, &zero);
				break;

			case 1:

				if (temp.area == 0) {
					temp.riga = i;
					temp.colonna = j;

					int k = 0;
					while (matrice[i + k][j] == 1) {
						temp.altezza++;
						k++;
					}
				}

				temp.base++;
				temp.area = 1;
				
				break;
			}
		}

		temp.area = temp.base * temp.altezza;

		if (temp.altezza > max_altezza.altezza) {
			copyRett(&max_altezza, &temp);
		}
		if (temp.base > max_base.base) {
			copyRett(&max_base, &temp);
		}
		if (temp.area > max_area.area) {
			copyRett(&max_area, &temp);
		}
	}

	printf("Max Base: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", max_base.riga, max_base.colonna, max_base.base, max_base.altezza, max_base.area);
	printf("Max Altezza: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", max_altezza.riga, max_altezza.colonna, max_altezza.base, max_altezza.altezza, max_altezza.area);
	printf("Max Area: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", max_area.riga, max_area.colonna, max_area.base, max_area.altezza, max_area.area);
}

void copyRett(Rett *dest, Rett *orig) {
	dest->colonna = orig->colonna;
	dest->riga = orig->riga;
	dest->base = orig->base;
	dest->altezza = orig->altezza;
	dest->area = orig->area;
}
