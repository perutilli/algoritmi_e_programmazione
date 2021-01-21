#ifndef TITOLO_H
#define TITOLO_H

#include "quot.h"
#include "time.h"

typedef struct titolo* Titolo;

Titolo TITOLOinit(char* nome);
void TITOLOfree(Titolo titolo);
char* TITOLOgetName(Titolo titolo);
Titolo TITOLOsetNull();
void TITOLOupdateQuot(Titolo t, Data data, float val, int num);
int TITOLOisNull(Titolo titolo);
Quot TITOLOsearchQuot(Titolo titolo, Data data);
//if data_min == data_max == NULL ricerca su tutto il BST
void TITOLOquotMaxMin(Titolo titolo, Data data_min, Data data_max);
void TITOLObalanceBst(Titolo titolo);

#endif
