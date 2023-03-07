// compile like this (for gcc on Linux):
// gcc -Wall -Wextra -Wpedantic -O3 -march=native -fPIC -shared -o c_wys_lib.so wys_lib.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT 
#endif

#ifdef __cplusplus
extern "C" {
#endif

void removechar(char *arr, unsigned int len, unsigned int i) {
	char *end = arr + len - 1;
	for (char *it = arr + i; it != end; it++) {
		*it = it[1];
	}
}
void removeuint(unsigned int *arr, unsigned int len, unsigned int i) {
	unsigned int *end = arr + len;
	for (unsigned int *it = arr + i; it != end; it++) {
		*it = it[1];
	}
}
void fill_incremental(unsigned int *arr, unsigned int len) {
	for (unsigned int i = 0; i < len; i++) {
		arr[i] = i;
	}
}

EXPORT void dontbother17_decrypt(char *data, unsigned int datalen, char *out, unsigned int n) {
	unsigned int i = 0;
	unsigned int currlen = datalen;
	for (unsigned int j = 0; j < datalen; j++, currlen--) {
		i = (i + n) % currlen;
		out[j] = data[i];
		removechar(data, currlen, i);
	}
}
EXPORT void dontbother17_encrypt(char *data, unsigned int datalen, char *out, unsigned int n) {
	unsigned int i = 0;
	unsigned int *places = (unsigned int *)malloc(sizeof(unsigned int) * datalen);
	unsigned int placeslen = datalen;
	fill_incremental(places, placeslen);
	for (unsigned int j = 0; j < datalen; j++, placeslen--) {
		i = (i + n) % placeslen;
		out[places[i]] = data[j];
		removeuint(places, placeslen, i);
	}
	free(places);
}
EXPORT void humanscantsolvethis_decrypt(char *data, unsigned int datalen, char *key, unsigned int keylen, char *out) {
	unsigned int i = 0;
	unsigned int ki = 0;
	unsigned int currlen = datalen;
	for (unsigned int j = 0; j < datalen; j++, currlen--) {
		i = (i + key[ki] - 64) % currlen;
		ki = (ki + 1) % keylen;
		out[j] = data[i];
		removechar(data, currlen, i);
	}
}
EXPORT void humanscantsolvethis_encrypt(char *data, unsigned int datalen, char *key, unsigned int keylen, char *out) {
	unsigned int i = 0;
	unsigned int ki = 0;
	unsigned int *places = (unsigned int *)malloc(sizeof(unsigned int) * datalen);
	unsigned int placeslen = datalen;
	fill_incremental(places, placeslen);
	for (unsigned int j = 0; j < datalen; j++, placeslen--) {
		i = (i + key[ki] - 64) % placeslen;
		ki = (ki + 1) % keylen;
		out[places[i]] = data[j];
		removeuint(places, placeslen, i);
	}
	free(places);
}

#ifdef __cplusplus
}
#endif
