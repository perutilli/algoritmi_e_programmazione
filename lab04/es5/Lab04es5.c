#pragma warning (disable:4996)

// sorting fatto anche se vettore già presente e merge sort in realtà non è stabile

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_L 30
#define NUM_COMANDI 7
#define NOME_FILE "corse.txt"
#define MAX_RIGHE 1000

typedef struct {
	int codice_tratta, ritardo, data_num;
	char partenza[MAX_L], destinazione[MAX_L], data[MAX_L], ora_partenza[MAX_L], ora_arrivo[MAX_L];
}LogLine;

typedef enum { r_print, r_data, r_codice, r_partenza, r_arrivo, r_ricerca, r_fine } Comando;
const char comandi[NUM_COMANDI][MAX_L] = { "printLog", "ordinaData", "ordinaCodice", "ordinaPartenza", "ordinaArrivo", "ricercaPartenza", "fine" };

int compareData(LogLine l1, LogLine l2);
int compareTratta(LogLine l1, LogLine l2);
int compareStazionePartenza(LogLine l1, LogLine l2);
int compareStazioneArrivo(LogLine l1, LogLine l2);
int compare(int chiave, LogLine l1, LogLine l2);

LogLine* ricercaDicotomica(LogLine* logs[MAX_RIGHE], int n_righe, char* nome_partenza);
LogLine* ricercaDicotomicaR(LogLine* logs[MAX_RIGHE], int l, int r, char* nome_partenza);
LogLine* ricercaLineare(LogLine logs[MAX_RIGHE], int n_righe, char* nome_partenza);

int leggiComando(char com[MAX_L]);
int eseguiComando(LogLine logs[MAX_RIGHE], LogLine * logs_data[MAX_RIGHE], LogLine * logs_codice[MAX_RIGHE], LogLine * logs_partenza[MAX_RIGHE], LogLine * logs_arrivo[MAX_RIGHE], int n_righe, int comando);
int normalizzaData(char data[MAX_L]);
void printLogLine(LogLine log);
void printLog(LogLine* logs[MAX_RIGHE], int n_righe);

void sort(LogLine* logs[MAX_RIGHE], LogLine* aux[MAX_RIGHE], int n_righe, int chiave);
void sortR(LogLine* logs[MAX_RIGHE], LogLine* aux[MAX_RIGHE], int l, int r, int chiave);
void Merge(LogLine* logs[MAX_RIGHE], LogLine* aux[MAX_RIGHE], int l, int q, int r, int chiave);


int main() {
	char com[MAX_L];
	FILE* input;
	int n_righe;
	LogLine logs[MAX_RIGHE];
	LogLine* logs_data[MAX_RIGHE], * logs_codice[MAX_RIGHE], *logs_partenza[MAX_RIGHE], * logs_arrivo[MAX_RIGHE];

	input = fopen(NOME_FILE, "r");
	fscanf(input, "%d", &n_righe);
	for (int i = 0; i < n_righe; i++) {
		fscanf(input, "%d %s %s %s %s %s %d", &logs[i].codice_tratta, logs[i].partenza, logs[i].destinazione, logs[i].data, logs[i].ora_partenza, logs[i].ora_arrivo, &logs[i].ritardo);
		logs[i].data_num = normalizzaData(logs[i].data);
	}
	fclose(input);

	for (int i = 0; i < n_righe; i++) {
		logs_data[i] = logs_codice[i] = logs_partenza[i] = logs_arrivo[i] = &logs[i];
	}
	printf("Comandi disponibili: printLog, ordinaData, ordinaCodice, ordinaPartenza, ordinaArrivo, ricercaPartenza, fine\n");
	printf("inserisci comando: ");
	scanf("%s", com);

	while (eseguiComando(logs, logs_data, logs_codice, logs_partenza, logs_arrivo, n_righe, leggiComando(com)) != r_fine) {
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

int eseguiComando(LogLine logs[MAX_RIGHE], LogLine * logs_data[MAX_RIGHE], LogLine * logs_codice[MAX_RIGHE], LogLine * logs_partenza[MAX_RIGHE], LogLine * logs_arrivo[MAX_RIGHE], int n_righe, int comando) {
	LogLine* aux[MAX_RIGHE];
	static int ordinato = 0;
	static int ordinamento = 0;
	switch (comando) {
	case r_print:
		switch (ordinamento)
		{
		case 0:
			printLog(logs_data, n_righe);
			break;
		case r_data:
			printLog(logs_data, n_righe);
			break;
		case r_codice:
			printLog(logs_codice, n_righe);
			break;
		case r_partenza:
			printLog(logs_partenza, n_righe);
			break;
		case r_arrivo:
			printLog(logs_arrivo, n_righe);
			break;
		}
		break;
	case r_data:
		sort(logs_data, aux, n_righe, r_data);
		ordinamento = r_data;
		break;
	case r_codice:
		sort(logs_codice, aux, n_righe, r_codice);
		ordinamento = r_codice;
		break;
	case r_partenza:
		sort(logs_partenza, aux, n_righe, r_partenza);
		ordinamento = r_partenza;
		ordinato = 1;
		break;
	case r_arrivo:
		sort(logs_arrivo, aux, n_righe, r_arrivo);
		ordinamento = r_arrivo;
		break;
	case r_ricerca:
	{
		char partenza[MAX_L];
		scanf("%s", partenza);
		if (ordinato) {
			LogLine* el = ricercaDicotomica(logs_partenza, n_righe, partenza);
			if (el != NULL) {
				printLogLine(*el);
			}
			else {
				printf("Stazione partenza non presente\n");
			}

		}
		else {
			LogLine* el = ricercaLineare(logs, n_righe, partenza);
			if (el != NULL) {
				printLogLine(*el);
			}
			else {
				printf("Stazione partenza non presente\n");
			}
		}
		break;
	}
	}
	return comando;
}

int normalizzaData(char data[MAX_L]) {
	int data_norm = (data[6] - '0') * 10000000 + (data[7] - '0') * 1000000 + (data[8] - '0') * 100000 + (data[9] - '0') * 10000 + (data[3] - '0') * 1000 + (data[4] - '0') * 100 + (data[0] - '0') * 10 + data[1] - '0';

	return data_norm;
}

void printLogLine(LogLine log) {
	printf("%d %s %s %s %s %s %d\n", log.codice_tratta, log.partenza, log.destinazione, log.data, log.ora_partenza, log.ora_arrivo, log.ritardo);
}

void printLog(LogLine* logs[MAX_RIGHE], int n_righe) {
	for (int i = 0; i < n_righe; i++) {
		printLogLine(*logs[i]);
	}
}

int compareData(LogLine l1, LogLine l2) {
	if ((l1.data_num - l2.data_num) != 0) {
		return (l1.data_num - l2.data_num);
	}
	return(strcmp(l1.ora_partenza, l2.ora_partenza));
}

int compareTratta(LogLine l1, LogLine l2) {
	return (l1.codice_tratta - l2.codice_tratta);
}

int compareStazionePartenza(LogLine l1, LogLine l2) {
	return (strcmp(l1.partenza, l2.partenza));
}

int compareStazioneArrivo(LogLine l1, LogLine l2) {
	return (strcmp(l1.destinazione, l2.destinazione));
}

int compare(int chiave, LogLine l1, LogLine l2) {
	switch (chiave)
	{
	case r_data:
		return compareData(l1, l2);
		break;
	case r_codice:
		return compareTratta(l1, l2);
		break;
	case r_partenza:
		return compareStazionePartenza(l1, l2);
		break;
	case r_arrivo:
		return compareStazioneArrivo(l1, l2);
		break;
	}

	exit(1);
}

LogLine* ricercaDicotomica(LogLine* logs[MAX_RIGHE], int n_righe, char* nome_partenza) {
	int l = 0, r = n_righe - 1;
	return ricercaDicotomicaR(logs, l, r, nome_partenza);
}

LogLine* ricercaDicotomicaR(LogLine* logs[MAX_RIGHE], int l, int r, char* nome_partenza) {
	int q = (l + r) / 2;
	if (l > r) {
		return NULL;
	}
	switch (strncmp(logs[q]->partenza, nome_partenza, strlen(nome_partenza))) {
	case 0:
		return logs[q];
	case -1:
		return ricercaDicotomicaR(logs, q + 1, r, nome_partenza);
	case 1:
		return ricercaDicotomicaR(logs, l, q - 1, nome_partenza);
	}


}

LogLine* ricercaLineare(LogLine logs[MAX_RIGHE], int n_righe, char* nome_partenza) {
	for (int i = 0; i < n_righe; i++) {
		if (strncmp(logs[i].partenza, nome_partenza, strlen(nome_partenza)) == 0) {
			return &(logs[i]);
		}
	}
	return NULL;
}

void sort(LogLine *logs[MAX_RIGHE], LogLine* aux[MAX_RIGHE], int n_righe, int chiave) {
	int l = 0, r = n_righe - 1;
	sortR(logs, aux, l, r, chiave);
}

void sortR(LogLine *logs[MAX_RIGHE], LogLine *aux[MAX_RIGHE], int l, int r, int chiave) {
	int q = (l + r) / 2;
	if (r <= l)
		return;
	sortR(logs, aux, l, q, chiave);
	sortR(logs, aux, q + 1, r, chiave);
	Merge(logs, aux, l, q, r, chiave);
}

void Merge(LogLine* logs[MAX_RIGHE], LogLine* aux[MAX_RIGHE], int l, int q, int r, int chiave) {
	int i = l, j = q + 1, k;
	for (k = l; k <= r; k++) {
		if (i > q) {
			aux[k] = logs[j++];
		}
		else if (j > r) {
			aux[k] = logs[i++];
		}
		else if (compare(chiave, *(logs[i]), *(logs[j])) <= 0) {
			aux[k] = logs[i++];
		}
		else {
			aux[k] = logs[j++];
		}
	}
	for (k = l; k <= r; k++) {
		logs[k] = aux[k];
	}
}