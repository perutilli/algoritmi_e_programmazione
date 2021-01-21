#ifndef QUOT_H
#define QUOT_H

#include "time.h"
#include <stdio.h>

typedef struct {
	float value;
	int n_trans;
	Data data;
} Quot;

Quot QUOTnew(float value, int n_trans, Data data);
Quot QUOTsetNull();
Data QUOTgetData(Quot quot);
int QUOTisNull(Quot quot);
Quot QUOTupdate(Quot quot, float val, int num);
void QUOTstore(Quot quot, FILE* fout);
float QUOTgetValue(Quot quot);
#endif

