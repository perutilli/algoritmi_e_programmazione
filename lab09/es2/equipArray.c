#include "equipArray.h"

struct equipArray_s {
	int inUso;
	int vettEq[EQUIP_SLOT];
};

void removeByIndex(equipArray_t equipArray, int index);
void insertByIndex(equipArray_t equipArray, invArray_t invArray, int index);

equipArray_t equipArray_init() {
	equipArray_t eq_arr = malloc(sizeof(*eq_arr));
	eq_arr->inUso = 0;
}

void equipArray_free(equipArray_t equipArray) {
	free(equipArray);
}

int equipArray_inUse(equipArray_t equipArray) {
	return equipArray->inUso;
}

void equipArray_print(FILE* fp, equipArray_t equipArray, invArray_t invArray) {
	for (int i = 0; i < equipArray->inUso; i++) {
		invArray_printByIndex(fp, invArray, (equipArray->vettEq)[i]);
	}
}

void equipArray_update(equipArray_t equipArray, invArray_t invArray) {
	int selezione, index;
	char nome[LEN];
	printf(" 1 > rimuovi oggetto\n 2 > aggiungi oggetto\n");
	scanf("%d", &selezione);
	switch (selezione) {
	case 1: {
		if (equipArray->inUso == 0) {
			printf("Nessun oggetto nell'equipaggiamento\n");
			return;
		}
		equipArray_print(stdout, equipArray, invArray);
		printf("inserire indice oggetto: ");
		scanf("%d", &index);
		if (index < EQUIP_SLOT && index >= 0) {
			removeByIndex(equipArray, index);
		}
		else {
			printf("indice non valido\n");
			return;
		}
		break;
	}
	case 2: {
		invArray_print(stdout, invArray);
		if (equipArray->inUso == EQUIP_SLOT) {
			printf("equipaggiamento pieno\n");
			return;
		}
		printf("inserire nome oggetto: ");
		scanf("%s", nome);
		index = invArray_searchByName(invArray, nome);
		insertByIndex(equipArray, invArray, index);
		break;
	}
	}

}

int equipArray_getEquipByIndex(equipArray_t equipArray, int index) {
	return (equipArray->vettEq)[index];
}

void removeByIndex(equipArray_t equipArray, int index) {
	equipArray->vettEq[index] = equipArray->vettEq[equipArray->inUso];
	(equipArray->inUso)--;
}

void insertByIndex(equipArray_t equipArray, invArray_t invArray, int index) {
	equipArray->vettEq[equipArray->inUso] = index;
	(equipArray->inUso)++;
}

stat_t equipArray_getStat(equipArray_t equipArray, invArray_t invArray) {
	stat_t stat_eq = stat_zero();
	for (int i = 0; i < equipArray->inUso; i++) {
		stat_eq = stat_sum(stat_eq, inv_getStat(invArray_getByIndex(invArray, (equipArray->vettEq)[i])));
	}
	return stat_eq;
}