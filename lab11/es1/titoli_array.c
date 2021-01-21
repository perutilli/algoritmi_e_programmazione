#include <stdlib.h>
#include <string.h>
#include "titolo.h"
#include "titoli_array.h"


struct arr_titoli {
	Titolo* titoli;
	int N;
	int maxN;
};

Titoli_array TITOLIarrayInit(int n_titoli) {
	Titoli_array vett = malloc(sizeof(*vett));
	vett->titoli = malloc(n_titoli * sizeof(*(vett->titoli)));
	vett->N = 0;
	vett->maxN = n_titoli;
	return vett;
}

void TITOLIarrayFree(Titoli_array vett) {
	free(vett->titoli);
	free(vett);
}

void TITOLIarrayInsert(Titoli_array vett, Titolo titolo) {
	if (vett->N >= vett->maxN) {
		vett->titoli = realloc(vett->titoli, vett->maxN * 2 * sizeof(*(vett->titoli)));
		vett->maxN *= 2;
	}
	vett->titoli[vett->N] = titolo;
	(vett->N)++;
}

Titolo TITOLIarraySearch(Titoli_array vett, char* nome) {
	for (int i = 0; i < vett->N; i++) {
		if (strcmp(TITOLOgetName((vett->titoli)[i]), nome) == 0) {
			return (vett->titoli)[i];
		}
	}
	return TITOLOsetNull();
}