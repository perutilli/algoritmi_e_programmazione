#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>

#define N_PIETRE 4
#define NOME_TEST "test.txt"

typedef enum { z, r, t, s } Pietra;

const char pietre[] = { 'z', 'r', 't', 's' };
void disp(int* rip_pietre, int max_rip, int* values);
void dispR(char* sol, int pos, int len_max, int* rip_pietre, int* end, int* len_best, char* sol_best, int max_rip, int* values, int curr_rip, int curr_value);
int check(char* sol, int len, int curr_rip, int max_rip);
int maxValEccesso(int* rip_pietre, int* values);
int calculateValue(char* sol, int len, int* values);
int writeBest(char* sol, char** sol_best, int len);

int main() {
	int rip_pietre[N_PIETRE], n_test, values[N_PIETRE], max_rip;
	FILE* test = fopen(NOME_TEST, "r");
	fscanf(test, "%d", &n_test);
	for (int i = 0; i < n_test; i++) {
		for (int j = 0; j < N_PIETRE; j++) {
			fscanf(test, "%d", &rip_pietre[j]);
		}
		for (int j = 0; j < N_PIETRE; j++) {
			fscanf(test, "%d", &values[j]);
		}
		fscanf(test, "%d", &max_rip);
		disp(rip_pietre, max_rip, values);
	}
}

void disp(int* rip_pietre, int max_rip, int* values) {
	int len_max = 0, end = 0, val_best = 0;
	int curr_rip = 0;
	char* sol, * sol_best;
	for (int i = 0; i < N_PIETRE; i++) {
		len_max += rip_pietre[i];
	}

	sol = (char*)malloc(len_max * sizeof(char));
	sol_best = (char*)malloc((len_max + 1) * sizeof(char));

	dispR(sol, 0, len_max, rip_pietre, &end, &val_best, sol_best, max_rip, values, curr_rip, 0);

	printf("val collana: %d\n", val_best);
	printf("%s\n", sol_best);

	free(sol);
	free(sol_best);
}

void dispR(char* sol, int pos, int len_max, int* rip_pietre, int* end, int* val_best, char* sol_best, int max_rip, int* values, int curr_rip, int curr_value) {
	int v;

	if (pos >= len_max) {
		if ((v = calculateValue(sol, pos, values)) != -1) {
			*val_best = v;
			*end = 1;
			return;
		}
	}

	int deadend;
	for (int i = 0; i < N_PIETRE && !(*end); i++) {
		deadend = 1;
		if (rip_pietre[i] > 0) {
			sol[pos] = pietre[i];
			curr_value += values[i];
			if (pos > 0 && sol[pos - 1] == sol[pos]) {
				curr_rip++;
			}
			else {
				curr_rip = 1;
			}

			if ((curr_value + maxValEccesso(rip_pietre, values)) < *val_best) {
				return;
			}
			rip_pietre[i]--;
			if (check(sol, pos + 1, curr_rip, max_rip)) {
				deadend = 0;
				dispR(sol, pos + 1, len_max, rip_pietre, end, val_best, sol_best, max_rip, values, curr_rip, curr_value);
				if (*end) return;
			}
			if (curr_rip != 1) {
				curr_rip--;
			}
			else {
				if (sol[pos - 1] == sol[pos - 2]) {
					curr_rip = 2;
					if (sol[pos - 2] == sol[pos - 3]) {
						curr_rip++;
					}
				}
				else {
					curr_rip = 1;
				}
			}
			curr_value -= values[i];
			rip_pietre[i]++;
		}
	}

	if (deadend) {
		if ((v = calculateValue(sol, pos, values)) > *val_best) {
			writeBest(sol, &sol_best, pos);
			*val_best = v;
		}
	}
	return;
}

int check(char* sol, int len, int curr_rip, int max_rip) {
	int i = len - 2;

	if (curr_rip > max_rip) {
		return 0;
	}

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


// usa anche n_s > n_z
int maxValEccesso(int* rip_pietre, int* values) {
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
	return max_z * values[z] + max_r * values[r] + max_s * values[s] + max_t * values[t];
}

//-1 se n_z > n_s
int calculateValue(char* sol, int len, int* values) {
	int val = 0;
	int n_z = 0, n_s = 0;
	for (int i = 0; i < len; i++) {
		switch (sol[i])
		{
		case 'z':
			n_z++;
			val += values[z];
			break;
		case 'r':
			val += values[r];
			break;
		case 't':
			val += values[t];
			break;
		case 's':
			n_s++;
			val += values[s];
			break;
		}
	}
	if (n_z > n_s) {
		val = -1;
	}
	return val;
}

int writeBest(char* sol, char** sol_best, int len) {
	int i;
	for (i = 0; i < len; i++) {
		(*sol_best)[i] = sol[i];
	}
	(*sol_best)[i] = '\0';
}