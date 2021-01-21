#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>

#define N_PIETRE 4
#define NOME_TEST "testfacile.txt"

typedef enum {z, r, t, s}Pietra;

const char pietre[] = {'z', 'r', 't', 's'};
void disp(int* rip_pietre);
void dispR(char* sol, int pos, int len, int* rip_pietre, int* end, int* len_best, char* sol_best);
int check(char* sol, int len);
int maxLenEccesso(int* rip_pietre);

int main() {
	int rip_pietre[N_PIETRE], n_test;
	FILE* test = fopen(NOME_TEST, "r");
	fscanf(test, "%d", &n_test);
	for (int i = 0; i < n_test; i++) {
		for (int j = 0; j < N_PIETRE; j++) {
			fscanf(test, "%d", &rip_pietre[j]);
		}
		disp(rip_pietre);
	}
}

void disp(int* rip_pietre) {
	int len_max = 0, end = 0, len_best = 0;
	char* sol, * sol_best;
	for (int i = 0; i < N_PIETRE; i++) {
		len_max += rip_pietre[i];
	}

	sol = (char*)malloc(len_max * sizeof(char));
	sol_best = (char*)malloc(len_max * sizeof(char));

	dispR(sol, 0, len_max, rip_pietre, &end, &len_best, sol_best);

	printf("len collana: %d\n", len_best);

	free(sol);
	free(sol_best);
}

void dispR(char* sol, int pos, int len, int* rip_pietre, int* end, int* len_best, char* sol_best) {

	if (*end) return;

	if (pos >= len) {
		*end = 1;
	}

	int deadend = 0;
	for (int i = 0; i < N_PIETRE && !(*end); i++) {
		deadend = 1;
		if (rip_pietre[i] > 0) {
			sol[pos] = pietre[i];
			if ((pos + maxLenEccesso(rip_pietre)) < *len_best) {
				return;
			}
			rip_pietre[i]--;
			if (check(sol, pos + 1)) {
				deadend = 0;
				dispR(sol, pos + 1, len, rip_pietre, end, len_best, sol_best);
				if (*end) return;
			}
			rip_pietre[i]++;
		}
	}

	if ((deadend && pos > *len_best) || (*end)) {
		for (int i = 0; i < pos; i++) {
			sol_best[i] = sol[i];
		}
		*len_best = pos;
	}
	return;
}

int check(char* sol, int len) {
	int i = len - 2;
	switch (sol[i]) {
	case 'z': case 't':
		if (sol[i + 1] != 'z' && sol[i + 1] != 'r') {
			return 0;
		}
		break;
	case 's': case 'r':
		if (sol[i + 1] != 's' && sol[i + 1] != 't') {
			return 0;
		}
		break;
	}
	return 1;
}

int maxLenEccesso(int* rip_pietre) {
	int max_z, max_r, max_s, max_t;
	
	max_z = rip_pietre[z] * (rip_pietre[t] > 0);
	if (max_z > 0) {
		rip_pietre[t]--;
	}
	max_s = rip_pietre[s] * (rip_pietre[r] > 0);
	if (max_s > 0) {
		rip_pietre[s]--;
	}
	max_t = min(rip_pietre[t], (rip_pietre[s] + rip_pietre[r]));
	max_r = min(rip_pietre[r], (rip_pietre[z] + rip_pietre[t]));
	if (max_z > 0) {
		rip_pietre[t]++;
	}
	if (max_s > 0) {
		rip_pietre[s]++;
	}
	return max_z + max_r + max_s + max_t;
}