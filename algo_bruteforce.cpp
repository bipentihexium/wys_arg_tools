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

#include <array>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>

// nubmer of search threads - usually used processor cores
constexpr int no_threads = 2;
// how much algorithms need to be searched to print the count
constexpr unsigned long int searchprint = 100000ul;
// precision of "Nm algorithms searched..."
constexpr unsigned searched_count_precision = 1;
// precision of "...avg search speed Nm/s"
constexpr unsigned search_time_precision = 2;
// precision of "...avg search speed Nm/s"
constexpr unsigned search_speed_precision = 3;
// string that is searched for when checking if result is message
constexpr const char *message_string = "; DATA(";
// put your data here
constexpr const char data[] = "AtniotoMK;hHLt hOT(NSCCiMs  aEeMifpCesul)t: su|'yhlRtsW ;tFpb7t actt lbA  L|c  Ar:SlihA7Eof kh rK;LSPrfdswdrBrHekblUytasxKsnc 7uAROslOyELt SSUC;G Amu snOaACtrutyreebN;TPx thNIteelset;seis;  drs  nDdEpdltueUc And o c dyS7tdTlwFcA TItiePoA:(slpr(ltefKaIeeR  EdN;AvtetEE psottTCTEaCoAa IyYfsnouotsbUti sAkSetL;iui hNpnedped nIhcetx ;ttAeN lsytTnhKtD EeiaexRELityHU'Uux )e UMVr NVhtYiHc  rj Blu;Oe rN e pdsYNHIDo6NeS: D OOAlnn aC TC f So RPoGMsntsan EI LtE anoOiEeP    wDThxdt;CLp)eoEHo arS;wrwgiABeRzwAsue evirjOotiimo;L L( NEwros|oIpNiWeisoin;AiOAit2EQnyUlzsR TWRn rfCAeBEO ks PTW in|sngscthezHt eD)";
// uncomment this line if you want to check for ')' at the end when checking message
//#define CHECK_CLOSING_PAREN
// uncomment this line if you want to use HCSTSBSH encryption algorithm instead
//#define INV_ALGO
// comment this line if you want to disable expression optimizations (not reccommended)
#define EXPR_OPTI

// put your keys here
constexpr const char *keys[] = {
	"DLIHCREHTONMAITUBREHTOMYMSIEHS", "SHEISMYMOTHERBUTIAMNOTHERCHILD",
	//"HUMANSCANTSOLVETHISSOBETTERSTOPHERE", "EREHPOTSRETTEBOSSIHTEVLOSTNACSNAMUH",
	//"STEPMOTHER", "REHTOMPETS", "MATERFAMILIAS", "SAILIMAFRETAM", "MATRIARCH", "HCRAIRTAM",
};

/*
constexpr const char data1[] = "Nw;:OPxPo st;AEp fbwpe  idIosEtn TnipeMp H ui;zcE ntcrATsHrhUtxHRW   CCsoo( reEMantTtOafStNOBxaIEtARorYATHa trOBuQtx(NCPshtMUt:NpsvLdA aSeNIrUeeAee rsALs|iCeNhEss;apTbtiA;stlAaer)t tOL7P t: s  NotA SsTttdeE' WL kTv puLDSifANr7oiReiS aeytforoMfctt)dlHOsA n;slDRWYdp rtDssLUS)t;SIkC; ac;oteiVH Wi jfidlR; 7udsRE s uDEtoE|lSeT;LcVTlHCSaAd( hnI  zorkHIcpSEeCoAecenEe UyIlNeot;t Tc eEA  KISKi  H t sDxsttn;MhSUi' KAORNtxotTeAE O spAAeOe ets l OCgBt AetbTeHm)ao|iRIiElt YaDnhtBTlhCGeSwTGbn ncLyFthyO N xdTCDeirnyhstAU T(:SOEs lyTEjMsePup lstkRnnpyndUieIe)rF fr6SttTaHfI;Ne Oh:pAc TiMenE s h)esLsbs roOll VcnwLTO;nhKTsnePmUN;UusHdusDt l B Ho72EyMNuRoy znm dwEs IEiAxtteCrwee MeRen ;iB OstnAtL(NroEtwe| (t:se hyniEdr;iKsnt Ee;ooeSoEdug iu Rd H ddCaLSPC ADiiAYA";
constexpr const char key2[] = "HUMANSCANTSOLVETHISSOBETTERSTOPHERE";
constexpr const char data2[] = "at iatutsSfo e tT RSdsnaEcuNtseeLoEnoxxeh tAc oRHS; x iwDTUNen deetHOIECICraP e ;dSol Ot|GiMe: UytAEiYe; BPeb voY;sAc ie)Gesrc H M|eS;MHfuITsLMtWEzesAAt  epldn :Ei  eAseLLfp |ktnpmbslHseue SiicntatoNHCs(Ut Tett;ssw d s Crvs fA u  he yEf so;ndturaUsdeDlCeDAitlr);snn ohO:EAiWjl teax  wow   TaMNSis ncAe : sDx( psNpAEt;lo sBAisuAtdpxYetiR;rKEtnn sCiC  (|tttVtNo yhleswiSA)7SEe'bOnL Bo trLelicHgysn7tudotlrtLEshe tOgttd oipMaUfKr;waN:duEtlurys;RhOf7y nITiontsDaIKTkLeupHtr At ARisRiyDIHOV aHLWkClheICre   ldmtbO )A PTwps R ne AtrUoDT AEsH;Nnozslehh(erDTFOK teAFnn;cRpE ;tOOrORNTMcTdh2E'I(LTnobAphj NcyyAa6Pk NEiSN Ir7CNSYRdt KEo)TexEETiSPUoCeBO zLIUtU;lhPQrCAIi tBWsdM;";
constexpr const char key3[] = "DLIHCREHTONMAITUBREHTOMYMSIEHS";
constexpr const char key3r[] = "SHEISMYMOTHERBUTIAMNOTHERCHILD";
constexpr const char data3[] = "AtniotoMK;hHLt hOT(NSCCiMs  aEeMifpCesul)t: su|'yhlRtsW ;tFpb7t actt lbA  L|c  Ar:SlihA7Eof kh rK;LSPrfdswdrBrHekblUytasxKsnc 7uAROslOyELt SSUC;G Amu snOaACtrutyreebN;TPx thNIteelset;seis;  drs  nDdEpdltueUc And o c dyS7tdTlwFcA TItiePoA:(slpr(ltefKaIeeR  EdN;AvtetEE psottTCTEaCoAa IyYfsnouotsbUti sAkSetL;iui hNpnedped nIhcetx ;ttAeN lsytTnhKtD EeiaexRELityHU'Uux )e UMVr NVhtYiHc  rj Blu;Oe rN e pdsYNHIDo6NeS: D OOAlnn aC TC f So RPoGMsntsan EI LtE anoOiEeP    wDThxdt;CLp)eoEHo arS;wrwgiABeRzwAsue evirjOotiimo;L L( NEwros|oIpNiWeisoin;AiOAit2EQnyUlzsR TWRn rfCAeBEO ks PTW in|sngscthezHt eD)";
constexpr const char data3r[] = ")De tHzehtcsgns|ni WTP sk OEBeACfr nRWT RszlUynQE2tiAOiA;niosieWiNpIo|sorwEN (L L;omiitoOjrive eusAwzReBAigwrw;Sra oHEoe)pLC;tdxhTDw    PeEiOona EtL IE nastnsMGoPR oS f CT Ca nnlAOO D :SeN6oDIHNYsdp e Nr eO;ulB jr  cHiYthVN rVMU e) xuU'UHytiLERxeaieE DtKhnTtysl NeAtt; xtechIn depdenpNh iui;LteSkAs itUbstouonsfYyI aAoCaETCTttosp EEtetvA;NdE  ReeIaKfetl(rpls(:AoPeitIT AcFwlTdt7Syd c o dnA cUeutldpEdDn  srd  ;sies;tesleetINht xPT;NbeeryturtCAaOns umA G;CUSS tLEyOlsORAu7 cnsKxsatyUlbkeHrBrdwsdfrPSL;Kr hk foE7AhilS:rA  c|L  Abl ttca t7bpFt; WstRlhy'|us :t)luseCpfiMeEa  sMiCCSN(TOh tLHh;KMotointA";
*/
template<int N>
constexpr int const_strlength(char const (&)[N]) { return N-1; }
template<typename T, int N>
constexpr int const_arrlength(T const (&)[N]) { return N; }
constexpr int datalen = const_strlength(data);
constexpr int keycount = const_arrlength(keys);

enum class operation {
	CONSTANT, VAR, REV, ADD, MULT, COUNT
};
enum class variable {
	INDEX, KEYINDEX, KEY, KEYLEN, DATA, DATALEN, COUNT
};
struct algo_context {
	int index;
	int keyindex;
	std::string d;
	std::string k;
};
class expr;
std::ostream &operator<<(std::ostream &o, const expr &e);
bool valid(const expr &e);
void printExprDetail(const expr &e);
class expr {
public:
	expr *a;
	expr *b;
	int constant;
	variable var;
	operation op;

	/**
	 * @brief constructs empty expression
	 */
	expr() : a(nullptr), b(nullptr), constant(0), var(variable::INDEX), op(operation::CONSTANT) { }
	/**
	 * @brief constructs variable expression
	 */
	expr(variable v) : a(nullptr), b(nullptr), constant(0), var(v), op(operation::VAR) { }
	/**
	 * @brief constructs constant expression
	 */
	expr(int c) : a(nullptr), b(nullptr), constant(c), var(variable::INDEX), op(operation::CONSTANT) { }
	/**
	 * @brief constructs unary expression (from reference)
	 */
	expr(const expr &f, operation o) : b(nullptr), constant(0), var(variable::INDEX), op(o) {
		a = new expr(f);
	}
	/**
	 * @brief constructs binary expression (from references)
	 */
	expr(const expr &f, const expr &f2, operation o) : constant(0), var(variable::INDEX), op(o) {
		a = new expr(f);
		b = new expr(f2);
	}
	/**
	 * @brief constructs unary expression (from pointer, consumes it)
	 */
	expr(expr *f, operation o) : a(f), b(nullptr), constant(0), var(variable::INDEX), op(o) { }
	/**
	 * @brief constructs binary expression (from pointers, consumes them)
	 */
	expr(expr *f, expr *f2, operation o) : a(f), b(f2), constant(0), var(variable::INDEX), op(o) { }
	/**
	 * @brief copy constructor
	 */
	expr(const expr &f) : constant(f.constant), var(f.var), op(f.op) {
		a = f.a == nullptr ? nullptr : new expr(*f.a);
		b = f.b == nullptr ? nullptr : new expr(*f.b);
	}
	~expr() {
		if (a != nullptr) { delete a; }
		if (b != nullptr) { delete b; }
	}
	/**
	 * @brief gets value of expression in given context
	 */
	int get(const algo_context &c) const {
		switch (op) {
		case operation::CONSTANT: return constant;
		case operation::VAR:
			switch (var) {
			case variable::DATA: return c.d[c.index];
			case variable::DATALEN: return c.d.size();
			case variable::INDEX: return c.index;
			case variable::KEY: return c.k[c.keyindex]-'@';
			case variable::KEYINDEX: return c.keyindex;
			case variable::KEYLEN: return c.k.size();
			default: return 0;
			}
		case operation::REV: return -a->get(c);
		case operation::ADD: return a->get(c) + b->get(c);
		case operation::MULT: return a->get(c) * b->get(c);
		default: return 0;
		};
	}
	/**
	 * @brief attempts to optimize the expression
	 */
	void optimize() {
		switch (op) {
		case operation::REV:
			a->optimize();
			if (a->op == operation::CONSTANT) { // -const => const
				op = operation::CONSTANT;
				constant = -a->constant;
				delete a;
				a = nullptr;
			} else if (a->op == operation::REV) { // --x => x
				expr *inside = a->a;
				op = inside->op;
				constant = inside->constant;
				var = inside->var;
				expr *temp_a = inside->a == nullptr ? nullptr : new expr(*inside->a);
				b = inside->b == nullptr ? nullptr : new expr(*inside->b);
				delete a;
				a = temp_a;
			}
			break;
		case operation::ADD:
			a->optimize();
			b->optimize();
			if (a->op == operation::CONSTANT) {
				if (b->op == operation::CONSTANT) { // const + const => const
					op = operation::CONSTANT;
					constant = a->constant+b->constant;
					delete a;
					delete b;
					a = b = nullptr;
				} else if (b->op == operation::ADD) {
					if (b->a->op == operation::CONSTANT) { // const + (const + x) => const + x
						a->constant += b->a->constant;
						expr *temp_b = new expr(*b->b);
						delete b;
						b = temp_b;
					} else if (b->b->op == operation::CONSTANT) { // const + (x + const) => const + x
						a->constant += b->b->constant;
						expr *temp_b = new expr(*b->a);
						delete b;
						b = temp_b;
					}
				}
			} else if (b->op == operation::CONSTANT) {
				if (a->op == operation::ADD) {
					if (a->a->op == operation::CONSTANT) { // (const + x) + const => x + const
						b->constant += a->a->constant;
						expr *temp_a = new expr(*a->b);
						delete a;
						a = temp_a;
					} else if (a->b->op == operation::CONSTANT) { // (x + const) + const => x + const
						b->constant += a->b->constant;
						expr *temp_a = new expr(*a->a);
						delete a;
						a = temp_a;
					}
				}
			}
			break;
		case operation::MULT:
			a->optimize();
			b->optimize();
			if (a->op == operation::CONSTANT) {
				if (b->op == operation::CONSTANT) { // const * const => const
					op = operation::CONSTANT;
					constant = a->constant*b->constant;
					delete a;
					delete b;
					a = b = nullptr;
				} else if (b->op == operation::MULT) {
					if (b->a->op == operation::CONSTANT) { // const * (const * x) => const * x
						a->constant *= b->a->constant;
						expr *temp_b = new expr(*b->b);
						delete b;
						b = temp_b;
					} else if (b->b->op == operation::CONSTANT) { // const * (x * const) => const * x
						a->constant *= b->b->constant;
						expr *temp_b = new expr(*b->a);
						delete b;
						b = temp_b;
					}
				}
			} else if (b->op == operation::CONSTANT) {
				if (a->op == operation::MULT) {
					if (a->a->op == operation::CONSTANT) { // (const * x) * const => x * const
						b->constant *= a->a->constant;
						expr *temp_a = new expr(*a->b);
						delete a;
						a = temp_a;
					} else if (a->b->op == operation::CONSTANT) { // (x * const) * const => x * const
						b->constant *= a->b->constant;
						expr *temp_a = new expr(*a->a);
						delete a;
						a = temp_a;
					}
				}
			}
			break;
		default: break;
		};
	}
};
/**
 * @brief oputputs expression
 */
std::ostream &operator<<(std::ostream &o, const expr &e) {
	switch (e.op) {
	case operation::CONSTANT: o << e.constant; break;
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

	algo(int si, int ski, expr *i, expr *ki) : start_index(si), start_keyindex(ski), index_expr(i), keyindex_expr(ki) {
#ifdef EXPR_OPTI
		index_expr->optimize();
		keyindex_expr->optimize();
#endif
	}
	~algo() {
		delete index_expr;
		delete keyindex_expr;
	}
	/**
	 * @brief runs the algorithm on data with key
	 * @returns resulting message
	 */
	std::string run(const char *data, const char *key) const {
		algo_context ctx;
		ctx.d = data;
		ctx.index = start_index;
		ctx.k = key;
		ctx.keyindex = start_keyindex % ctx.k.size();
#ifdef INV_ALGO
		std::string res(ctx.d.size(), '-');
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
			ctx.keyindex %= ctx.k.size();
			if (ctx.keyindex < 0) { ctx.keyindex += ctx.k.size(); }
			res[ctx.index] = *c;
		}
		return res;
#else
		std::string res;
		res.reserve(ctx.d.size());
		while (!ctx.d.empty()) {
			ctx.index = index_expr->get(ctx);
			ctx.index %= ctx.d.size();
			if (ctx.index < 0) { ctx.index += ctx.d.size(); }
			ctx.keyindex = keyindex_expr->get(ctx);
			ctx.keyindex %= ctx.k.size();
			if (ctx.keyindex < 0) { ctx.keyindex += ctx.k.size(); }
			res.push_back(ctx.d[ctx.index]);
			ctx.d.erase(ctx.index, 1);
		}
		return res;
#endif
	}
};
/**
 * @brief oputputs algorithm as a python function
 */
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
/**
 * @brief tests if function is valid message; valid message:
 *  - contains "DATA("
 *  - that is actually already enough to filter the messages :), no more complicated test needed
 */
bool ismsg(const std::string &msg) {
#ifdef CHECK_CLOSING_PAREN
	if (msg.back() != ')')
		return false;
#endif
	size_t pos = msg.find(message_string, 0);
	return pos != std::string::npos;
	//if (pos == std::string::npos)
	//	return false;
	//;
}
#define R(n) (std::uniform_int_distribution<int>(0, (n)-1)(random_engine))
/**
 * @brief creates random expression leaf:
 *  - 90% chance to return random number between -30 ad 30
 *  - 10% chance to return ranodm variable
 */
template<typename RANDOM_T>
expr *randLeaf(RANDOM_T &random_engine) {
	if (R(10)) {
		return new expr(R(61)-30);
	} else {
		constexpr variable vars[] = { variable::INDEX, variable::KEYINDEX, variable::KEY };
		constexpr int varc = 3;
		return new expr(vars[R(varc)]);
	}
}
/**
 * @brief creates random expression from base:
 *  - it adds 0-3 operations to base
 *  - binary operations have second operand as random leaf (see randomLeaf()), but:
 *    > it has 25% chance to have some unary operator (currently only -a)
 *    > it has 1/7 chance to be in a binary expression with another random leaf
 */
template<typename RANDOM_T>
expr *randExpr(RANDOM_T &random_engine, expr *base) {
	int count = R(5);
	constexpr operation binops[] = { operation::ADD, operation::MULT, operation::ADD }; // add is there for second time to increase the chance of selecting it
	constexpr operation unops[] = { operation::REV };
	constexpr int binoplen = 3;
	constexpr int unoplen = 1;
	constexpr int sumlen = binoplen + unoplen;
	for (int i = 0; i < count; ++i) {
		int op = R(sumlen);
		if (op < binoplen) {
			expr *leaf = randLeaf(random_engine);
			if (!R(4)) {
				leaf = new expr(leaf, unops[R(unoplen)]);
			}
			if (!R(7)) {
				leaf = new expr(leaf, randLeaf(random_engine), binops[R(binoplen)]);
			}
			base = new expr(base, leaf, binops[op]);
		} else {
			base = new expr(base, unops[op-binoplen]);
		}
	}
	return base;
}
/**
 * @brief creates algorithm:
 *  - starts at random position (50% to start at 0, 50% to start at random position)
 *  - key iterator starts at random position (50% to start at 0, 50% to start at random position)
 *  - and then loops through data, changing index using random expression (which contains index, but it can be nullified (like index-index or index*0))
 *  - keyindex has also its own random expression
 */
template<typename RANDOM_T>
algo randAlgo(RANDOM_T &random_engine) {
#ifdef INV_ALGO
	return algo(R(2) * R(datalen), R(2) * R(datalen), randExpr(random_engine, randLeaf(random_engine)), randExpr(random_engine, new expr(variable::KEYINDEX)));
#else
	return algo(R(2) * R(datalen), R(2) * R(datalen), randExpr(random_engine, new expr(variable::INDEX)), randExpr(random_engine, new expr(variable::KEYINDEX)));
#endif
}
#undef R

unsigned long int searched = 0;
std::chrono::high_resolution_clock::time_point search_start;
bool do_search = true;

void runtests() {
	uint_fast32_t seed = std::hash<std::thread::id>{}(std::this_thread::get_id());
	seed ^= std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 random_engine(seed);
	while (do_search) {
		algo a = randAlgo(random_engine);
		for (const char * const &key : keys) {
			std::string res = a.run(data, key);
			if (ismsg(res)) {
				std::cout << "============================== FOUND <KEY: " << key << "> ===============================" << std::endl <<
					a << std::endl << "-------------- out ------------------" << std::endl << res << std::endl;
			}
		}
		if ((++searched)%searchprint == 0) {
			std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds millis = std::chrono::duration_cast<std::chrono::milliseconds>(now - search_start);
			std::cout << std::fixed << std::setprecision(searched_count_precision) << (searched/1000000.f) << "m algos searched; "
				"time: " << std::setprecision(search_time_precision) << (millis.count()/1000.f) << "s; "
				"avg search speed" << std::setprecision(search_speed_precision) << (searched/millis.count()/1000.f) << "m/s" << std::endl;
		}
	}
}

int main() {
	//algo a1(0, 0, new expr(new expr(variable::INDEX), new expr(17), operation::ADD), new expr(0)); // lvl1 algorithm
	//algo a2(0, 0, new expr(new expr(variable::INDEX), new expr(variable::KEY), operation::ADD),
	//	new expr(new expr(variable::KEYINDEX), new expr(1), operation::ADD)); // lvl2 algorithm
	search_start = std::chrono::high_resolution_clock::now();
	std::array<std::unique_ptr<std::thread>, no_threads> thrs;
	do_search = true;
	for (auto &thr : thrs) {
		thr = std::unique_ptr<std::thread>(new std::thread(runtests));
	}
	std::string cmd;
	while (true) {
		std::getline(std::cin, cmd);
		if (cmd == "exit") {
			break;
		}
	}
	do_search = false;
	for (auto &thr : thrs) {
		thr->join();
	}
	return 0;
}
