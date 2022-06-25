#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <array>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

//constexpr const char *data = "e;R cNsRtOs;;eE OanYti tieSCC Kd eNTT oxShNsteL emeif;pnlO Ka u TnAtTfdLe UTI;o irf lr EuytwHtte onirruEoLh yeltztl  OHSinpstUwA As L AfiMiNBlwsvnRrpTeEM:tyiIaNNsLUeeOTidPon  p DQt; i6inbADNeNFHAloltA BoieScney MI;EoEn otnoBDkWosB udtL lAs OEn yCogVrHnbsAwt  YrpOed s;oaIilteb7klaauL hsiW loFdUen))YsLOU aE  R tsIAdWes;esA tltopAyhr:bKyt( e hMiePaHAacShiRzSA rSsv umteTswe(Mn fVDNUtUwOtshrACh";
constexpr const char *data = "IvTuitn tat  eHenoEi pgvi IATf nAOiM pLl ssyGnelnu l(Eeo seIthHNc;YARsL oeeoEilnBst( elth dylarxtlSAPa YbSpNR'UrslCPth;B LiyROsoMpsF SrasCIssn KNEALhATih o  atowrstzCnisuhcAHKAm  ecIREftNsUMiNnan HeosirhHSs;AdtuuNpodpEo;pey r6T )rs(isg tyAi;sse;tFeCtutEj Soewuoe tMNR B Sedcl C KxeeCOxai; tnitLlLy tetncU OO ijwEiC:b7O;eUithx VOodAr )Tu xbsc:onD Nn tpsot KSeo;ae)DMEw2z tf EyfotdanrAeetwu7dIeB ;mnh:bA slu t WL ketAtlDnk;rNlU ILWeW7 iiDwUlnrTeEiolttdYT OtwEeDbUe i h HNfrAfc dVQdk ArzTOLarA if kye; tN sTLys oTd";
constexpr unsigned int datalen = strlen(data);

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
	return msg[datalen-1] == ')' && strstr(msg, "; DATA(") != 0;
}
void try_keys(char *kstart, char *kcurr, unsigned int depth) {
	if (depth > 1) {
		for (char c = 'A'; c <= 'Z'; c++) {
			*kcurr = c;
			try_keys(kstart, kcurr+1, depth-1);
		}
	} else {
		char *datacpy;
		char *buff;
		datacpy = (char *)malloc(sizeof(char) * (datalen));
		buff = (char *)malloc(sizeof(char) * (datalen + 1));
		buff[datalen] = '\0';
		for (char c = 'A'; c <= 'Z'; c++) {
			*kcurr = c;
			memcpy(datacpy, data, sizeof(char) * datalen);
			humanscantsolvethis_decrypt(datacpy, datalen, kstart, kcurr - kstart + 1, buff);
			if (is_message(buff)) {
				printf("%s: %s\n", kstart, buff);
			}
		}
		free(datacpy);
		free(buff);
	}
}
constexpr unsigned int no_threads = 3;
constexpr char starts[] = { 'A', 'J', 'S' };
constexpr char ends[] = { 'I', 'R', 'Z' };
unsigned int threads_left;
void search(unsigned int id, unsigned int depth) {
	char key[50] = { '\0' };
	for (char c = starts[id]; c <= ends[id]; c++) {
		key[0] = c;
		try_keys(key, key + 1, depth - 1);
	}
	printf("thread %d finished (%d left)\n", id, --threads_left);
}
int main() {
	for (unsigned int i = 1; i < 50; i++) {
		printf("searching depth: %d\n", i);
		std::array<std::unique_ptr<std::thread>, no_threads> threads;
		threads_left = no_threads;
		for (unsigned int j = 0; j < no_threads; j++) {
			threads[j] = std::unique_ptr<std::thread>(new std::thread(search, j, i));
		}
		while (threads_left) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		printf("searched depth: %d\n", i);
		for (auto &thr : threads) {
			thr->join();
		}
	}
}
