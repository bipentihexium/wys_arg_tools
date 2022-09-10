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

typedef struct {
	char *data;
	unsigned int len;
	unsigned int *perm;
} TranspositionCipher;
EXPORT TranspositionCipher *TranspositionCipher_new(char *data, unsigned int len) {
	TranspositionCipher *tc = (TranspositionCipher *)malloc(sizeof(TranspositionCipher));
	tc->data = (char *)malloc(sizeof(char) * len);
	tc->perm = (unsigned int *)malloc(sizeof(unsigned int) * len);
	tc->len = len;
	memcpy(tc->data, data, sizeof(char) * len);
	return tc;
}
EXPORT void TranspositionCipher_delete(TranspositionCipher *tc) {
	free(tc->data);
	free(tc->perm);
	free(tc);
}
EXPORT void TranspositionCipher_setPerm(TranspositionCipher *tc, unsigned int *perm, unsigned int len) {
	memcpy(tc->perm, perm, (len < tc->len ? len : tc->len) * sizeof(unsigned int));
}
EXPORT void TranspositionCipher_setIdentity(TranspositionCipher *tc) {
	fill_incremental(tc->perm, tc->len);
}
EXPORT void TranspositionCipher_data(TranspositionCipher *tc, char *out) {
	memcpy(out, tc->data, sizeof(char) * tc->len);
}
EXPORT unsigned int TranspositionCipher_len(TranspositionCipher *tc) {
	return tc->len;
}
EXPORT void TranspositionCipher_perm(TranspositionCipher *tc, unsigned int *out) {
	memcpy(out, tc->perm, sizeof(unsigned int) * tc->len);
}
EXPORT void TranspositionCipher_apply_char(TranspositionCipher *tc, char *in, unsigned int len, char *out) {
	for (unsigned int i = 0; i < len; ++i) {
		out[i] = in[tc->perm[i]];
	}
}
EXPORT void TranspositionCipher_apply_int(TranspositionCipher *tc, int *in, unsigned int len, int *out) {
	for (unsigned int i = 0; i < len; ++i) {
		out[i] = in[tc->perm[i]];
	}
}
EXPORT void TranspositionCipher_apply_uint(TranspositionCipher *tc, unsigned int *in, unsigned int len, unsigned int *out) {
	for (unsigned int i = 0; i < len; ++i) {
		out[i] = in[tc->perm[i]];
	}
}
EXPORT void TranspositionCipher_apply(TranspositionCipher *tc, char *out) {
	TranspositionCipher_apply_char(tc, tc->data, tc->len, out);
}

EXPORT TranspositionCipher *TranspositionCipher_mul(TranspositionCipher *a, TranspositionCipher *b) {
	TranspositionCipher *c = TranspositionCipher_new(a->data, a->len);
	TranspositionCipher_apply_uint(a, b->perm, (a->len > b->len ? b : a)->len, c->perm);
	return c;
}
EXPORT TranspositionCipher *TranspositionCipher_inv(TranspositionCipher *a) {
	TranspositionCipher *b = TranspositionCipher_new(a->data, a->len);
	for (unsigned int i = 0; i < a->len; i++) {
		b->perm[a->perm[i]] = i;
	}
	return b;
}
EXPORT TranspositionCipher *TranspositionCipher_pow(TranspositionCipher *a, int b) { // TODO: remove unnecessary data copying
	if (b < 0) {
		TranspositionCipher *c = TranspositionCipher_inv(a);
		TranspositionCipher *d = TranspositionCipher_pow(c, -b);
		TranspositionCipher_delete(c);
		return d;
	} else if (b > 0) {
		TranspositionCipher *c = TranspositionCipher_new(a->data, a->len);
		TranspositionCipher_setPerm(c, a->perm, a->len);
		unsigned int rev = 0;
		while (b) {
			rev = (rev | (b & 1)) << 1;
			b >>= 1;
		}
		for (rev >>= 1; rev; rev >>= 1) {
			if (rev & 1) {
				TranspositionCipher *d = TranspositionCipher_mul(c, a);
				free(c);
				c = d;
			}
			TranspositionCipher *e = TranspositionCipher_mul(c, c);
			free(c);
			c = e;
		}
		return c;
	} else {
		TranspositionCipher *c = TranspositionCipher_new(a->data, a->len);
		TranspositionCipher_setIdentity(c);
		return c;
	}
}

typedef struct LinkedNode LinkedNode;
struct LinkedNode {
	char *key;
	unsigned int off;
	LinkedNode *next;
};
LinkedNode *make_linked_node(unsigned int keysize) {
	LinkedNode *ln = (LinkedNode *)malloc(sizeof(LinkedNode));
	ln->key = (char *)malloc(sizeof(char) * keysize);
	memset(ln->key, 0, sizeof(char) * keysize);
	ln->off = 0;
	ln->next = NULL;
	return ln;
}
LinkedNode *cpy_linked_node(LinkedNode *ln, unsigned int keysize) {
	LinkedNode *ln2 = (LinkedNode *)malloc(sizeof(LinkedNode));
	ln2->key = (char *)malloc(sizeof(char) * keysize);
	memcpy(ln2->key, ln->key, sizeof(char) * keysize);
	ln2->off = ln->off;
	ln2->next = ln->next;
	return ln2;
}
LinkedNode *advance_linked_node(LinkedNode *ln, unsigned int keysize, unsigned int keypos, unsigned int skip, unsigned int datalen) {
	LinkedNode *ln2 = (LinkedNode *)malloc(sizeof(LinkedNode));
	ln2->key = (char *)malloc(sizeof(char) * keysize);
	memcpy(ln2->key, ln->key, sizeof(char) * keysize);
	ln2->key[keypos] = skip + ('A'-2);
	ln2->off = ln->off + skip % datalen;
	ln2->next = NULL;
	return ln2;
}
void delete_linked_node(LinkedNode *ln) {
	free(ln->key);
	free(ln);
}
EXPORT LinkedNode *pop_linked_node(LinkedNode *ln) {
	LinkedNode *retval = ln->next;
	delete_linked_node(ln);
	return retval;
}
EXPORT int hasnext_linked_node(LinkedNode *ln) {
	return ln->next != NULL;
}
EXPORT char *getkey_linked_node(LinkedNode *ln) {
	return ln->key;
}
EXPORT unsigned int getoff_linked_node(LinkedNode *ln) {
	return ln->off;
}
void delete_linked_list(LinkedNode *ln) {
	while (ln != NULL) {
		free(ln->key);
		LinkedNode *next = ln->next;
		free(ln);
		ln = next;
	}
}
LinkedNode *linked_list_deep_copy(LinkedNode *list, LinkedNode **cpy, unsigned int keysize) {
	*cpy = cpy_linked_node(list, keysize);
	LinkedNode *cpyit = *cpy;
	for (LinkedNode *it = list->next; it != NULL; it = it->next) {
		cpyit->next = cpy_linked_node(it, keysize);
		cpyit = cpyit->next;
	}
	return cpyit;
}
EXPORT unsigned int humanscantsolvethis_keys_from_result(const char *data, unsigned int datalen, const char *result, unsigned int resultlen,
	unsigned int *offsets, unsigned int offsetslen, LinkedNode **out) {
	LinkedNode *list = make_linked_node(resultlen);
	list->off = offsets[0] - 1;
	LinkedNode *list_last = list;
	LinkedNode *list_cpy = NULL;
	unsigned int *offsets_end = offsets + offsetslen;
	for (unsigned int *i = offsets + 1; i != offsets_end; i++) {
		list_last->next = make_linked_node(resultlen);
		list_last = list_last->next;
		list_last->off = *i - 1;
	}
	unsigned int prev_gen = offsetslen;
	for (unsigned int ri = 0; ri < resultlen; ri++) {
		unsigned int gen = 0;
		linked_list_deep_copy(list, &list_cpy, resultlen);
		for (unsigned int counter = 0; counter < prev_gen; list = pop_linked_node(list), counter++) {
			for (unsigned int skip = 2; skip <= 28; skip++) {
				if (data[(list->off + skip) % datalen] == result[ri]) {
					list_last->next = advance_linked_node(list, resultlen, ri, skip, datalen);
					list_last = list_last->next;
					gen++;
				}
			}
		}
		if (resultlen > 15) {
			fprintf(stderr, "[key rev]: %u letters done (%c); %u results\n", ri+1, result[ri], gen);
		}
		if (gen == 0) {
			delete_linked_list(list);
			*out = list_cpy;
			return ri;
		}
		prev_gen = gen;
		delete_linked_list(list_cpy);
	}
	*out = list;
	return resultlen;
}

#ifdef __cplusplus
}
#endif
