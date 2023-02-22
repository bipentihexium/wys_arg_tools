#include <string.h>
#include <algorithm>
#include <experimental/iterator>
#include <deque>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

// L5
constexpr const char *data = "e;R cNsRtOs;;eE OanYti tieSCC Kd eNTT oxShNsteL emeif;pnlO Ka u TnAtTfdLe UTI;o irf lr EuytwHtte onirruEoLh yeltztl  OHSinpstUwA As L AfiMiNBlwsvnRrpTeEM:tyiIaNNsLUeeOTidPon  p DQt; i6inbADNeNFHAloltA BoieScney MI;EoEn otnoBDkWosB udtL lAs OEn yCogVrHnbsAwt  YrpOed s;oaIilteb7klaauL hsiW loFdUen))YsLOU aE  R tsIAdWes;esA tltopAyhr:bKyt( e hMiePaHAacShiRzSA rSsv umteTswe(Mn fVDNUtUwOtshrACh";
// L4
//constexpr const char *data = "IvTuitn tat  eHenoEi pgvi IATf nAOiM pLl ssyGnelnu l(Eeo seIthHNc;YARsL oeeoEilnBst( elth dylarxtlSAPa YbSpNR'UrslCPth;B LiyROsoMpsF SrasCIssn KNEALhATih o  atowrstzCnisuhcAHKAm  ecIREftNsUMiNnan HeosirhHSs;AdtuuNpodpEo;pey r6T )rs(isg tyAi;sse;tFeCtutEj Soewuoe tMNR B Sedcl C KxeeCOxai; tnitLlLy tetncU OO ijwEiC:b7O;eUithx VOodAr )Tu xbsc:onD Nn tpsot KSeo;ae)DMEw2z tf EyfotdanrAeetwu7dIeB ;mnh:bA slu t WL ketAtlDnk;rNlU ILWeW7 iiDwUlnrTeEiolttdYT OtwEeDbUe i h HNfrAfc dVQdk ArzTOLarA if kye; tN sTLys oTd";
constexpr const char *filter = "DATA(";
constexpr size_t filter_len = strlen(filter);
constexpr size_t key_base[] = {
	9,14,20,5,12,12,9,7,5,14,3,5,3,8,5,3,11 // INTELLIGENCECHECK
	//24,4,25,15,25,15,25 // XDYOYOY
};

template<typename IT>
std::string decrypt(IT key_begin, IT key_end) {
	std::string data_cpy(data);
	std::string out; out.reserve(data_cpy.size());
	size_t at = 0;
	IT key_it = key_begin;
	for (size_t i = 0; data_cpy.size() > 0; i++) {
		at = (at + static_cast<size_t>(*key_it % static_cast<int>(data_cpy.size()) + data_cpy.size())) % data_cpy.size();
		if (++key_it == key_end) { key_it = key_begin; }
		out.push_back(data_cpy[at]);
		data_cpy.erase(data_cpy.begin() + at);
	}
	return out;
}

template<typename IT>
size_t matches_filter(IT key_begin, IT key_end) {
	std::string data_cpy(data);
	std::deque<char> decrypted_buff;
	size_t at = 0;
	IT key_it = key_begin;
	for (size_t i = 1; data_cpy.size() > 0; i++) {
		at = (at + static_cast<size_t>(*key_it % static_cast<int>(data_cpy.size()) + data_cpy.size())) % data_cpy.size();
		if (++key_it == key_end) { key_it = key_begin; }
		decrypted_buff.push_back(data_cpy[at]);
		if (decrypted_buff.size() >= filter_len) {
			if (decrypted_buff.size() > filter_len)
				decrypted_buff.pop_front();
			const char *filter_it = filter;
			for (const auto &c : decrypted_buff) {
				if (*(filter_it++) != c) {
					goto check_failed;
				}
			}
			return i-filter_len;
		}
	check_failed:
		data_cpy.erase(data_cpy.begin() + at);
	}
	return static_cast<size_t>(-1);
}

constexpr const unsigned int op_id_count = 4;
constexpr char op_repr[] = {
	'~', '+', '*', '%'
};
constexpr int op_n_ranges[] = {
	0, 1,
	-30, 31,
	-30, 31,
	2, 31,
};
constexpr unsigned int op_mask[] = {
	0b1110,
	0b1101,
	0b1011,
	0b0111,
};
constexpr unsigned int op_unmask[] = {
	0b0000,
	0b1100,
	0b1010,
	0b0110,
};

void modify(std::vector<int> &k, unsigned int op_id, unsigned int n) {
	switch (op_id) {
	case 0: std::reverse(k.begin(), k.end()); break;
	case 1: std::for_each(k.begin(), k.end(), [n](int &x) { x += n; }); break;
	case 2: std::for_each(k.begin(), k.end(), [n](int &x) { x *= n; }); break;
	default: break;
	}
}

std::unordered_set<std::string> found;

template<typename IT>
void do_search(IT k_begin, IT k_end, std::vector<unsigned int> &ops, std::vector<int> &ns, unsigned int depth, unsigned int mask) {
	for (unsigned int op_id = 0; op_id < op_id_count; op_id++) {
		if (mask & (1u << op_id)) {
			for (int n = op_n_ranges[2*op_id]; n < op_n_ranges[2*op_id+1]; n++) {
				ops[ops.size() - depth] = op_id;
				ns[ns.size() - depth] = n;
				std::vector<int> kcpy(k_begin, k_end);
				modify(kcpy, op_id, n);
				if (depth == 1) {
					size_t match = matches_filter(kcpy.begin(), kcpy.end());
					if (match != static_cast<size_t>(-1)) {
						std::string decr(decrypt(kcpy.begin(), kcpy.end()));
						std::cout << "\x1b[1m\x1b[96mhit at " << match << "! {";
						for (size_t i = 0; i < ops.size(); i++) {
							std::cout << op_repr[ops[i]] << '(' << ns[i] << ')' << (i == ops.size() - 1 ? "" : ", ");
						}
						if (found.contains(decr)) {
							std::cout << "}\x1b[0m - \x1b[91m<found already>\x1b[0m" << std::endl;
						} else {
							found.insert(decr);
							std::cout << "} -> {";
							std::copy(kcpy.begin(), kcpy.end(), std::experimental::make_ostream_joiner(std::cout, ", "));
							std::cout << "}: \x1b[0m" << '"' << decr.substr(0, match) << "\x1b[1m\x1b[92m" << decr.substr(match, filter_len) << "\x1b[0m" <<
								decr.substr(match + filter_len) << '"' << std::endl;
						}
					}
				} else {
					do_search(kcpy.begin(), kcpy.end(), ops, ns, depth - 1, (mask & op_mask[op_id]) | op_unmask[op_id]);
				}
			}
		}
	}
}

int main() {
	std::cout << decrypt(std::begin(key_base), std::end(key_base)) << std::endl;
	std::cout << matches_filter(std::begin(key_base), std::end(key_base)) << std::endl;
	std::vector<unsigned int> ops;
	std::vector<int> ns;
	for (unsigned int depth = 1; ; depth++) {
		std::cout << "searching depth " << depth << "! Good luck!\n";
		ops.push_back(0);
		ns.push_back(0);
		do_search(std::begin(key_base), std::end(key_base), ops, ns, depth, ~0b0);
	}
	return 0;
}
