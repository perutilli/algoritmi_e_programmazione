#pragma warning (disable:4996)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ST.h"

struct symboltable { 
	char** a; 
	int maxN; 
	int N; 
};

ST STinit(int maxN) {
	ST st = malloc(sizeof(*st));
	st->a = malloc(maxN * sizeof(*(st->a)));
	st->maxN = maxN;
	st->N = 0;
	return st;
}

void STfree(ST st) {
	for (int i = 0; i < st->N; i++) {
		free((st->a)[i]);
	}
	free(st->a);
	free(st);
}

int STsize(ST st) {
	return st->N;
}

void STinsert(ST st, char* str, int i) {
	if (i > st->maxN) {
		return;
	}
	(st->a)[i] = strdup(str);
	(st->N)++;
}

int STsearch(ST st, char* str) {
	for (int i = 0; i < st->N; i++) {
		if (strcmp(st->a[i], str) == 0) {
			return i;
		}
	}
	return -1;
}

char* STsearchByIndex(ST st, int i) {
	if (i >= st->N) {
		return NULL;
	}
	return (st->a)[i];
}