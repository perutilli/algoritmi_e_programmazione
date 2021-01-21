#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_L 30
#define NUM_COMANDI 6
#define NOME_FILE "corse.txt"
#define MAX_RIGHE 1000

typedef struct {
	int codice_tratta, ritardo;
	char partenza[MAX_L], destinazione[MAX_L], data[MAX_L], ora_partenza[MAX_L], ora_arrivo[MAX_L];
}LogLine;

typedef enum {r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine} Comando;
//ho cambiato la stringa per il ritardo_tot perchè la strcmp non mi funzionava con l'underscore
const char comandi[NUM_COMANDI][MAX_L] = { "date", "partenza", "capolinea", "ritardo", "ritardotot", "fine" };

int leggiComando(char com[MAX_L]);
int selezioneDati(LogLine logs[MAX_RIGHE], int n_righe, int comando);
void normalizzaData(char data[MAX_L]);
void printLogLine(LogLine log);

int main() {
	char com[MAX_L];
	FILE* input;
	int n_righe;
	LogLine logs[MAX_RIGHE];

	input = fopen(NOME_FILE, "r");
	fscanf(input, "%d", &n_righe);
	for (int i = 0; i < n_righe; i++) {
		fscanf(input, "%d %s %s %s %s %s %d", &logs[i].codice_tratta, logs[i].partenza, logs[i].destinazione, logs[i].data, logs[i].ora_partenza, logs[i].ora_arrivo, &logs[i].ritardo);
		normalizzaData(logs[i].data);
	}
	fclose(input);

	printf("inserisci comando: ");
	scanf("%s", com);

	while (selezioneDati(logs, n_righe, leggiComando(com)) != r_fine) {
		printf("inserisci comando: ");
		scanf("%s", com);
	}
	
}

int leggiComando(char com[MAX_L]) {
	
	int n_comando = -1;
	for (int i = 0; i < NUM_COMANDI; i++) {
		if (strcmp(comandi[i], com) == 0) {
			n_comando = i;
		}
	}
	return n_comando;
}

int selezioneDati(LogLine logs[MAX_RIGHE], int n_righe, int comando) {
	char dato1[MAX_L], dato2[MAX_L];
	int dato3, tot_ritardo;

	switch (comando)
	{
	case r_date:
		scanf("%s %s", dato1, dato2);
		normalizzaData(dato1);
		normalizzaData(dato2);
		for (int i = 0; i < n_righe; i++) {
			if ((strcmp(logs[i].data, dato1) >= 0) && (strcmp(logs[i].data, dato2) <= 0)) {
				printLogLine(logs[i]);
			}
		}
		break;
	case r_partenza:
		scanf("%s", dato1);
		for (int i = 0; i < n_righe; i++) {
			if (strcmp(logs[i].partenza, dato1) == 0) {
				printLogLine(logs[i]);
			}
		}
		break;
	case r_capolinea:
		scanf("%s", dato1);
		for (int i = 0; i < n_righe; i++) {
			if (strcmp(logs[i].destinazione, dato1) == 0) {
				printLogLine(logs[i]);
			}
		}
		break;
	case r_ritardo:
		scanf("%s %s", dato1, dato2);
		normalizzaData(dato1);
		normalizzaData(dato2);
		for (int i = 0; i < n_righe; i++) {
			if ((strcmp(logs[i].data, dato1) >= 0) && (strcmp(logs[i].data, dato2) <= 0) && logs[i].ritardo != 0) {
				printLogLine(logs[i]);
			}
		}
		break;
	case r_ritardo_tot:
		tot_ritardo = 0;
		scanf("%d", &dato3);
		for (int i = 0; i < n_righe; i++) {
			if (logs[i].codice_tratta == dato3) {
				tot_ritardo += logs[i].ritardo;
			}
		}
		printf("Ritardo totale: %d\n", tot_ritardo);
		break;
	case r_fine:
		break;
	default:
		printf("Comando non valido");
		break;
	}

	return comando;
}

void normalizzaData(char data[MAX_L]) {
	char data_norm[MAX_L] = { data[6], data[7], data[8], data[9], data[3], data[4], data[0], data[1], '\0' };

	strcpy(data, data_norm);
}

void printLogLine(LogLine log) {
	printf("%d %s %s %s %s %s %d\n", log.codice_tratta, log.partenza, log.destinazione, log.data, log.ora_partenza, log.ora_arrivo, log.ritardo);
}