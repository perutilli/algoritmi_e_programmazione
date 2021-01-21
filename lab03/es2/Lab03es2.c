#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>

// Nel mio computer sembra che double e long double siano entrambi su 8 bit e le rappresentazioni risultano identiche

void stampaCodifica(void* p, int size, int bigEndian);

int main() {
	float af, prova = 10.0;
	double ad;
	long double ald;
	int bigEndian;

	unsigned char* c = (unsigned char*)&prova;
	bigEndian = (*c != 0);

	printf("inserire float, double e long double\n");
	scanf("%f %lf %Lf", &af, &ad, &ald);

	stampaCodifica((void*)&af, sizeof(af), bigEndian);
	stampaCodifica((void*)&ad, sizeof(ad), bigEndian);
	stampaCodifica((void*)&ald, sizeof(ald), bigEndian);
	

}

void stampaCodifica(void* p, int size, int bigEndian) {
	int byte, temp;
	int rappr[80];
	unsigned char* c = (unsigned char*)p;
	// rimuove padding bit in caso di long double
	if (size == 12) {
		c += 2;
		size -= 2;
	}

	for (int i = 0; i < size; i++) {
		byte = *(c + i);
		int n = 0;
		while (byte > 0) {
			rappr[i * 8 + n] = (byte % 2);
			byte /= 2;
			n++;
		}
		while (n < 8) {
			rappr[i * 8 + n] = 0;
			n++;
		}
	}

	if (!bigEndian) {
		for (int i = 0; i < (size * 4); i++) {
			temp = rappr[i];
			rappr[i] = rappr[size * 8 - i - 1];
			rappr[size * 8 - i - 1] = temp;
		}
	}

	printf("Byte/Bit rappresentazione: %d/%d\n", size, size*8);
	printf("Bit del segno: %d\n", rappr[0]);

	switch (size) {
		case 4:
			printf("Esponente: ");
			for (int i = 1; i < 9; i++) {
				printf("%d", rappr[i]);
			}
			printf("\nMantissa: ");
			for (int i = 9; i < size * 8; i++) {
				printf("%d", rappr[i]);
			}
			break;
		case 8:
			printf("Esponente: ");
			for (int i = 1; i < 12; i++) {
				printf("%d", rappr[i]);
			}
			printf("\nMantissa: ");
			for (int i = 12; i < size * 8; i++) {
				printf("%d", rappr[i]);
			}
			break;
		case 10:
			printf("Esponente: ");
			for (int i = 1; i < 16; i++) {
				printf("%d", rappr[i]);
			}
			printf("\nMantissa: ");
			for (int i = 16; i < size * 8; i++) {
				printf("%d", rappr[i]);
			}
			break;
	}
	printf("\n");

}
