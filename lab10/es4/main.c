#pragma warning (disable:4996)

#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"

#define N_SCELTE 5

const char* scelte[] = {
	  "Uscita",
	  "Genera lista adiacenze",
	  "Stampa grafo",
	  "Verifica componente connessa ladj",
	  "Verifica componente connessa madj"
};

void stampaMenu(char* scelte[], int* selezione) {
	int i = 0;
	printf("\nMENU'\n");
	for (i = 0; i < N_SCELTE; i++)
		printf("%2d > %s\n", i, scelte[i]);
	scanf(" %d", selezione);
}

int main(int argc, char** argv) {
	FILE* fin;
	Graph G;
	int fineProgramma = 0, selezione;

	fin = fopen(argv[1], "r");
	G = GRAPHload(fin);
	fclose(fin);

	do {
		stampaMenu(scelte, &selezione);
		switch (selezione) {

		case 0: {
			fineProgramma = 1;
		} break;
		case 1: {
			GRAPHcreateListAdj(G);
		} break;
		case 2: {
			GRAPHstore(G, stdout);
		} break;
		case 3: {
			char nome1[MAXC], nome2[MAXC], nome3[MAXC];
			int connesso;
			printf("Inserire nomi 3 nodi: ");
			scanf("%s %s %s", nome1, nome2, nome3);
			connesso = GRAPHsottoGrafoCompletoLadj(G, nome1, nome2, nome3);
			if (connesso) {
				printf("Componente connessa\n");
			}
			else {
				printf("Componente non connessa\n");
			}
		} break;
		case 4: {
			char nome1[MAXC], nome2[MAXC], nome3[MAXC];
			int connesso;
			printf("Inserire nomi 3 nodi: ");
			scanf("%s %s %s", nome1, nome2, nome3);
			connesso = GRAPHsottoGrafoCompletoMadj(G, nome1, nome2, nome3);
			if (connesso) {
				printf("Componente connessa\n");
			}
			else {
				printf("Componente non connessa\n");
			}
		} break;
		}
	} while (!fineProgramma);




	GRAPHfree(G);
}