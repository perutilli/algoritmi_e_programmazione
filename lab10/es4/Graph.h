#pragma warning (disable:4996)

#ifndef GRAFO_H
#define GRAFO_H

#define MAXC 30
#include "ST.h"

typedef struct {
	int v, w, wt;
} Edge;

typedef	struct graph *Graph;

Graph	GRAPHinit(int V);
void	GRAPHfree(Graph G);
Graph	GRAPHload(FILE* fin);
void	GRAPHinsertE(Graph G, int id1, int id2, int wt);
void	GRAPHstore(Graph G, FILE* fout);
void	GRAPHcreateListAdj(Graph G);
int		GRAPHsottoGrafoCompletoMadj(Graph G, char* name1, char* name2, char* name3);
int		GRAPHsottoGrafoCompletoLadj(Graph G, char* name1, char* name2, char* name3);

#endif
