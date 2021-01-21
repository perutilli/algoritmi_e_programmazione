#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define NOME_FILE "grafo2.txt"

int main() {
	Graph G;
	FILE* fin;
	Edge** edge_dag;

	fin = fopen(NOME_FILE, "r");
	G = GRAPHload(fin);
	fclose(fin);
	removeToCreateDAG(G);
}