#ifndef TIME_H
#define TIME_H

typedef struct {
	int ora;
	int minuti;
} Ora;

typedef struct {
	int anno;
	int mese;
	int giorno;
} Data;

Ora ORAnew(int ora, int minuti);
Data DATAnew(char* data_str);
Data DATAsetNull();
int DATAcompare(Data data1, Data data2);
int DATAisNull(Data data);


#endif
