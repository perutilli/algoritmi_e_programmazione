#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "quot.h"
#include "titolo.h"
#include "titoli_array.h"

#define MAXC 20
#define L_DATA 11
#define L_ORA 6
#define N_SCELTE0 3
#define N_SCELTE1 5

const char* menu0[N_SCELTE0] = {
	"Uscita",
	"Acquisisci da file", 
	"Selezione titolo"
};

const char* menu1[N_SCELTE1] = {
	"Torna a menu precedente",
	"Ricerca quotazione per data",
	"Ricerca quotazione min e max tra date",
	"Ricerca quotazione min e max", 
	"Bilanciamento albero"	
};

void printMenu(char** comandi, int n_comandi);
void acquisisciFile(FILE* fin, Titoli_array titoli);

int main() {
	FILE* fin;
	int num, fine = 0, com;
	float val;
	int n_titoli, n_transaz;
	char nome[MAXC], data[L_DATA], data1[L_DATA], ora[L_ORA], nome_file[MAXC];
	Titoli_array titoli = TITOLIarrayInit(1);
	Titolo t;

	do {
		printMenu(menu0, N_SCELTE0);
		printf("Inserire comando: ");
		scanf("%d", &com);
		switch (com)
		{
		case 0:
			fine = 1;
			break;
		case 1:
			printf("Inserisci nome file: ");
			scanf("%s", nome_file);
			fin = fopen(nome_file, "r");
			acquisisciFile(fin, titoli);
			fclose(fin);
			break;
		case 2: 
		{
			printf("Inserire nome titolo: ");
			scanf("%s", nome);
			t = TITOLIarraySearch(titoli, nome);
			if (TITOLOisNull(t)) {
				printf("Titolo non presente\n");
			} 
			else {
				do {
					printMenu(menu1, N_SCELTE1);
					scanf("%d", &com);
					switch (com)
					{
					case 0:
						break;
					case 1:
						printf("Inserisci data: ");
						scanf("%s", data);
						QUOTstore(TITOLOsearchQuot(t, DATAnew(data)), stdout);
						break;
					case 2:
						printf("Inserisci date: ");
						scanf("%s %s", data, data1);
						TITOLOquotMaxMin(t, DATAnew(data), DATAnew(data1));
						break;
					case 3:
						TITOLOquotMaxMin(t, DATAsetNull(), DATAsetNull());
						break;
					case 4:
						TITOLObalanceBst(t);
					}

				} while (com != 0);
			}
			break;
		}
		}


	} while (!fine);

	TITOLIarrayFree(titoli);
}

void printMenu(char** comandi, int n_comandi) {
	for (int i = 0; i < n_comandi; i++) {
		printf("\t%d %s\n", i, comandi[i]);
	}
}

void acquisisciFile(FILE* fin, Titoli_array titoli) {
	char nome[MAXC], ora[L_ORA], data[L_DATA];
	int num, n_transaz, n_titoli;
	float val;
	Titolo t;

	fscanf(fin, "%d", &n_titoli);
	for (int i = 0; i < n_titoli; i++) {
		fscanf(fin, "%s %d", nome, &n_transaz);
		TITOLIarrayInsert(titoli, TITOLOinit(nome));
		t = TITOLIarraySearch(titoli, nome);
		for (int i = 0; i < n_transaz; i++) {
			fscanf(fin, "%s %s %f %d", data, ora, &val, &num);
			TITOLOupdateQuot(t, DATAnew(data), val, num);
		}
	}
}