#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int t_inizio, t_fine;
} att;

void attSel(int N, att* v);
void attSelR(int pos, int N, att* v, int* sol, int* sol_best, int * max_durata);
int check(int* sol, int pos, att* v);
int durataSol(int* sol, int len, att* v);
void printAtt(att attivita);

int main() {
	att S[] = { {1,2}, {2,4}, {2,5}, {3,5}, {5,7}, {6,8} };
	int N = 6;

	attSel(N, S);

}

void attSel(int N, att* v) {
	int durata = 0;
	int* sol = calloc(N, sizeof(int));
	int* sol_best = calloc(N, sizeof(int));
	attSelR(0, N, v, sol, sol_best, &durata);

	for (int i = 0; i < N; i++) {
		if (sol_best[i] == 1) {
			printAtt(v[i]);
		}
	}

	free(sol);
	free(sol_best);
}

void attSelR(int pos, int N, att* v, int* sol, int* sol_best, int * max_durata) {
	int durata;

	if (pos >= N) {
		if ((durata = durataSol(sol, pos, v)) > *max_durata) {
			for (int i = 0; i < N; i++) {
				sol_best[i] = sol[i];
				*max_durata = durata;
			}
		}
		return;
	}


	sol[pos] = 1;
	if (check(sol, pos + 1, v)) {
		attSelR(pos + 1, N, v, sol, sol_best, max_durata);
	}
	sol[pos] = 0;
	attSelR(pos + 1, N, v, sol, sol_best, max_durata);
}

int check(int* sol, int len, att* v) {
	for (int i = 0; i < len; i++) {
		if (sol[i] == 1) {
			for (int j = i + 1; j < len; j++) {
				if (sol[j] == 1) {
					if (v[i].t_inizio <= v[j].t_inizio) {
						if (v[i].t_fine > v[j].t_inizio) {
							return 0;
						}
					}
					else {
						if (v[j].t_fine > v[j].t_inizio) {
							return 0;
						}
					}
				}
			}
		}
	}
	return 1;
}

int durataSol(int* sol, int len, att* v) {
	int durata = 0;

	for (int i = 0; i < len; i++) {
		if (sol[i] == 1) {
			durata += (v[i].t_fine - v[i].t_inizio);
		}
	}

	return durata;

}


void printAtt(att attivita) {
	printf("(%d %d) ", attivita.t_inizio, attivita.t_fine);
}