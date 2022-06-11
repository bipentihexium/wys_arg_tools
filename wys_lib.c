/*
Copyright (c) 2022 bipentihexium

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

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
	char *end = arr + len;
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
