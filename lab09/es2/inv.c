#include "inv.h"

void stat_read(FILE* fp, stat_t* statp) {
	fscanf(fp, "%d %d %d %d %d %d", &(statp->hp), &(statp->mp), &(statp->atk), &(statp->def), &(statp->mag), &(statp->spr));
}

void stat_print(FILE* fp, stat_t* statp, int soglia) {
	if (soglia) {
		fprintf(fp, "%d %d %d %d %d %d", max(MIN_STAT, statp->hp), max(MIN_STAT, statp->mp), max(MIN_STAT, statp->atk), max(MIN_STAT, statp->def), max(MIN_STAT, statp->mag), max(MIN_STAT, statp->spr));
	}
	else {
		fprintf(fp, "%d %d %d %d %d %d", statp->hp, statp->mp, statp->atk, statp->def, statp->mag, statp->spr);
	}
}

void inv_read(FILE* fp, inv_t* invp) {
	char nome[LEN], tipo[LEN];
	if (fscanf(fp, "%s %s", nome, tipo) != EOF) {
		strcpy(invp->nome, nome);
		strcpy(invp->tipo, tipo);
		stat_read(fp, &(invp->stat));
	}
}

void inv_print(FILE* fp, inv_t* invp) {
	fprintf(fp, "%s %s ", invp->nome, invp->tipo);
	stat_print(fp, &(invp->stat), 1);
}

stat_t inv_getStat(inv_t* invp) {
	return (invp->stat);
}

stat_t stat_sum(stat_t stat1, stat_t stat2) {
	stat_t stat = {
		stat1.hp + stat2.hp,
		stat1.mp + stat2.mp,
		stat1.atk + stat2.atk,
		stat1.def + stat2.def,
		stat1.mag + stat2.mag,
		stat1.spr + stat2.spr
	};
	return stat;
}

stat_t stat_zero() {
	stat_t stat = { 0, 0, 0, 0, 0, 0 };
	return stat;
}