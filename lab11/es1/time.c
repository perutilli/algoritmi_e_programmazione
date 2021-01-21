#pragma warning (disable:4996)

#include <stdlib.h>
#include <stdio.h>
#include "time.h"

Ora ORAnew(int ora, int minuti) {
	Ora orario;
	orario.ora = ora;
	orario.minuti = minuti;
	return orario;
}

Data DATAnew(char* data_str) {
	Data data;
	int anno, mese, giorno;
	sscanf(data_str, "%d/%d/%d", &anno, &mese, &giorno);
	data.anno = anno;
	data.mese = mese;
	data.giorno = giorno;
	return data;
}

Data DATAsetNull() {
	return DATAnew("0/0/0");
}

int DATAcompare(Data data1, Data data2) {
	int diff;
	if ((diff = data1.anno - data2.anno) != 0) {
		return diff;
	}
	if ((diff = data1.mese - data2.mese) != 0) {
		return diff;
	}
	if ((diff = data1.giorno - data2.giorno) != 0) {
		return diff;
	}
	return 0;
}

int DATAisNull(Data data) {
	return (data.anno == 0);
}