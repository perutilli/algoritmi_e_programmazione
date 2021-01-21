#ifndef INV_H
#define INV_H

#define LEN_MAX 51
#define LEN_CODICE 7

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

//fun stat
stat_t newStat(int hp, int mp, int atk, int def, int mag, int spr);
void printStat(stat_t stat);
stat_t sommaStat(stat_t stat1, stat_t stat2);
//fun tabInv
tabInv_t initTabInv(size_t n_obj);
void inserisciInv(tabInv_t* tabInv, inv_t oggetto);
void stampaTabInv(tabInv_t tab);
void acquisisciInv(FILE* f_inv, tabInv_t* tabInv);
//fun inv_t
inv_t newOggettoInv(int id, char* nome, char* tipo, stat_t stat);
void stampaOggettoInv(inv_t obj);

#endif
