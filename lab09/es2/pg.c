#include "pg.h"

int pg_read(FILE* fp, pg_t* pgp) {
	char cod[LEN], nome[LEN], classe[LEN];
	if (fscanf(fp, "%s %s %s", cod, nome, classe) == EOF) {
		return EOF;
	}
	strcpy(pgp->cod, cod);
	strcpy(pgp->nome, nome);
	strcpy(pgp->classe, classe);
	stat_read(fp, &(pgp->b_stat));
	pgp->equip = equipArray_init();
	//pgp->eq_stat = equipArray_getStat(pgp->equip);

	return 1;
}

void pg_clean(pg_t* pgp) {
	equipArray_free(pgp->equip);
}

void pg_print(FILE* fp, pg_t* pgp, invArray_t invArray) {
	fprintf(fp, "%s %s %s ", pgp->cod, pgp->nome, pgp->classe);
	stat_print(fp, &(pgp->b_stat), 1);
	if (equipArray_inUse(pgp->equip) > 0) {
		fprintf(fp, "\nequipaggiamento:\n");
		equipArray_print(fp, pgp->equip, invArray);
		fprintf(fp, "statistiche equipaggiamento: ");
		pgp->eq_stat = equipArray_getStat(pgp->equip, invArray);
		stat_print(fp, &(pgp->eq_stat), 1);
	}
}

void pg_updateEquip(pg_t* pgp, invArray_t invArray) {
	equipArray_update(pgp->equip, invArray);
}

int pg_codCompare(pg_t* pgp, char* cod) {
	return (strcmp(pgp->cod, cod));
}