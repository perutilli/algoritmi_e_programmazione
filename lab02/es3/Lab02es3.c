#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MAX_SEQ 20
#define L_MAX_SEQ 5
#define L_MAX_RIGA 200
#define L_MAX_PAROLA 25
#define NOME_SEQ "sequenze.txt"
#define NOME_TEXT "testo.txt"
#define MAX_OCC 10

typedef struct {
	char sequenza[L_MAX_SEQ + 1];
	char parole[MAX_OCC][L_MAX_PAROLA + 1];
	int posizione[MAX_OCC], n_occ;
}Sequenza;

int compareStrings(char str1[L_MAX_PAROLA + 1], char str2[L_MAX_PAROLA + 1]);

int main() {
	FILE* sequenze, * testo;
	int n_seq, pos;
	char riga[L_MAX_RIGA + 1];
	char *parola;
	Sequenza el_sequenze[N_MAX_SEQ];

	sequenze = fopen(NOME_SEQ, "r");
	fscanf(sequenze, "%d", &n_seq);
	for (int i = 0; i < n_seq; i++) {
		fscanf(sequenze, "%s", el_sequenze[i].sequenza);
		el_sequenze[i].n_occ = 0;
	}
	fclose(sequenze);

	testo = fopen(NOME_TEXT, "r");
	pos = 0;
	while (fgets(riga, L_MAX_RIGA + 1, testo) != NULL) {
		parola = strtok(riga, " ,.-\'");
		while (parola != NULL)
		{
			pos++;
			for (int i = 0; i < n_seq; i++) {
				if (compareStrings(parola, el_sequenze[i].sequenza) && el_sequenze[i].n_occ < 10) {
					strcpy(el_sequenze[i].parole[el_sequenze[i].n_occ], parola);
					el_sequenze[i].posizione[el_sequenze[i].n_occ] = pos;
					el_sequenze[i].n_occ++;
				}
			}
			parola = strtok(NULL, " ,.-\'");
		}
	}
	fclose(testo);

	for (int i = 0; i < n_seq; i++) {
		if (el_sequenze[i].n_occ == 0) {
			continue;
		}
		printf("La sequenza %s e\' contenuta in ", el_sequenze[i].sequenza);
		for (int j = 0; j < el_sequenze[i].n_occ; j++) {
			printf("%s(parola in posizione %d nel testo), ", el_sequenze[i].parole[j], el_sequenze[i].posizione[j]);
		}
		printf("\n\n");
	}

}


int compareStrings(char str1[L_MAX_PAROLA + 1], char str2[L_MAX_PAROLA + 1]) {
	char tmp1[L_MAX_PAROLA + 1], tmp2[L_MAX_PAROLA + 1];
	for (int i = 0; i < strlen(str1); i++) {
		tmp1[i] = toupper(str1[i]);
	}
	tmp1[strlen(str1)] = '\0';
	for (int i = 0; i < strlen(str2); i++) {
		tmp2[i] = toupper(str2[i]);
	}
	tmp2[strlen(str2)] = '\0';

	return (strstr(tmp1, tmp2) != NULL);
}
