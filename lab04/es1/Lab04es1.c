#pragma warning (disable:4996)

#include <stdlib.h>
#include <stdio.h>

int gcd(int a, int b);

int main() {
	int a, b;

	while (1) {
		printf("Inserisci 2 interi (n negativo per chiudere): ");
		scanf("%d %d", &a, &b);
		if (a < 0 || b < 0) {
			break;
		}
		printf("%d\n", gcd(a, b));
	}
}

int gcd(int a, int b) {
	int temp;

	//a deve essere il maggiore tra i due
	if (b > a) {
		temp = b;
		b = a;
		a = temp;
	}

	if (b == 0) {
		return a;
	}

	if (a % 2 == 0 && b % 2 == 0) {
		return 2 * gcd(a / 2, b / 2);
	}
	else if (a % 2 == 1 && b % 2 == 0) {
		return (gcd(a, b / 2));
	}
	else if (a % 2 == 0 && b % 2 == 1) {
		return (gcd(a / 2, b));
	}
	else {
		return (gcd((a - b) / 2, b));
	}
}
