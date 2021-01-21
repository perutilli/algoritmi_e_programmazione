#pragma warning (disable:4996)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* cercaRegexp(char* src, char* regexp);
char* cercaRegexpR(char* src, int index_write, int index_read, char* regexp, char* str);

int main() {
	char src[20] = "sdfaAGsnRgdasf";
	char regexp[20] = "A[^f]\\anR.d";

	printf("%s", cercaRegexp(src, regexp));

}

char* cercaRegexp(char* src, char* regexp) {
	char str[20];
	return cercaRegexpR(src, 0, 0, regexp, str);
}

char* cercaRegexpR(char* src, int index_write, int index_read, char* regexp, char* str) {
	char* p_write = str + index_write;
	char* p_read = regexp + index_read;
	char* res;
	switch (*p_read) {
	case '\0':
		*p_write = '\0';
		return (strstr(src, str));
	case '.':
		for (char c = 'A'; c <= 'Z'; c++) {
			*p_write = c;
			if ((res = cercaRegexpR(src, index_write + 1, index_read + 1, regexp, str)) != NULL) {
				return res;
			}
		}
		for (char c = 'a'; c <= 'z'; c++) {
			*p_write = c;
			if ((res = cercaRegexpR(src, index_write + 1, index_read + 1, regexp, str)) != NULL) {
				return res;
			}
		}
		return NULL;
	case '[':
		switch (*(p_read + 1)) {
		case '^':
		{
			char lettere[52];
			char* x;
			int idx;
			for (char c = 'A'; c <= 'Z'; c++) {
				lettere[c - 'A'] = c;
			}
			for (char c = 'a'; c <= 'z'; c++) {
				lettere[c + 'Z' - 'A' + 1 - 'a'] = c;
			}
			for (idx = 2; 
				(p_read + idx)[0] != ']'; 
				idx++) {
				for (int j = 0; j < 52; j++) {
					if (lettere[j] == *(p_read + idx)) {
						lettere[j] = -1;
					}
				}
				x = (p_read + idx) + 1;
			}

			for (int i = 0; i < 52; i++) {
				if (lettere[i] != -1) {
					*p_write = lettere[i];
					if ((res = cercaRegexpR(src, index_write + 1, index_read + idx + 1, regexp, str)) != NULL) {
						return res;
					}
				}
			}

			return NULL;
		}
		default:
		{
			char chs[52];
			int i;
			for (i = 1; *(p_read + i) != ']'; i++) {
				chs[i] = *(p_read + i);
			}
			for (int j = 0; j <= i; j++) {
				*p_write = chs[j];
				if ((res = cercaRegexpR(src, index_write + 1, index_read + i + 1, regexp, str)) != NULL) {
					return res;
				}
			}
			return NULL;
		}
		}
		break;
	case '\\':
		switch (*(p_read + 1)) {
		case 'a':
			for (char c = 'a'; c <= 'z'; c++) {
				*p_write = c;
				if ((res = cercaRegexpR(src, index_write + 1, index_read + 2, regexp, str)) != NULL) {
					return res;
				}
			}
			return NULL;
		case 'A':
			for (char c = 'A'; c <= 'Z'; c++) {
				*p_write = c;
				if ((res = cercaRegexpR(src, index_write + 1, index_read + 2, regexp, str)) != NULL) {
					return res;
				}
			}
			return NULL;
		}
		break;
	default:
		*p_write = *p_read;
		return cercaRegexpR(src, index_write + 1, index_read + 1, regexp, str);
		break;
	}

}
