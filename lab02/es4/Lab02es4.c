#include <stdlib.h>
#include <stdio.h>

#define MAX_L 40

void selectionSort(int arr[], int N);
void insertionSort(int arr[], int N);
void shellSort(int arr[], int N);

int main() {
	int n_seq, sequenza[MAX_L], len;
	FILE* input;

	input = fopen("sort.txt", "r");
	fscanf(input, "%d", &n_seq);
	for (int i = 0; i < n_seq; i++) {
		fscanf(input, "%d", &len);
		for (int j = 0; j < len; j++) {
			fscanf("%d", &sequenza[j]);
		}
	}

	insertionSort(arr, len);

	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
}

void selectionSort(int arr[], int N) {
	int n_scambi = 0, n_it_est = 0;
	int i_min, temp;
	for (int i = 0; i < N; i++) {
		n_it_est++;
		i_min = i;
		for (int j = i + 1; j < N; j++) {
			if (arr[j] < arr[i_min]) {
				i_min = j;
			}
		}
		temp = arr[i];
		arr[i] = arr[i_min];
		arr[i_min] = temp;
		n_scambi++;
	}
	printf("selection sort: num scamb -> %d num iterazioni ciclo esterno -> %d\n", n_scambi, n_it_est);
}

void insertionSort(int arr[], int N) {
	int n_scambi = 0, n_it_est = 0;
	int temp;
	for (int i = 1; i < N; i++) {
		n_it_est++;
		for (int j = i - 1; j >= 0; j--) {
			if (arr[j + 1] < arr[j]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				n_scambi++;
			}
			else {
				break;
			}
		}
	}
	printf("insertion sort: num scamb -> %d num iterazioni ciclo esterno -> %d\n", n_scambi, n_it_est);
}

void shellSort(int arr[], int N) {
	int n_scambi = 0, n_it_est = 0;
	int k = 0, delta = 0, temp;
	while (delta < N / 3) {
		k++;
		delta = (3 * k) + 1;
	}
	while (delta > 0) {
		for (int i = 1; i < N; i++) {
			n_it_est++;
			for (int k = i - delta; k >= 0; k = k - delta) {
				if (arr[k + 1] < arr[k]) {
					temp = arr[k];
					arr[k] = arr[k + 1];
					arr[k + 1] = temp;
					n_scambi++;
				}
				else {
					break;
				}
			}
		}
		delta -= 3;
	}
	printf("shell sort: num scamb -> %d num iterazioni ciclo esterno -> %d\n", n_scambi, n_it_est);
}
