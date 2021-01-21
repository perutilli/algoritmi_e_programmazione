#pragma warning (disable:4996)

// non dà i risultati giusti non so perchè

#include <stdio.h>
#include <stdlib.h>

#define N_PIETRE 4
#define NOME_FILE "hard_test_set.txt"

typedef enum { z, r, t, s } Pietra;
const char pietre[] = { 'z', 'r', 't', 's' };

int calcolaLenMax(int* rip_pietre);
int**** allocaMat(int* rip_pietre);
void freeMat(int**** mat, int* rip_pietre);
int fZ(int* rip_pietre, int**** mat_best);
int fR(int* rip_pietre, int**** mat_best);
int fT(int* rip_pietre, int**** mat_best);
int fS(int* rip_pietre, int**** mat_best);

void main() {
	int rip_pietre[N_PIETRE];
	FILE* test = fopen(NOME_FILE, "r");
	int n_test;
	fscanf(test, "%d", &n_test);
	for (int i = 0; i < n_test; i++) {
		fscanf(test, "%d %d %d %d", &(rip_pietre[0]), &(rip_pietre[1]), &(rip_pietre[2]), &(rip_pietre[3]));
		printf("%d\n", calcolaLenMax(rip_pietre));
	}
	fclose(test);
}

int calcolaLenMax(int* rip_pietre) {
	int**** mat;
	int lenZ, lenR, lenT, lenS;
	mat = allocaMat(rip_pietre);
	rip_pietre[z]--;
	lenZ = fZ(rip_pietre, mat) + 1;
	rip_pietre[z]++;
	rip_pietre[r]--;
	lenR = fR(rip_pietre, mat) + 1;
	rip_pietre[r]++;
	rip_pietre[t]--;
	lenT = fT(rip_pietre, mat) + 1;
	rip_pietre[t]++; 
	rip_pietre[s]--;
	lenS = fS(rip_pietre, mat) + 1;
	rip_pietre[s]++;
	freeMat(mat, rip_pietre);
	return max(max(max(lenZ, lenR), lenT), lenS);

}

int fZ(int* rip_pietre, int**** mat_best) {
	int res, t1 = 0, t2 = 0;
	if (rip_pietre[z] == 0) {
		return 0;
	} 
	else if (mat_best[rip_pietre[0]][rip_pietre[1]][rip_pietre[2]][rip_pietre[3]] != -1) {
		return mat_best[rip_pietre[0]][rip_pietre[1]][rip_pietre[2]][rip_pietre[3]];
	}
	else if (rip_pietre[z] > 0) {
		rip_pietre[z]--;
		t1 = fZ(rip_pietre, mat_best) + 1;
		rip_pietre[z]++;
	} 
	if (rip_pietre[r] > 0) {
		rip_pietre[r]--;
		t2 = fR(rip_pietre, mat_best) + 1;
		rip_pietre[r]++;
	}
	res = max(t1, t2);
	mat_best[rip_pietre[0]][rip_pietre[1]][rip_pietre[2]][rip_pietre[3]] = res;
	return res;
}

int fR(int* rip_pietre, int**** mat_best) {
	int res, t1 = 0, t2 = 0;
	if (rip_pietre[r] == 0) {
		return 0;
	}
	else if (mat_best[rip_pietre[0]][rip_pietre[1]][rip_pietre[2]][rip_pietre[3]] != -1) {
		return mat_best[rip_pietre[0]][rip_pietre[1]][rip_pietre[2]][rip_pietre[3]];
	}
	else if (rip_pietre[s] > 0) {
		rip_pietre[s]--;
		t1 = fS(rip_pietre, mat_best) + 1;
		rip_pietre[s]++;
	}
	if (rip_pietre[t] > 0) {
		rip_pietre[t]--;
		t2 = fT(rip_pietre, mat_best) + 1;
		rip_pietre[t]++;
	}
	res = max(t1, t2);
	mat_best[rip_pietre[0]][rip_pietre[1]][rip_pietre[2]][rip_pietre[3]] = res;
	return res;
}

int fT(int* rip_pietre, int**** mat_best) {
	int res, t1 = 0, t2 = 0;
	if (rip_pietre[t] == 0) {
		return 0;
	}
	else if (mat_best[rip_pietre[0]][rip_pietre[1]][rip_pietre[2]][rip_pietre[3]] != -1) {
		return mat_best[rip_pietre[0]][rip_pietre[1]][rip_pietre[2]][rip_pietre[3]];
	}
	else if (rip_pietre[z] > 0) {
		rip_pietre[z]--;
		t1 = fZ(rip_pietre, mat_best) + 1;
		rip_pietre[z]++;
	}
	if (rip_pietre[r] > 0) {
		rip_pietre[r]--;
		t2 = fR(rip_pietre, mat_best) + 1;
		rip_pietre[r]++;
	}
	res = max(t1, t2);
	mat_best[rip_pietre[0]][rip_pietre[1]][rip_pietre[2]][rip_pietre[3]] = res;
	return res;
}

int fS(int* rip_pietre, int**** mat_best) {
	int res, t1 = 0, t2 = 0;
	if (rip_pietre[s] == 0) {
		return 0;
	}
	else if (mat_best[rip_pietre[0]][rip_pietre[1]][rip_pietre[2]][rip_pietre[3]] != -1) {
		return mat_best[rip_pietre[0]][rip_pietre[1]][rip_pietre[2]][rip_pietre[3]];
	}
	else if (rip_pietre[s] > 0) {
		rip_pietre[s]--;
		t1 = fS(rip_pietre, mat_best) + 1;
		rip_pietre[s]++;
	}
	if (rip_pietre[t] > 0) {
		rip_pietre[t]--;
		t2 = fT(rip_pietre, mat_best) + 1;
		rip_pietre[t]++;
	}
	res = max(t1, t2);
	mat_best[rip_pietre[0]][rip_pietre[1]][rip_pietre[2]][rip_pietre[3]] = res;
	return res;
}



int**** allocaMat(int* rip_pietre) {
	int**** mat;
	mat = malloc((rip_pietre[z] + 1) * sizeof(*mat));
	for (int i = 0; i < rip_pietre[z] + 1; i++) {
		mat[i] = malloc((rip_pietre[r] + 1) * sizeof(*mat[i]));
		for (int j = 0; j < rip_pietre[r] + 1; j++) {
			mat[i][j] = malloc((rip_pietre[t] + 1) * sizeof(*mat[i][j]));
			for (int k = 0; k < rip_pietre[t] + 1; k++) {
				mat[i][j][k] = malloc((rip_pietre[s] + 1) * sizeof(*mat[i][j][k]));
				for (int l = 0; l < rip_pietre[s] + 1; l++) {
					mat[i][j][k][l] = -1;
				}
			}
		}
	}
	return mat;
}

void freeMat(int**** mat, int* rip_pietre) {
	for (int i = 0; i < rip_pietre[z] + 1; i++) {
		for (int j = 0; j < rip_pietre[r] + 1; j++) {
			for (int k = 0; k < rip_pietre[t] + 1; k++) {
				free(mat[i][j][k]);
			}
			free(mat[i][j]);
		}
		free(mat[i]);
	}
	free(mat);
}

