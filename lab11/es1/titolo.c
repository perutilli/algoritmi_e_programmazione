#pragma warning (disable:4996)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BST.h"
#include "titolo.h"

struct titolo {
	char* nome;
	BST quot_bst;
};

Titolo TITOLOinit(char* nome) {
	Titolo titolo = malloc(sizeof(titolo));
	titolo->nome = strdup(nome);
	titolo->quot_bst = BSTinit();
	return titolo;
}

void TITOLOfree(Titolo titolo) {
	free(titolo->nome);
	BSTfree(titolo->quot_bst);
	free(titolo);
}

char* TITOLOgetName(Titolo titolo) {
	return titolo->nome;
}

Titolo TITOLOsetNull() {
	return TITOLOinit("\0");
}

void TITOLOupdateQuot(Titolo t, Data data, float val, int num) {
	BSTupdateQuot(t->quot_bst, data, val, num);
}

int TITOLOisNull(Titolo titolo) {
	return (strcmp(titolo->nome, "\0") == 0);
}

Quot TITOLOsearchQuot(Titolo titolo, Data data) {
	return (BSTsearch(titolo->quot_bst, data));
}

void TITOLOquotMaxMin(Titolo titolo, Data data_min, Data data_max) {
	Quot q_min = QUOTsetNull();
	Quot q_max = QUOTsetNull();
	BSTquotMinMax(titolo->quot_bst, data_min, data_max, &q_min, &q_max);
	QUOTstore(q_min, stdout);
	QUOTstore(q_max, stdout);
}

void TITOLObalanceBst(Titolo titolo) {
	BSTbalance(titolo->quot_bst);
}
