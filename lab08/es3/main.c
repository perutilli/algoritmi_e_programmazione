#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include "personaggio.h"
#include "inventario.h"

#define NOME_FILE_PG "pg.txt"
#define NOME_FILE_INV "inventario.txt"

const char comandi[][LEN_MAX] = { "aggiungi personaggio", "elimina personaggio", "aggiungi equipaggiamento", "rimuovi equipaggiamento", "calcola statistiche", "fine" };
typedef enum { r_aggiungi_pg, r_elimina_pg, r_aggiungi_equip, r_rimuovi_equip, r_calcola_stat, r_fine } Comando;

int main() {
	FILE* f_pg, * f_inv;
	tabPg_t listPg = initTabPg();
	tabInv_t tab_inv;
	Comando com;

	f_pg = fopen(NOME_FILE_PG, "r");
	aquisisciPgFile(f_pg, &listPg);
	fclose(f_pg);

	f_inv = fopen(NOME_FILE_INV, "r");
	acquisisciInv(f_inv, &tab_inv);
	fclose(f_inv);

	printf("Comandi: \n");
	for (int i = 0; i <= r_fine; i++) {
		printf("%d %s\n", i, comandi[i]);
	}
	printf("Inserire numero comando: ");
	scanf("%d", &com);
	while (com != r_fine) {
		switch (com)
		{
		case r_aggiungi_pg:
			printf("Inserire personaggio: ");
			pgRead(stdin, &listPg);
			break;
		case r_elimina_pg:
		{
			char codice[LEN_CODICE];
			stampaTabPg(listPg);
			printf("Inserire codice personaggio da eliminare: ");
			scanf("%s", codice);
			eliminaNodo(codice, &listPg);
			break;
		}
		case r_aggiungi_equip:
		{
			char codice[LEN_CODICE];
			linkPg pg;
			int id;
			stampaTabPg(listPg);
			printf("Selezionare personaggio: ");
			scanf("%s", codice);
			pg = ricercaPg(codice, &listPg);
			stampaTabInv(tab_inv);
			printf("Selezionare oggetto: ");
			scanf("%d", &id);
			if (aggiungiObjInv(pg, &(tab_inv.vettInv[id])) == -1) {
				printf("Inventario pieno\n");
			}
			break;
		}
		case r_rimuovi_equip:
		{
			char codice[LEN_CODICE];
			linkPg pg;
			int id;
			stampaTabPg(listPg);
			printf("Selezionare personaggio: ");
			scanf("%s", codice);
			pg = ricercaPg(codice, &listPg);
			printf("Selezionare oggetto: ");
			scanf("%d", &id);
			if (rimuoviObjInv(pg, &(tab_inv.vettInv[id])) == -1) {
				printf("Oggetto non in inventario\n");
			}
			break;
		}
		case r_calcola_stat:
		{
			char codice[LEN_CODICE];
			linkPg pg;
			stat_t stat;
			stampaTabPg(listPg);
			printf("Selezionare personaggio: ");
			scanf("%s", codice);
			pg = ricercaPg(codice, &listPg);
			stat = calcolaStat(pg->val);
			printStat(stat);
			printf("\n");

		}
		}


		printf("Inserire numero comando: ");
		scanf("%d", &com);
	}
}