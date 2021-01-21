#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>

#define N_FILE_TESSERE "tiles.txt"
#define N_FILE_SCACCHIERA "board.txt"

typedef struct {
	char col_v, col_o;
	int val_v, val_o;
} Tessera;

Tessera** malloc2d(int nr, int nc);
Tessera tesseraVuota();
void posizionaTessere(Tessera* tessere, Tessera** board, int n_righe, int n_colonne, int n_tessere, int* mark);
void posizionaTessereR(int pos, Tessera* tessere, Tessera** board, int n_righe, int n_colonne, int* max_punt, int* mark, int n_tessere, Tessera** best_board);
Tessera ruota(Tessera tes);
int calcolaPunt(Tessera** board, int nr, int nc);
void free2d(Tessera** mat, int n_righe);
void printTes(Tessera tes);

int main() {
	int n_tessere, n_righe, n_colonne, idx, rot, * usate;
	Tessera* tessere, **board;
	FILE* f_tessere, * f_board;

	f_tessere = fopen(N_FILE_TESSERE, "r");
	fscanf(f_tessere, "%d", &n_tessere);
	tessere = malloc(n_tessere * sizeof(*tessere));
	usate = calloc(n_tessere, sizeof(int));
	for (int i = 0; i < n_tessere; i++) {
		fscanf(f_tessere, " %c %d %c %d ", &(tessere[i].col_o), &(tessere[i].val_o), &(tessere[i].col_v), &(tessere[i].val_v));
	}
	fclose(f_tessere);

	f_board = fopen(N_FILE_SCACCHIERA, "r");
	fscanf(f_board, "%d %d", &n_righe, &n_colonne);
	board = malloc2d(n_righe, n_colonne);
	for (int i = 0; i < n_righe; i++) {
		for (int j = 0; j < n_colonne; j++) {
			fscanf(f_board, "%d/%d", &idx, &rot);
			if (idx != -1) {
				usate[idx] = 1;
				if (rot == 1) {
					board[i][j] = ruota(tessere[idx]);
				}
				else {
					board[i][j] = tessere[idx];
				}
			}
			else {
				board[i][j] = tesseraVuota();
			}
		}
	}
	fclose(f_board);

	posizionaTessere(tessere, board, n_righe, n_colonne, n_tessere, usate);

	free(tessere);
	free(usate);
	free2d(board, n_righe);
}

Tessera** malloc2d(int nr, int nc) {
	Tessera** mat;
	mat = malloc(nr * sizeof(*mat));
	for (int i = 0; i < nr; i++) {
		mat[i] = malloc(nc * sizeof(*mat[i]));
	}
	return mat;
}

Tessera tesseraVuota() {
	Tessera tes = { -1, -1, -1, -1 };
	return tes;
}

void posizionaTessere(Tessera* tessere, Tessera** board, int n_righe, int n_colonne, int n_tessere, int* mark) {
	int max_punt = 0;
	Tessera** best_board = malloc2d(n_righe, n_colonne);
	posizionaTessereR(0, tessere, board, n_righe, n_colonne, &max_punt, mark, n_tessere, best_board);
	for (int i = 0; i < n_righe; i++) {
		for (int j = 0; j < n_colonne; j++) {
			printTes(best_board[i][j]);
		}
		printf("\n");
	}
	printf("Punteggio max: %d", calcolaPunt(best_board, n_righe, n_colonne));

	free2d(best_board, n_righe);
}

void posizionaTessereR(int pos, Tessera* tessere, Tessera** board, int n_righe, int n_colonne, int* max_punt, int* mark, int n_tessere, Tessera** best_board) {
	int riga = pos / n_colonne, colonna = pos % n_colonne;
	int punt;

	if (riga >= n_righe) {
		if ((punt = calcolaPunt(board, n_righe, n_colonne)) > *max_punt) {
			*max_punt = punt;
			for (int i = 0; i < n_righe; i++) {
				for (int j = 0; j < n_colonne; j++) {
					best_board[i][j] = board[i][j];
				}
			}
		}
		return;
	}

	if (board[riga][colonna].col_o == -1) {
		for (int i = 0; i < n_tessere; i++) {
			if (mark[i] == 0) {
				mark[i] = 1;
				board[riga][colonna] = tessere[i];
				posizionaTessereR(pos + 1, tessere, board, n_righe, n_colonne, max_punt, mark, n_tessere, best_board);
				board[riga][colonna] = ruota(tessere[i]);
				posizionaTessereR(pos + 1, tessere, board, n_righe, n_colonne, max_punt, mark, n_tessere, best_board);
				mark[i] = 0;
				board[riga][colonna] = tesseraVuota();
			}
		}
	}
	else {
		posizionaTessereR(pos + 1, tessere, board, n_righe, n_colonne, max_punt, mark, n_tessere, best_board);
	}
	
}

Tessera ruota(Tessera tes) {
	Tessera r_val = { tes.col_o, tes.col_v, tes.val_o, tes.val_v };
	return r_val;
}

int calcolaPunt(Tessera** board, int nr, int nc) {
	int punteggio = 0, punt_riga, punt_colonna;
	int col_uguale, riga_uguale;
	char col;
	for (int i = 0; i < nr; i++) {
		riga_uguale = 1;
		punt_riga = board[i][0].val_o;
		col = board[i][0].col_o;
		for (int j = 1; j < nc && riga_uguale; j++) {
			punt_riga += board[i][j].val_o;
			if (col != board[i][j].col_o) {
				riga_uguale = 0;
			}
		}
		if (riga_uguale) {
			punteggio += punt_riga;
		}
	}

	for (int j = 0; j < nc; j++) {
		col_uguale = 1;
		punt_riga = board[0][j].val_v;
		col = board[0][j].col_v;
		for (int i = 1; i < nr && col_uguale; i++) {
			punt_riga += board[i][j].val_v;
			if (col != board[i][j].col_v) {
				col_uguale = 0;
			}
		}
		if (col_uguale) {
			punteggio += punt_riga;
		}
	}

	return punteggio;
}

void free2d(Tessera** mat, int n_righe) {
	for (int i = 0; i < n_righe; i++) {
		free(mat[i]);
	}
	free(mat);
}

void printTes(Tessera tes) {
	printf("| %c %d %c %d | ", tes.col_o, tes.val_o, tes.col_v, tes.val_v);
}