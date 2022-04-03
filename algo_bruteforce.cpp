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

#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>

// TODO: add support for testing multiple keys

constexpr const char data1[] = "Nw;:OPxPo st;AEp fbwpe  idIosEtn TnipeMp H ui;zcE ntcrATsHrhUtxHRW   CCsoo( reEMantTtOafStNOBxaIEtARorYATHa trOBuQtx(NCPshtMUt:NpsvLdA aSeNIrUeeAee rsALs|iCeNhEss;apTbtiA;stlAaer)t tOL7P t: s  NotA SsTttdeE' WL kTv puLDSifANr7oiReiS aeytforoMfctt)dlHOsA n;slDRWYdp rtDssLUS)t;SIkC; ac;oteiVH Wi jfidlR; 7udsRE s uDEtoE|lSeT;LcVTlHCSaAd( hnI  zorkHIcpSEeCoAecenEe UyIlNeot;t Tc eEA  KISKi  H t sDxsttn;MhSUi' KAORNtxotTeAE O spAAeOe ets l OCgBt AetbTeHm)ao|iRIiElt YaDnhtBTlhCGeSwTGbn ncLyFthyO N xdTCDeirnyhstAU T(:SOEs lyTEjMsePup lstkRnnpyndUieIe)rF fr6SttTaHfI;Ne Oh:pAc TiMenE s h)esLsbs roOll VcnwLTO;nhKTsnePmUN;UusHdusDt l B Ho72EyMNuRoy znm dwEs IEiAxtteCrwee MeRen ;iB OstnAtL(NroEtwe| (t:se hyniEdr;iKsnt Ee;ooeSoEdug iu Rd H ddCaLSPC ADiiAYA";
constexpr const char key2[] = "HUMANSCANTSOLVETHISSOBETTERSTOPHERE";
constexpr const char data2[] = "at iatutsSfo e tT RSdsnaEcuNtseeLoEnoxxeh tAc oRHS; x iwDTUNen deetHOIECICraP e ;dSol Ot|GiMe: UytAEiYe; BPeb voY;sAc ie)Gesrc H M|eS;MHfuITsLMtWEzesAAt  epldn :Ei  eAseLLfp |ktnpmbslHseue SiicntatoNHCs(Ut Tett;ssw d s Crvs fA u  he yEf so;ndturaUsdeDlCeDAitlr);snn ohO:EAiWjl teax  wow   TaMNSis ncAe : sDx( psNpAEt;lo sBAisuAtdpxYetiR;rKEtnn sCiC  (|tttVtNo yhleswiSA)7SEe'bOnL Bo trLelicHgysn7tudotlrtLEshe tOgttd oipMaUfKr;waN:duEtlurys;RhOf7y nITiontsDaIKTkLeupHtr At ARisRiyDIHOV aHLWkClheICre   ldmtbO )A PTwps R ne AtrUoDT AEsH;Nnozslehh(erDTFOK teAFnn;cRpE ;tOOrORNTMcTdh2E'I(LTnobAphj NcyyAa6Pk NEiSN Ir7CNSYRdt KEo)TexEETiSPUoCeBO zLIUtU;lhPQrCAIi tBWsdM;";
constexpr const char key3[] = "DLIHCREHTONMAITUBREHTOMYMSIEHS";
constexpr const char key3r[] = "SHEISMYMOTHERBUTIAMNOTHERCHILD";
constexpr const char data3[] = "AtniotoMK;hHLt hOT(NSCCiMs  aEeMifpCesul)t: su|'yhlRtsW ;tFpb7t actt lbA  L|c  Ar:SlihA7Eof kh rK;LSPrfdswdrBrHekblUytasxKsnc 7uAROslOyELt SSUC;G Amu snOaACtrutyreebN;TPx thNIteelset;seis;  drs  nDdEpdltueUc And o c dyS7tdTlwFcA TItiePoA:(slpr(ltefKaIeeR  EdN;AvtetEE psottTCTEaCoAa IyYfsnouotsbUti sAkSetL;iui hNpnedped nIhcetx ;ttAeN lsytTnhKtD EeiaexRELityHU'Uux )e UMVr NVhtYiHc  rj Blu;Oe rN e pdsYNHIDo6NeS: D OOAlnn aC TC f So RPoGMsntsan EI LtE anoOiEeP    wDThxdt;CLp)eoEHo arS;wrwgiABeRzwAsue evirjOotiimo;L L( NEwros|oIpNiWeisoin;AiOAit2EQnyUlzsR TWRn rfCAeBEO ks PTW in|sngscthezHt eD)";
constexpr const char data3r[] = ")De tHzehtcsgns|ni WTP sk OEBeACfr nRWT RszlUynQE2tiAOiA;niosieWiNpIo|sorwEN (L L;omiitoOjrive eusAwzReBAigwrw;Sra oHEoe)pLC;tdxhTDw    PeEiOona EtL IE nastnsMGoPR oS f CT Ca nnlAOO D :SeN6oDIHNYsdp e Nr eO;ulB jr  cHiYthVN rVMU e) xuU'UHytiLERxeaieE DtKhnTtysl NeAtt; xtechIn depdenpNh iui;LteSkAs itUbstouonsfYyI aAoCaETCTttosp EEtetvA;NdE  ReeIaKfetl(rpls(:AoPeitIT AcFwlTdt7Syd c o dnA cUeutldpEdDn  srd  ;sies;tesleetINht xPT;NbeeryturtCAaOns umA G;CUSS tLEyOlsORAu7 cnsKxsatyUlbkeHrBrdwsdfrPSL;Kr hk foE7AhilS:rA  c|L  Abl ttca t7bpFt; WstRlhy'|us :t)luseCpfiMeEa  sMiCCSN(TOh tLHh;KMotointA";
#define data data3
#define key key3
template<int N>
constexpr int const_strlength(char const (&)[N]) { return N-1; }
constexpr int datalen = const_strlength(data);
constexpr int keylen = const_strlength(key);

//#define INV_ALGO

enum class operation {
	CONST, VAR, REV, ADD, MULT, COUNT
};
enum class variable {
	INDEX, KEYINDEX, KEY, KEYLEN, DATA, DATALEN, COUNT
};
struct algo_context {
	int index;
	int keyindex;
	std::string d;
};
class expr {
public:
	expr *a;
	expr *b;
	int constant;
	variable var;
	operation op;

	expr() : a(nullptr), b(nullptr), constant(0), op(operation::CONST) { }
	expr(variable v) : a(nullptr), b(nullptr), constant(0), var(v), op(operation::VAR) { }
	expr(int c) : a(nullptr), b(nullptr), constant(c), op(operation::CONST) { }
	expr(const expr &f, operation o) : b(nullptr), constant(0), op(o) {
		a = new expr(f);
	}
	expr(const expr &f, const expr &f2, operation o) : constant(0), op(o) {
		a = new expr(f);
		b = new expr(f2);
	}
	expr(expr *f, operation o) : a(f), b(nullptr), constant(0), op(o) { }
	expr(expr *f, expr *f2, operation o) : a(f), b(f2), constant(0), op(o) { }
	expr(const expr &f) : constant(f.constant), var(f.var), op(f.op) {
		a = f.a == nullptr ? nullptr : new expr(*f.a);
		b = f.b == nullptr ? nullptr : new expr(*f.b);
	}
	~expr() {
		if (a != nullptr) delete a;
		if (b != nullptr) delete b;
	}
	int get(const algo_context &c) {
		switch (op) {
		case operation::CONST: return constant;
		case operation::VAR:
			switch (var) {
			case variable::DATA: return c.d[c.index];
			case variable::DATALEN: return c.d.size();
			case variable::INDEX: return c.index;
			case variable::KEY: return key[c.keyindex]-'@';
			case variable::KEYINDEX: return c.keyindex;
			case variable::KEYLEN: return keylen;
			default: return 0;
			}
		case operation::REV: return -a->get(c);
		case operation::ADD: return a->get(c) + b->get(c);
		case operation::MULT: return a->get(c) * b->get(c);
		default: return 0;
		};
	}
};
std::ostream &operator<<(std::ostream &o, const expr &e) {
	switch (e.op) {
	case operation::CONST: o << e.constant; break;
	case operation::VAR:
		switch (e.var) {
		case variable::DATA: o << "data[index]"; break;
		case variable::DATALEN: o << "len(data)"; break;
		case variable::INDEX: o << "index"; break;
		case variable::KEY: o << "key[keyindex]"; break;
		case variable::KEYINDEX: o << "keyindex"; break;
		case variable::KEYLEN: o << "len(key)"; break;
		default: break;
		}
		break;
	case operation::REV: o << "-" << *e.a; break;
	case operation::ADD: o << "(" << *e.a << "+" << *e.b << ")"; break;
	case operation::MULT: o << "(" << *e.a << "*" << *e.b << ")"; break;
	default: break;
	};
	return o;
}
class algo {
public:
	int start_index;
	int start_keyindex;
	expr *index_expr;
	expr *keyindex_expr;

	algo(int si, int ski, expr *i, expr *ki) : start_index(si), start_keyindex(ski), index_expr(i), keyindex_expr(ki) { }
	~algo() {
		delete index_expr;
		delete keyindex_expr;
	}
	std::string run() {
#ifdef INV_ALGO
		algo_context ctx;
		ctx.index = start_index;
		ctx.keyindex = start_keyindex;
		std::string res(datalen, '-');
		const char *c;
		for (c = data; *c; ++c) {
			int step = index_expr->get(ctx);
			step %= res.size()-(c-data);
			if (step > 0) {
				while (step) {
					ctx.index = (ctx.index + 1) % res.size();
					if (res[ctx.index] == '-') {
						step--;
					}
				}
			} else if (step < 0) {
				while (step) {
					ctx.index = (ctx.index - 1 + res.size()) % res.size();
					if (res[ctx.index] == '-') {
						step++;
					}
				}
			} else {
				return res;
			}
			ctx.keyindex = keyindex_expr->get(ctx);
			while (ctx.keyindex < 0) { ctx.keyindex += keylen; }
			ctx.keyindex %= keylen;
			res[ctx.index] = *c;
		}
		return res;
#else
		algo_context ctx;
		ctx.index = start_index;
		ctx.keyindex = start_keyindex;
		ctx.d = data;
		std::string res;
		res.reserve(datalen);
		while (!ctx.d.empty()) {
			ctx.index = index_expr->get(ctx);
			while (ctx.index < 0) { ctx.index += ctx.d.size(); }
			ctx.index %= ctx.d.size();
			ctx.keyindex = keyindex_expr->get(ctx);
			while (ctx.keyindex < 0) { ctx.keyindex += keylen; }
			ctx.keyindex %= keylen;
			res.push_back(ctx.d[ctx.index]);
			ctx.d.erase(ctx.index, 1);
		}
		return res;
#endif
	}
};
std::ostream &operator<<(std::ostream &o, const algo &a) {
#ifdef INV_ALGO
	o << "def algo(data, key):\n"
		"	key=[ord(c)-64 for c in key]\n"
		"	index=" << a.start_index << "\n"
		"	keyindex=" << a.start_keyindex << "\n"
		"	res='-'*len(data)\n"
		"	for char in data:\n"
		"		skip=" << *a.index_expr << "\n"
		"		if skip > 0:\n"
		"			while skip > 0\n"
		"				index=(index+1)%len(data)\n"
		"				if res[index] == '-':\n"
		"					skip -= 1\n"
		"		elif skip < 0:\n"
		"			while skip < 0\n"
		"				index=(index-1+len(data))%len(data)\n"
		"				if res[index] == '-':\n"
		"					skip += 1\n"
		"		else:\n"
		"			return res\n"
		"		index%=len(data)\n"
		"		keyindex=" << *a.keyindex_expr << "\n"
		"		while keyindex < 0: keyindex+=len(key)\n"
		"		keyindex%=len(key)\n"
		"		res[index]=char\n"
		"	return res";
#else
	o << "def algo(data, key):\n"
		"	key=[ord(c)-64 for c in key]\n"
		"	index=" << a.start_index << "\n"
		"	keyindex=" << a.start_keyindex << "\n"
		"	res=''\n"
		"	while data:\n"
		"		index=" << *a.index_expr << "\n"
		"		while index < 0: index+=len(data)\n"
		"		index%=len(data)\n"
		"		keyindex=" << *a.keyindex_expr << "\n"
		"		while keyindex < 0: keyindex+=len(key)\n"
		"		keyindex%=len(key)\n"
		"		res+=data[index]\n"
		"		data=data[:index]+data[index+1:]\n"
		"	return res";
#endif
	return o;
}
bool ismsg(const std::string &msg) {
	size_t pos = msg.find("DATA(", 0);
	return pos != std::string::npos;
	//if (pos == std::string::npos)
	//	return false;
	//;
}
#define R(n) (rand()%(n))
expr *randLeaf() {
	if (R(10)) {
		return new expr(R(41)-20);
	} else {
		constexpr variable vars[] = { variable::INDEX, variable::KEYINDEX, variable::KEY };
		constexpr int varc = 3;
		return new expr(vars[R(varc)]);
	}
}
expr *randExpr(expr *base) {
	int count = R(4);
	constexpr operation binops[] = { operation::ADD, operation::MULT, operation::ADD };
	constexpr operation unops[] = { operation::REV };
	constexpr int binoplen = 3;
	constexpr int unoplen = 1;
	constexpr int sumlen = binoplen + unoplen;
	for (int i = 0; i < count; ++i) {
		int op = R(sumlen);
		if (op < binoplen) {
			expr *leaf = randLeaf();
			if (!R(4)) {
				leaf = new expr(leaf, unops[R(unoplen)]);
			}
			if (!R(7)) {
				leaf = new expr(leaf, randLeaf(), binops[R(binoplen)]);
			}
			base = new expr(base, leaf, binops[op]);
		} else {
			base = new expr(base, unops[op-binoplen]);
		}
	}
	return base;
}
algo randAlgo() {
#ifdef INV_ALGO
	return algo(R(2) * R(datalen), R(2) * R(keylen), randExpr(randLeaf()), randExpr(new expr(variable::KEYINDEX)));
#else
	return algo(R(2) * R(datalen), R(2) * R(keylen), randExpr(new expr(variable::INDEX)), randExpr(new expr(variable::KEYINDEX)));
#endif
}
#undef R
int main() {
	srand(time(NULL));
	//algo a1(0, 0, new expr(new expr(variable::INDEX), new expr(17), operation::ADD), new expr(0));
	//algo a2(0, 0, new expr(new expr(variable::INDEX), new expr(variable::KEY), operation::ADD),
	//	new expr(new expr(variable::KEYINDEX), new expr(1), operation::ADD));
	//std::cout << a2 << std::endl;
	for (unsigned long int i = 0; ; ++i) {
		algo a = randAlgo();
		std::string res = a.run();
		if (ismsg(res)) {
			std::cout << "==================================== FOUND ====================================" << std::endl <<
				a << std::endl << "-------------- out ------------------" << std::endl << res << std::endl;
		}
		if (i%100000==0) {
			std::cout << (i/1000000.f) << "m algos searched" << std::endl;
		}
	}
	return 0;
}
