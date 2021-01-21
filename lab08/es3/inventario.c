#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include "inventario.h"

stat_t newStat(int hp, int mp, int atk, int def, int mag, int spr) {
	stat_t stat;
	stat.hp = hp;
	stat.mp = mp;
	stat.atk = atk;
	stat.def = def;
	stat.mag = mag;
	stat.spr = spr;
	return stat;
}

void printStat(stat_t stat) {
	printf("%d %d %d %d %d %d", stat.hp, stat.mp, stat.atk, stat.def, stat.mag, stat.spr);
}

stat_t sommaStat(stat_t stat1, stat_t stat2) {
	stat_t res;
	res.hp = stat1.hp + stat2.hp;
	res.mp = stat1.mp + stat2.mp;
	res.atk = stat1.atk + stat2.atk;
	res.def = stat1.def + stat2.def;
	res.mag = stat1.mag + stat2.mag;
	res.spr = stat1.spr + stat2.spr;
	return res;
}

tabInv_t initTabInv(size_t n_obj) {
	tabInv_t tab;
	tab.maxInv = n_obj;
	tab.vettInv = malloc(tab.maxInv * sizeof(*(tab.vettInv)));
	tab.nInv = 0;
	return tab;
}

void inserisciInv(tabInv_t* tabInv, inv_t oggetto) {
	tabInv->vettInv[tabInv->nInv] = oggetto;
	tabInv->nInv += 1;
}

void stampaTabInv(tabInv_t tab) {
	for (int i = 0; i < tab.nInv; i++) {
		stampaOggettoInv(tab.vettInv[i]);
		printf("\n");
	}
}

inv_t newOggettoInv(int id, char* nome, char* tipo, stat_t stat) {
	inv_t obj;
	obj.id = id;
	obj.nome = strdup(nome);
	obj.tipo = strdup(tipo);
	obj.stat = stat;
	return obj;
}

void stampaOggettoInv(inv_t obj) {
	printf("%d %s %s ", obj.id, obj.nome, obj.tipo);
	printStat(obj.stat);
}

void acquisisciInv(FILE* f_inv, tabInv_t* tabInv) {
	char nome[LEN_MAX], tipo[LEN_MAX];
	stat_t stat;
	inv_t item;
	int hp, mp, atk, def, mag, spr, n_obj;
	fscanf(f_inv, "%d", &n_obj);
	*tabInv = initTabInv(n_obj);
	for (int i = 0; i < n_obj; i++) {
		fscanf(f_inv, "%s %s %d %d %d %d %d %d", nome, tipo, &hp, &mp, &atk, &def, &mag, &spr);
		stat = newStat(hp, mp, atk, def, mag, spr);
		item = newOggettoInv(i, nome, tipo, stat);
		inserisciInv(tabInv, item);
	}
}