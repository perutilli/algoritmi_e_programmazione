#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int t_inizio, t_fine;
} att;

void attSelDP(att* atts, int n_att);
int getDurata(att a);
//richiede che a.t_inizio < b.t_inizio
int disgiunti(att a, att b);
void printAttSel(att* atts, int* precedente, int last);
void printAtt(att a);
//compara t_inizio
int compareAtt(att a, att b);

int main() {
	att S[] = { {2,4}, {1,2}, {2,5}, {5,7}, {3,5}, {6,8} };
	int N = 6;

	attSelDP(S, N);
}

void attSelDP(att* atts, int n_att) {
	int* durata, * precedente, durata_max, last;

	durata = malloc(n_att * sizeof(int));
	precedente = malloc(n_att * sizeof(int));
	
	qsort(atts, n_att, sizeof(att), compareAtt);

	durata_max = durata[0] = getDurata(atts[0]);
	precedente[0] = -1;
	for (int i = 1; i < n_att; i++) {
		durata[i] = getDurata(atts[i]);
		precedente[i] = -1;
		for (int j = 0; j < i; j++) {
			if (disgiunti(atts[j], atts[i])) {
				if (durata[i] < durata[j] + getDurata(atts[i])) {
					durata[i] = durata[j] + getDurata(atts[i]);
					precedente[i] = j;
				}
			}
		}
		if (durata[i] > durata_max) {
			durata_max = durata[i];
			last = i;
		}
	}


	printf("Attivita' scelte: ");
	printAttSel(atts, precedente, last);
	printf("\nDurata attivita': %d", durata_max);

	free(durata);
	free(precedente);
}

int getDurata(att a) {
	return (a.t_fine - a.t_inizio);
}

int disgiunti(att a, att b) {
	return (a.t_fine <= b.t_inizio);
}

void printAttSel(att* atts, int* precedente, int last) {
	if (precedente[last] == -1) {
		printAtt(atts[last]);
		return;
	}

	printAttSel(atts, precedente, precedente[last]);
	printAtt(atts[last]);
}

void printAtt(att a) {
	printf("(%d, %d)", a.t_inizio, a.t_fine);
}

int compareAtt(att a, att b) {
	return (a.t_inizio - b.t_inizio);
}