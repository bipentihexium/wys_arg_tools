/*
MIT License

Copyright (c) 2022 bipentihexium

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *data = "e;R cNsRtOs;;eE OanYti tieSCC Kd eNTT oxShNsteL emeif;pnlO Ka u TnAtTfdLe UTI;o irf lr EuytwHtte onirruEoLh yeltztl  OHSinpstUwA As L AfiMiNBlwsvnRrpTeEM:tyiIaNNsLUeeOTidPon  p DQt; i6inbADNeNFHAloltA BoieScney MI;EoEn otnoBDkWosB udtL lAs OEn yCogVrHnbsAwt  YrpOed s;oaIilteb7klaauL hsiW loFdUen))YsLOU aE  R tsIAdWes;esA tltopAyhr:bKyt( e hMiePaHAacShiRzSA rSsv umteTswe(Mn fVDNUtUwOtshrACh";
unsigned int datalen;
char *datacpy;
char *buff;

void removechar(char *arr, unsigned int len, unsigned int i) {
	char *end = arr + len - 1;
	for (char *it = arr + i; it != end; it++) {
		*it = it[1];
	}
}
void humanscantsolvethis_decrypt(char *data, unsigned int datalen, char *key, unsigned int keylen, char *out) {
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
int is_message(char *msg) {
	return strstr(msg, "; DATA(") != 0; // && strstr(msg, "passed;") != 0;
}
void try_keys(char *kstart, char *kcurr, unsigned int depth) {
	if (depth > 1) {
		for (char c = 'A'; c <= 'Z'; c++) {
			*kcurr = c;
			try_keys(kstart, kcurr+1, depth-1);
		}
	} else {
		for (char c = 'A'; c <= 'Z'; c++) {
			*kcurr = c;
			memcpy(datacpy, data, sizeof(char) * datalen);
			humanscantsolvethis_decrypt(datacpy, datalen, kstart, kcurr - kstart + 1, buff);
			if (is_message(buff)) {
				printf("%s: %s\n", kstart, buff);
			}
		}
	}
}

int main() {
	datalen = strlen(data);
	datacpy = (char *)malloc(sizeof(char) * (datalen));
	buff = (char *)malloc(sizeof(char) * (datalen + 1));
	buff[datalen] = '\0';
	char key[50] = { '\0' };
	for (unsigned int i = 1; i < 50; i++) {
		printf("searching depth: %d\n", i);
		try_keys(key, key, i);
	}
	free(datacpy);
	free(buff);
	return 0;
}
