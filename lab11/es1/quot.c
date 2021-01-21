#include <stdlib.h>
#include "quot.h"

Quot QUOTnew(float value, int n_trans, Data data) {
	Quot quot;
	quot.value = value;
	quot.n_trans = n_trans;
	quot.data = data;
	return quot;
}

Quot QUOTsetNull() {
	return QUOTnew(-1, 0, DATAsetNull());
}

Data QUOTgetData(Quot quot) {
	return quot.data;
}

int QUOTisNull(Quot quot) {
	return (quot.value == -1);
}

Quot QUOTupdate(Quot quot, float val, int num) {
	float value;
	int n_trans;
	value = (quot.value * quot.n_trans + val * num) / (quot.n_trans + num);
	n_trans = quot.n_trans + num;
	return QUOTnew(value, n_trans, quot.data);
}

void QUOTstore(Quot quot, FILE* fout) {
	fprintf(fout, "%f\n", quot.value);
}

float QUOTgetValue(Quot quot) {
	return quot.value;
}