#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "invArray.h"

struct invArray_s {
	inv_t* vettInv;
	int nInv, maxInv;
};

// non è chiaro se il file inventario è come nel lab scorso e contiene il numero di oggetti sulla prima riga, assunto di sì
invArray_t invArray_init() {
	invArray_t inv_arr = malloc(sizeof(*inv_arr));
	inv_arr->maxInv = 0;
	inv_arr->nInv = 0;
	return inv_arr;
}

void invArray_free(invArray_t invArray) {
	free(invArray->vettInv);
	free(invArray);
}

void invArray_read(FILE* fp, invArray_t invArray) {
	int n_el;
	fscanf(fp, "%d", &n_el);
	invArray->vettInv = malloc(n_el * sizeof(inv_t));
	invArray->maxInv = n_el;
	for (int i = 0; i < n_el; i++) {
		inv_read(fp, invArray->vettInv + i);
	}
	invArray->nInv = n_el;
}

void invArray_print(FILE* fp, invArray_t invArray) {
	for (int i = 0; i < invArray->nInv; i++) {
		invArray_printByIndex(fp, invArray, i);
	}
}

void invArray_printByIndex(FILE* fp, invArray_t invArray, int index) {
	inv_t* invp = invArray_getByIndex(invArray, index);
	if (invp == NULL) {
		return;
	}
	inv_print(fp, invp);
	fprintf(fp, "\n");
}

inv_t* invArray_getByIndex(invArray_t invArray, int index) {
	if (index >= invArray->nInv) {
		return NULL;
	}
	return (invArray->vettInv + index);
}

int invArray_searchByName(invArray_t invArray, char* name) {
	for (int i = 0; i < invArray->nInv; i++) {
		if (strcmp(name, invArray_getByIndex(invArray, i)->nome) == 0) {
			return i;
		}
	}
	return -1;
}