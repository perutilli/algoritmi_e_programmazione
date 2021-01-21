#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>

int majority(int* a, int N);
void QuickSort(int* v, int len);
void QuickSortR(int* v, int l, int r);
int partition(int* v, int l, int r);
void swap(int* v, int n1, int n2);

int main() {
	int v[] = { 8, 8, 8, 7, 3, 2, 8, 8 };
	printf("%d", majority(v, 8));
}

int majority(int* a, int N) {
	int t, cnt;
	QuickSort(a, N);
	t = a[0];
	cnt = 1;
	for (int i = 1; i < N; i++) {
		if (a[i] == t) {
			cnt++;
		}
		else {
			cnt = 1;
			t = a[i];
		}
		if (cnt > N / 2) {
			return t;
		}
	}
	return -1;
}

void QuickSort(int* v, int len) {
	int l = 0, r = len - 1;
	QuickSortR(v, l, r);
}

void QuickSortR(int* v, int l, int r) {
	int q;
	if (r <= l) {
		return;
	}
	q = partition(v, l, r);
	QuickSortR(v, l, q - 1);
	QuickSortR(v, q + 1, r);
	return;
	
}

void swap(int* v, int n1, int n2) {
	int temp;
	temp = v[n1];
	v[n1] = v[n2];
	v[n2] = temp;
}

int partition(int* v, int l, int r) {
	int i = l - 1, j = r;
	int pivot = v[r];

	for (;;) {
		while (v[++i] < pivot);
		while (v[--j] > pivot) {
			if (j == l) {
				break;
			}
		}
		if (i >= j) 
			break;
		swap(v, i, j);
	}
	swap(v, i, r);
	return i;
}
