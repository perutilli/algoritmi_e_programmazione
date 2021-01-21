#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_CODICE 7
#define LEN_MAX 51
#define NOME_FILE_PG "pg.txt"
#define NOME_FILE_INV "inventario.txt"
#define MAX_EQUIP 8

const char comandi[][LEN_MAX] = {"aggiungi personaggio", "elimina personaggio", "aggiungi equipaggiamento", "rimuovi equipaggiamento", "calcola statistiche", "fine"};
typedef enum { r_aggiungi_pg, r_elimina_pg, r_aggiungi_equip, r_rimuovi_equip, r_calcola_stat, r_fine } Comando;

typedef struct nodoPg_t* linkPg;

typedef struct {
	int hp, mp, atk, def, mag, spr;
} stat_t;

typedef struct {
	int id;
	char* nome, * tipo;
	stat_t stat;
} inv_t;

typedef struct {
	inv_t* vettInv;
	int nInv, maxInv;
} tabInv_t;

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
void liberaList(tabPg_t list);
//fun nodo
linkPg newNode(pg_t val, linkPg next);
void eliminaNodo(char* codice, tabPg_t* listPg);
linkPg ricercaPg(char* codice, tabPg_t* listPg);
void liberaNodo(linkPg nodo);
//fun stat
stat_t newStat(int hp, int mp, int atk, int def, int mag, int spr);
void printStat(stat_t stat);
stat_t sommaStat(stat_t stat1, stat_t stat2);
//fun pg
pg_t* newPg(char* codice, char* nome, char* classe, stat_t stat);
pg_t copiaPg(pg_t pg);
void printPg(pg_t pg);
void liberaPg(pg_t* pg);
int aggiungiObjInv(linkPg nodo, inv_t* obj);
int rimuoviObjInv(linkPg nodo, inv_t* obj);
stat_t calcolaStat(pg_t pg);
//fun tabInv
tabInv_t initTabInv(size_t n_obj);
void inserisciInv(tabInv_t* tabInv, inv_t oggetto);
void stampaTabInv(tabInv_t tab);
void liberaTabInv(tabInv_t tab);
//fun inv_t
inv_t newOggettoInv(int id, char* nome, char* tipo, stat_t stat);
void stampaOggettoInv(inv_t obj);
//fun tabEquip
tabEquip_t tabEquigInit();
//fun main
void acquisisciPg(FILE* f_pg, tabPg_t* listPg);
void acquisisciInv(FILE* f_inv, tabInv_t* tabInv);

int main() {
	FILE* f_pg, * f_inv;
	tabPg_t listPg = initTabPg();
	tabInv_t tab_inv;
	Comando com;

	f_pg = fopen(NOME_FILE_PG, "r");
	acquisisciPg(f_pg, &listPg);
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
		{
			char codice[LEN_CODICE], nome[LEN_MAX], classe[LEN_MAX];
			stat_t stat;
			pg_t* p_pg;
			int hp, mp, atk, def, mag, spr;
			printf("Inserire personaggio: ");
			scanf("%s %s %s %d %d %d %d %d %d", codice, nome, classe, &hp, &mp, &atk, &def, &mag, &spr);
			stat = newStat(hp, mp, atk, def, mag, spr);
			p_pg = newPg(codice, nome, classe, stat);
			inserisciNodo(&listPg, *p_pg);
			liberaPg(p_pg);
			break;
		}
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
			printPg(pg->val);
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

	liberaList(listPg);
	liberaTabInv(tab_inv);

}

void acquisisciPg(FILE* f_pg, tabPg_t* listPg) {
	char codice[LEN_CODICE], nome[LEN_MAX], classe[LEN_MAX];
	stat_t stat;
	pg_t* p_pg;
	int hp, mp, atk, def, mag, spr;
	while (fscanf(f_pg, "%s %s %s %d %d %d %d %d %d", codice, nome, classe, &hp, &mp, &atk, &def, &mag, &spr) != EOF) {
		stat = newStat(hp, mp, atk, def, mag, spr);
		p_pg = newPg(codice, nome, classe, stat);
		inserisciNodo(listPg, *p_pg);
		liberaPg(p_pg);
	}
	
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

tabPg_t initTabPg() {
	tabPg_t listPg;
	listPg.headPg = listPg.tailPg = NULL;
	listPg.nPg = 0;
	return listPg;
}

tabInv_t initTabInv(size_t n_obj) {
	tabInv_t tab;
	tab.maxInv = n_obj;
	tab.vettInv = malloc(tab.maxInv * sizeof(*(tab.vettInv)));
	tab.nInv = 0;
	return tab;
}

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

pg_t* newPg(char* codice, char* nome, char* classe, stat_t stat) {
	pg_t* p_pg = malloc(sizeof(*p_pg));
	p_pg->codice = strdup(codice);
	p_pg->nome = strdup(nome);
	p_pg->classe = strdup(classe);
	p_pg->equip = tabEquigInit();
	p_pg->stat = stat;
	return p_pg;
}

void inserisciInv(tabInv_t* tabInv, inv_t oggetto) {
	tabInv->vettInv[tabInv->nInv] = oggetto;
	tabInv->nInv += 1;
}

linkPg newNode(pg_t val, linkPg next) {
	linkPg node = malloc(sizeof(*node));
	node->val = copiaPg(val);
	node->next = next;
	return node;
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

void liberaPg(pg_t* pg) {
	free(pg->codice);
	free(pg->nome);
	free(pg->classe);
	free(pg);
}

pg_t copiaPg(pg_t pg) {
	pg_t* p_pg = newPg(pg.codice, pg.nome, pg.classe, pg.stat);
	return *p_pg;
}

void stampaTabPg(tabPg_t tab) {
	linkPg l;
	for (l = tab.headPg; l != NULL; l = l->next) {
		printPg(l->val);
		printf("\n");
	}
}

void printPg(pg_t pg) {
	printf("%s %s %s ", pg.codice, pg.nome, pg.classe);
	printStat(pg.stat);
	printf("\n");
}

void printStat(stat_t stat) {
	printf("%d %d %d %d %d %d", stat.hp, stat.mp, stat.atk, stat.def, stat.mag, stat.spr);
}

inv_t newOggettoInv(int id, char* nome, char* tipo, stat_t stat) {
	inv_t obj;
	obj.id = id;
	obj.nome = strdup(nome);
	obj.tipo = strdup(tipo);
	obj.stat = stat;
	return obj;
}

void stampaTabInv(tabInv_t tab) {
	for (int i = 0; i < tab.nInv; i++) {
		stampaOggettoInv(tab.vettInv[i]);
		printf("\n");
	}
}

void stampaOggettoInv(inv_t obj) {
	printf("%d %s %s ", obj.id, obj.nome, obj.tipo);
	printStat(obj.stat);
}

tabEquip_t tabEquigInit() {
	tabEquip_t tab;
	tab.in_uso = 0;
	return tab;
}

void eliminaNodo(char* codice, tabPg_t* listPg) {
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

linkPg ricercaPg(char* codice, tabPg_t* listPg) {
	linkPg x, p;
	for (x = listPg->headPg, p = NULL;
		x != NULL; p = x, x = x->next) {
		if (strcmp(x->val.codice, codice) == 0) {
			return x;
		}
	}
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

void liberaNodo(linkPg nodo) {
	liberaPg(&(nodo->val));
}

void liberaList(tabPg_t list) {
	linkPg p, t;
	for (p = list.headPg; p != NULL; p = t) {
		t = p->next;
		liberaNodo(p);
	}
}

void liberaTabInv(tabInv_t tab) {
	free(tab.vettInv);
}