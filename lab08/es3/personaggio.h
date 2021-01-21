#ifndef PERS_H
#define PERS_H

#define MAX_EQUIP 8

#include "inventario.h"

typedef struct nodoPg_t* linkPg;

typedef struct {
	int in_uso;
	inv_t* vettEq[MAX_EQUIP];
} tabEquip_t;

typedef struct {
	char* codice, * nome, * classe;
	tabEquip_t equip;
	stat_t stat;
} pg_t;

struct nodoPg_t {
	pg_t val;
	linkPg next;
};

typedef struct {
	linkPg headPg, tailPg;
	int nPg;
} tabPg_t;


//fun tabella
tabPg_t initTabPg();
void stampaTabPg(tabPg_t tab);
void inserisciNodo(tabPg_t* tab, pg_t val);
//fun nodo
linkPg newNode(pg_t val, linkPg next);
linkPg eliminaNodo(char* codice, tabPg_t* listPg);
linkPg ricercaPg(char* codice, tabPg_t* listPg);
//fun pg
pg_t* newPg(char* codice, char* nome, char* classe, stat_t stat);
pg_t copiaPg(pg_t pg);
void printPg(pg_t pg);
void liberaPg(pg_t* pg);
int aggiungiObjInv(linkPg nodo, inv_t* obj);
int rimuoviObjInv(linkPg nodo, inv_t* obj);
stat_t calcolaStat(pg_t pg);
//fun tabEquip
tabEquip_t tabEquigInit();
int pgRead(FILE* fp, tabPg_t* listPg);
void aquisisciPgFile(FILE* fp, tabPg_t* listPg);

#endif