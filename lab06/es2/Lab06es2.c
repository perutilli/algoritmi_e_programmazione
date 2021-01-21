#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARATTERI 50
#define LEN_DATA 11
#define LEN_CODICE 5

typedef enum { r_ins_tastiera, r_ins_file, r_ricerca, r_canc_codice, r_canc_date, r_stampa_file, r_fine } Comando;
const char comandi[r_fine + 1][MAX_CARATTERI] = { "inserimento_tastiera", "inserimento_file", "ricerca", "cancellazione_per_codice", "cancellazione_tra_date", "stampa_su_file", "fine" };

typedef struct {
	char codice[LEN_CODICE + 1], nome[MAX_CARATTERI + 1], cognome[MAX_CARATTERI + 1], data_nascita[LEN_DATA + 1], via[MAX_CARATTERI + 1], citta[MAX_CARATTERI + 1];
	int cap, data_num;
}Item;

typedef struct node* link;

struct node {
	Item val;
	link next;
};

int leggiComando(char* com);
void switchComando(int comando, link* h);
Item voidItem();
int dataToDatanum(char* data);

//funzioni lista
link newNode(Item val, link next);
link inserisciNodo(link h, Item val);
Item estraiNodoCodice(link* h, char* k);
Item estraiNodoData(link* h, int data1, int data2);
void printList(link h);

void printItem(Item val);

int main() {
	link head = NULL;
	int comando;
	char com[MAX_CARATTERI + 1];

	printf("Inserire un comando: ");
	for (int i = 0; i < r_fine; i++) {
		printf("%s, ", comandi[i]);
	}
	printf("%s\n", comandi[r_fine]);
	printf("(scrivere solo comando, argomenti richiesti successivamente)\n");

	printf("Inserisci comando: ");
	scanf("%s", com);

	while ((comando = leggiComando(com)) != r_fine) {
		if (comando == -1)
			printf("Comando non valido\n");
		else
			switchComando(comando, &head);
		printf("Inserisci comando: ");
		scanf("%s", com);
	}
}

int leggiComando(char* com) {

	int n_comando = -1;
	for (int i = 0; i <= r_fine; i++) {
		if (strcmp(comandi[i], com) == 0) {
			n_comando = i;
		}
	}
	return n_comando;
}

void switchComando(int comando, link* h) {
	Item nuovo;
	int giorno, mese, anno;

	switch (comando)
	{
	case r_ins_tastiera:
		printf("Inserisci item (codice, nome, cognome, data nascita, via, citta' cap): \n");
		scanf("%s %s %s %s %s %s %d", nuovo.codice, nuovo.nome, nuovo.cognome, nuovo.data_nascita, nuovo.via, nuovo.citta, &nuovo.cap);
		nuovo.data_num = dataToDatanum(nuovo.data_nascita);
		*h = inserisciNodo(*h, nuovo);
		break;
	case r_ins_file:
	{
		char nome_file[MAX_CARATTERI + 1];
		printf("Inserisci nome file: ");
		scanf("%s", nome_file);
		FILE* in = fopen(nome_file, "r");
		while (fscanf(in, "%s %s %s %s %s %s %d", nuovo.codice, nuovo.nome, nuovo.cognome, nuovo.data_nascita, nuovo.via, nuovo.citta, &nuovo.cap) != EOF) {
			nuovo.data_num = dataToDatanum(nuovo.data_nascita);
			*h = inserisciNodo(*h, nuovo);
		}
		break;
	}
	case r_ricerca:
	{
		link t;
		char codice[LEN_CODICE + 1];
		printf("Inserisci codice: ");
		scanf("%s", codice);
		for (t = *h; t != NULL; t = t->next) {
			if (strcmp((t->val).codice, codice) == 0) {
				printItem(t->val);
				printf("\n");
				break;
			}
		}
		break;
	}
	case r_canc_codice:
	{
		char codice[LEN_CODICE + 1];
		scanf("%s", codice);
		printItem(estraiNodoCodice(h, codice));
		break;
	}
	case r_canc_date:
	{
		char data1_str[LEN_DATA], data2_str[LEN_DATA];
		int data1, data2;
		Item it;
		printf("Inserisci date: ");
		scanf("%s %s", data1_str, data2_str);
		data1 = dataToDatanum(data1_str);
		data2 = dataToDatanum(data2_str);

		it = estraiNodoData(h, data1, data2);
		while (it.cap != 0) {
			printItem(it);
			it = estraiNodoData(h, data1, data2);
		}
		break;

	}
	case r_stampa_file:
	{
		link node = *h;
		char nome_file_out[MAX_CARATTERI + 1];
		FILE* f_out;
		printf("Inserisci nome file: ");
		scanf("%s", nome_file_out);
		f_out = fopen(nome_file_out, "w");
		for (; node != NULL; node = node->next) {
			fprintf(f_out, "%s %s %s %s %s %s %d\n", (node->val).codice, (node->val).nome, (node->val).cognome, (node->val).data_nascita, (node->val).via, (node->val).citta, (node->val).cap);
		}
		fclose(f_out);
		break;
	}
	}
	return;
}

Item voidItem() {
	Item val = { "", "", "", "", "", "", 0, 0 };
	return val;
}

int dataToDatanum(char* data){
	int giorno, mese, anno;
	int data_num;
	sscanf(data, "%d/%d/%d", &giorno, &mese, &anno);
	data_num = giorno + mese * 100 + anno * 10000;
}

link newNode(Item val, link next) {
	link x = malloc(sizeof(*x));
	if (x == NULL) {
		return NULL;
	}
	x->val = val;
	x->next = next;
	return x;
}

link inserisciNodo(link h, Item val) {
	link x, p;
	int k = val.data_num;
	if (h == NULL || ((h->val).data_num < k))
		return newNode(val, h);
	for (x = h->next, p = h;
		x != NULL && (k < (x->val).data_num);
		p = x, x = x->next);
	p->next = newNode(val, x);
	return h;
}

Item estraiNodoCodice(link* h, char* k) {
	link x, p, t, head = *h;
	Item r_value = voidItem();
	if (strcmp((head->val).codice, k) == 0) {
		r_value = head->val;
		t = *h;
		*h = head->next;
		free(t);
	}
	else {
		for (x = head, p = NULL; (x->next) != NULL; p = x, x = x->next) {
			if (strcmp((x->val).codice, k) == 0) {
				t = x;
				p->next = x->next;
				r_value = t->val;
				free(t);
				break;
			}
		}
	}
	return r_value;
}

Item estraiNodoData(link* h, int data1, int data2) {
	link x, p, t, head = *h;
	Item r_value = voidItem();
	if (head->val.data_num >= data1 && head->val.data_num <= data2) {
		r_value = head->val;
		t = *h;
		*h = head->next;
		free(t);
	}
	else {
		for (x = head, p = NULL;
			(x->next) != NULL && x->val.data_num >= data2;
			p = x, x = x->next);
		if (x->val.data_num >= data1) {
			t = x;
			p->next = x->next;
			r_value = t->val;
			free(t);
		}
	}
	return r_value;
}

void printList(link h) {
	for (; h != NULL; h = h->next) {
		printItem(h->val);
	}
}

void printItem(Item val) {
	printf("%s %s %s %s %s %s %d\n", val.codice, val.nome, val.cognome, val.data_nascita, val.via, val.citta, val.cap);
}