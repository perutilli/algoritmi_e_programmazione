#pragma warning (disable:4996)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILE_NAME "brani.txt"
#define FILE_OUT "playlists.txt"
#define MAX_NOME 255

// le playlist possibili sono scritte sul file playlists.txt (FILE_OUT)

void generaPlaylists(char*** mat, int* n_canzoni, int n_amici);
void generaPlaylistsR(int pos, char*** mat, int* n_canzoni, int n_amici, char** playlist, FILE* output);

int main() {
	char*** canzoni;
	int n_amici, *n_canzoni;
	FILE* input;

	input = fopen(FILE_NAME, "r");
	fscanf(input, "%d", &n_amici);
	canzoni = (char***)malloc(n_amici * sizeof(char**));
	n_canzoni = (int*)malloc(n_amici * sizeof(int));
	if (canzoni == NULL) exit(1);
	for (int i = 0; i < n_amici; i++) {
		fscanf(input, "%d", &(n_canzoni[i]));
		canzoni[i] = (char**)malloc(n_canzoni[i] * sizeof(char*));
		for (int j = 0; j < n_canzoni[i]; j++) {
			canzoni[i][j] = (char*)malloc(MAX_NOME * sizeof(char));
			fscanf(input, "%s", canzoni[i][j]);
		}
	}
	fclose(input);

	generaPlaylists(canzoni, n_canzoni, n_amici);

	for (int i = 0; i < n_amici; i++) {
		for (int j = 0; j < n_canzoni[i]; j++) {
			free(canzoni[i][j]);
		}
		free(canzoni[i]);
	}
	free(canzoni);
	free(n_canzoni);

}

void generaPlaylists(char*** mat, int* n_canzoni, int n_amici) {
	FILE* out = fopen(FILE_OUT, "w");
	char** playlist = (char**)malloc(n_amici * sizeof(char*));
	generaPlaylistsR(0, mat, n_canzoni, n_amici, playlist, out);
	fclose(out);
	free(playlist);

}

void generaPlaylistsR(int pos, char*** mat, int* n_canzoni, int n_amici, char** playlist, FILE* output) {

	if (pos == n_amici) {
		for (int i = 0; i < n_amici; i++) {
			fprintf(output, "%s ", playlist[i]);
		}
		fprintf(output, "\n");
		return;
	}

	for (int i = 0; i < n_canzoni[pos]; i++) {
		playlist[pos] = mat[pos][i];
		generaPlaylistsR(pos + 1, mat, n_canzoni, n_amici, playlist, output);
	}
}
