#pragma warning (disable:4996)

#include <stdlib.h>
#include <stdio.h>

#define MAXC 100
#define MAX_EL 5
#define FILE_NAME "elementi.txt"
#define DD 10000

typedef enum {trans, indietro, avanti} Tipo;
typedef enum {spalle, fronte} Direzione;
typedef enum {false, true} bool;

typedef struct {
	char nome[MAXC];
	Tipo tipo;
	Direzione entrata, uscita;
	bool can_first, only_last;
	float value;
	int difficoltà;
} Elemento;

typedef struct {
	Elemento elementi[MAX_EL];
	int difficoltà;
	int n_elementi;
	bool avanti, indietro;
} Diagonale;

void genDiag(Diagonale* diagonali, Elemento* elementi, int n_elementi);
void genDiagR(int pos, Diagonale* diag, Diagonale* diagonali, Elemento* elementi, int n_elementi, int* n_diag, int* max_diag, int max_elementi);
bool check(Diagonale* diag, int max_el);
void DiagonalePutElemento(Diagonale* diag, int pos, Elemento elemento);
Diagonale DiagonaleInit();
void DiagonaleClear(Diagonale diag);
void DiagonalePrint(Diagonale diag);
void ElementoPrint(Elemento el);

int main() {
	FILE* fin;
	Elemento* elementi;
	int n_elementi;
	Diagonale* diagonali = NULL;

	fin = fopen(FILE_NAME, "r");
	fscanf(fin, "%d", &n_elementi);
	elementi = malloc(n_elementi * sizeof(*elementi));
	for (int i = 0; i < n_elementi; i++) {
		fscanf(fin, "%s %d %d %d %d %d %f %d", 
			elementi[i].nome, &elementi[i].tipo, &elementi[i].entrata, &elementi[i].uscita, &elementi[i].can_first, &elementi[i].only_last, &elementi[i].value, &elementi[i].difficoltà);
	}
	fclose(fin);

	genDiag(diagonali, elementi, n_elementi);
}

void genDiag(Diagonale* diagonali, Elemento* elementi, int n_elementi) {
	int n_diag = 0, max_diag = 1, pos = 0;
	Diagonale diag = DiagonaleInit();
	diagonali = malloc(max_diag * sizeof(*diagonali));
	for (int i = 1; i <= MAX_EL; i++) {
		genDiagR(pos, &diag, diagonali, elementi, n_elementi, &n_diag, &max_diag, i);
	}
	for (int i = 0; i < n_diag; i++) {
		DiagonalePrint(diagonali[i]);
	}
}

void genDiagR(int pos, Diagonale* diag, Diagonale* diagonali, Elemento* elementi, int n_elementi, int* n_diag, int* max_diag, int max_elementi) {

	if (pos >= max_elementi) {
		if (*n_diag >= *max_diag) {
			*max_diag *= 2;
			diagonali = realloc(diagonali, (*max_diag) * sizeof(Diagonale));
		}
		diagonali[*n_diag] = *diag;
		(*n_diag)++;
		return;
	}

	for (int i = 0; i < n_elementi; i++) {
		DiagonalePutElemento(diag, pos, elementi[i]);
		if (check(diag, max_elementi)) {
			genDiagR(pos + 1, diag, diagonali, elementi, n_elementi, n_diag, max_diag, max_elementi);
		}
	}
}

Diagonale DiagonaleInit() {
	Diagonale diag;
	diag.difficoltà = 0;
	diag.avanti = false;
	diag.indietro = false;
	diag.n_elementi = 0;
	return diag;
}

void DiagonaleClear(Diagonale diag) {
	free(diag.elementi);
}

void DiagonalePutElemento(Diagonale* diag, int pos, Elemento elemento) {
	diag->elementi[pos] = elemento;
	diag->n_elementi = pos + 1;
	diag->difficoltà += elemento.difficoltà;
	diag->avanti = diag->avanti || (elemento.tipo == avanti);
	diag->indietro = diag->indietro || (elemento.tipo == indietro);
}

bool check(Diagonale* diag, int max_el) {
	bool valid;
	int n_el = diag->n_elementi;
	Elemento last = diag->elementi[n_el - 1], one_to_last;

	if (n_el == 1) {
		if ((last.can_first == false) || (last.entrata != fronte)) {
			return false;
		}
	}
	else {
		one_to_last = diag->elementi[n_el - 2];
		if ((one_to_last.uscita != one_to_last.entrata) || (diag->difficoltà > DD)) {
			return false;
		}
		if (diag->n_elementi != max_el) {
			if (last.only_last) {
				return false;
			}
		}
	}
	return true;
}

void DiagonalePrint(Diagonale diag) {
	for (int i = 0; i < diag.n_elementi; i++) {
		ElementoPrint(diag.elementi[i]);
	}
	printf("\n");
}

void ElementoPrint(Elemento el) {
	printf("%s ", el.nome);
}