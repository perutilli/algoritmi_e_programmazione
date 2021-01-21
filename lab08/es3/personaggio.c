#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include "personaggio.h"

tabPg_t initTabPg() {
	tabPg_t listPg;
	listPg.headPg = listPg.tailPg = NULL;
	listPg.nPg = 0;
	return listPg;
}

void stampaTabPg(tabPg_t tab) {
	linkPg l;
	for (l = tab.headPg; l != NULL; l = l->next) {
		printPg(l->val);
		printf("\n");
	}
}

linkPg newNode(pg_t val, linkPg next) {
	linkPg node = malloc(sizeof(*node));
	node->val = copiaPg(val);
	node->next = next;
	return node;
}

linkPg eliminaNodo(char* codice, tabPg_t* listPg) {
	linkPg head = listPg->headPg, p;
	if (strcmp(head->val.codice, codice) == 0) {
		listPg->headPg = head->next;
		free(head);
		return;
	}
	for (p = NULL; head != NULL; p = head, head = head->next) {
		if (strcmp(head->val.codice, codice) == 0) {
			p->next = head->next;
			free(head);
			return;
		}
	}
}

linkPg ricercaPg(char* codice, tabPg_t* listPg) {
	linkPg x, p;
	for (x = listPg->headPg, p = NULL;
		x != NULL; p = x, x = x->next) {
		if (strcmp(x->val.codice, codice) == 0) {
			return x;
		}
	}
}

void inserisciNodo(tabPg_t* tab, pg_t val) {
	linkPg nodo = newNode(val, NULL);
	tab->nPg += 1;
	if (tab->headPg == NULL) {
		tab->headPg = tab->tailPg = nodo;
	}
	else {
		tab->tailPg->next = nodo;
		tab->tailPg = nodo;
	}
}

pg_t* newPg(char* codice, char* nome, char* classe, stat_t stat) {
	pg_t* p_pg = malloc(sizeof(*p_pg));
	p_pg->codice = strdup(codice);
	p_pg->nome = strdup(nome);
	p_pg->classe = strdup(classe);
	p_pg->equip = tabEquigInit();
	p_pg->stat = stat;
	return p_pg;
}

pg_t copiaPg(pg_t pg) {
	pg_t* p_pg = newPg(pg.codice, pg.nome, pg.classe, pg.stat);
	return *p_pg;
}

void printPg(pg_t pg) {
	printf("%s %s %s ", pg.codice, pg.nome, pg.classe);
	printStat(pg.stat);
}


void liberaPg(pg_t* pg) {
	free(pg->codice);
	free(pg->nome);
	free(pg->classe);
	free(pg);
}

int aggiungiObjInv(linkPg nodo, inv_t* obj) {
	if (nodo->val.equip.in_uso > MAX_EQUIP) {
		return -1;
	}
	nodo->val.equip.vettEq[nodo->val.equip.in_uso] = obj;
	nodo->val.equip.in_uso++;

}

int rimuoviObjInv(linkPg nodo, inv_t* obj) {
	int inUso = nodo->val.equip.in_uso;

	for (int i = 0; i < inUso; i++) {
		if (nodo->val.equip.vettEq[i] == obj) {
			nodo->val.equip.vettEq[i] = nodo->val.equip.vettEq[inUso - 1];
			nodo->val.equip.vettEq[inUso - 1] = NULL;
			nodo->val.equip.in_uso--;
			return 0;
		}
	}

	return -1;
}

stat_t calcolaStat(pg_t pg) {
	stat_t stat = pg.stat;
	for (int i = 0; i < pg.equip.in_uso; i++) {
		stat = sommaStat(stat, pg.equip.vettEq[i]->stat);
	}
	stat.hp = max(stat.hp, 1);
	stat.mp = max(stat.mp, 1);
	stat.atk = max(stat.atk, 1);
	stat.def = max(stat.def, 1);
	stat.mag = max(stat.mag, 1);
	stat.spr = max(stat.spr, 1);
	return stat;
}

tabEquip_t tabEquigInit() {
	tabEquip_t tab;
	tab.in_uso = 0;
	return tab;
}

int pgRead(FILE* fp, tabPg_t* listPg) {
	char codice[LEN_CODICE], nome[LEN_MAX], classe[LEN_MAX];
	stat_t stat;
	pg_t* p_pg;
	int hp, mp, atk, def, mag, spr;
	if (fscanf(fp, "%s %s %s %d %d %d %d %d %d", codice, nome, classe, &hp, &mp, &atk, &def, &mag, &spr) == EOF) {
		return EOF;
	}
	stat = newStat(hp, mp, atk, def, mag, spr);
	p_pg = newPg(codice, nome, classe, stat);
	inserisciNodo(listPg, *p_pg);
	liberaPg(p_pg);
}

void aquisisciPgFile(FILE* fp, tabPg_t* listPg) {
	while (pgRead(fp, listPg) != EOF);
}