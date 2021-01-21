#ifndef TITOLI_ARR_H
#define TITOLI_ARR_H

typedef struct arr_titoli* Titoli_array;

Titoli_array TITOLIarrayInit(int n_titoli);
void TITOLIarrayFree(Titoli_array vett);
void TITOLIarrayInsert(Titoli_array vett, Titolo titolo);
Titolo TITOLIarraySearch(Titoli_array vett, char* nome);

#endif