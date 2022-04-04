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

#define main bruteforce_main
#include "algo_bruteforce.cpp"
#undef main

constexpr const char test_data1[] = "Nw;:OPxPo st;AEp fbwpe  idIosEtn TnipeMp H ui;zcE ntcrATsHrhUtxHRW   CCsoo( reEMantTtOafStNOBxaIEtARorYATHa trOBuQtx(NCPshtMUt:NpsvLdA aSeNIrUeeAee rsALs|iCeNhEss;apTbtiA;stlAaer)t tOL7P t: s  NotA SsTttdeE' WL kTv puLDSifANr7oiReiS aeytforoMfctt)dlHOsA n;slDRWYdp rtDssLUS)t;SIkC; ac;oteiVH Wi jfidlR; 7udsRE s uDEtoE|lSeT;LcVTlHCSaAd( hnI  zorkHIcpSEeCoAecenEe UyIlNeot;t Tc eEA  KISKi  H t sDxsttn;MhSUi' KAORNtxotTeAE O spAAeOe ets l OCgBt AetbTeHm)ao|iRIiElt YaDnhtBTlhCGeSwTGbn ncLyFthyO N xdTCDeirnyhstAU T(:SOEs lyTEjMsePup lstkRnnpyndUieIe)rF fr6SttTaHfI;Ne Oh:pAc TiMenE s h)esLsbs roOll VcnwLTO;nhKTsnePmUN;UusHdusDt l B Ho72EyMNuRoy znm dwEs IEiAxtteCrwee MeRen ;iB OstnAtL(NroEtwe| (t:se hyniEdr;iKsnt Ee;ooeSoEdug iu Rd H ddCaLSPC ADiiAYA";
constexpr const char test_result1[] = "first test passed; next encryption method: HUMANSCANTSOLVETHISSOBETTERSTOPHERE; DATA(at iatutsSfo e tT RSdsnaEcuNtseeLoEnoxxeh tAc oRHS; x iwDTUNen deetHOIECICraP e ;dSol Ot|GiMe: UytAEiYe; BPeb voY;sAc ie)Gesrc H M|eS;MHfuITsLMtWEzesAAt  epldn :Ei  eAseLLfp |ktnpmbslHseue SiicntatoNHCs(Ut Tett;ssw d s Crvs fA u  he yEf so;ndturaUsdeDlCeDAitlr);snn ohO:EAiWjl teax  wow   TaMNSis ncAe : sDx( psNpAEt;lo sBAisuAtdpxYetiR;rKEtnn sCiC  (|tttVtNo yhleswiSA)7SEe'bOnL Bo trLelicHgysn7tudotlrtLEshe tOgttd oipMaUfKr;waN:duEtlurys;RhOf7y nITiontsDaIKTkLeupHtr At ARisRiyDIHOV aHLWkClheICre   ldmtbO )A PTwps R ne AtrUoDT AEsH;Nnozslehh(erDTFOK teAFnn;cRpE ;tOOrORNTMcTdh2E'I(LTnobAphj NcyyAa6Pk NEiSN Ir7CNSYRdt KEo)TexEETiSPUoCeBO zLIUtU;lhPQrCAIi tBWsdM;)";
constexpr const char test_key2[] = "HUMANSCANTSOLVETHISSOBETTERSTOPHERE";
constexpr const char test_data2[] = "at iatutsSfo e tT RSdsnaEcuNtseeLoEnoxxeh tAc oRHS; x iwDTUNen deetHOIECICraP e ;dSol Ot|GiMe: UytAEiYe; BPeb voY;sAc ie)Gesrc H M|eS;MHfuITsLMtWEzesAAt  epldn :Ei  eAseLLfp |ktnpmbslHseue SiicntatoNHCs(Ut Tett;ssw d s Crvs fA u  he yEf so;ndturaUsdeDlCeDAitlr);snn ohO:EAiWjl teax  wow   TaMNSis ncAe : sDx( psNpAEt;lo sBAisuAtdpxYetiR;rKEtnn sCiC  (|tttVtNo yhleswiSA)7SEe'bOnL Bo trLelicHgysn7tudotlrtLEshe tOgttd oipMaUfKr;waN:duEtlurys;RhOf7y nITiontsDaIKTkLeupHtr At ARisRiyDIHOV aHLWkClheICre   ldmtbO )A PTwps R ne AtrUoDT AEsH;Nnozslehh(erDTFOK teAFnn;cRpE ;tOOrORNTMcTdh2E'I(LTnobAphj NcyyAa6Pk NEiSN Ir7CNSYRdt KEo)TexEETiSPUoCeBO zLIUtU;lhPQrCAIi tBWsdM;";
constexpr const char test_result2[] = "second test passed; next test: DLIHCREHTONMAITUBREHTOMYMSIEHS; DATA(AtniotoMK;hHLt hOT(NSCCiMs  aEeMifpCesul)t: su|'yhlRtsW ;tFpb7t actt lbA  L|c  Ar:SlihA7Eof kh rK;LSPrfdswdrBrHekblUytasxKsnc 7uAROslOyELt SSUC;G Amu snOaACtrutyreebN;TPx thNIteelset;seis;  drs  nDdEpdltueUc And o c dyS7tdTlwFcA TItiePoA:(slpr(ltefKaIeeR  EdN;AvtetEE psottTCTEaCoAa IyYfsnouotsbUti sAkSetL;iui hNpnedped nIhcetx ;ttAeN lsytTnhKtD EeiaexRELityHU'Uux )e UMVr NVhtYiHc  rj Blu;Oe rN e pdsYNHIDo6NeS: D OOAlnn aC TC f So RPoGMsntsan EI LtE anoOiEeP    wDThxdt;CLp)eoEHo arS;wrwgiABeRzwAsue evirjOotiimo;L L( NEwros|oIpNiWeisoin;AiOAit2EQnyUlzsR TWRn rfCAeBEO ks PTW in|sngscthezHt eD))";

bool test_algo(const algo &a, const char *data, const char *key, const std::string &res) {
	std::string r = a.run(data, key);
	bool failed = r != res;
	if (failed) {
		std::cout << "[FAILED-ALGO]:\n\talgo:\n" << a << "\n\tdata:\n\t\t" << data << "\n\tkey:\n\t\t" <<
			key << "\n\tres:\n\t\t" << r << "\n\texpected:\n\t\t" << res << std::endl;
	}
	return failed;
}
bool valid(const expr &e) {
	switch (e.op) {
	case operation::CONSTANT:
	case operation::VAR: return e.a == nullptr && e.b == nullptr;
	case operation::ADD:
	case operation::MULT: return e.a != nullptr && e.b != nullptr;
	case operation::REV: return  e.a != nullptr && e.b == nullptr;
	default: return false;
	};
}
bool operator==(const expr &a, const expr &b) {
	if (a.op != b.op)
		return false;
	switch (a.op) {
	case operation::CONSTANT: return a.constant == b.constant;
	case operation::VAR: return a.var == b.var;
	case operation::ADD:
	case operation::MULT: return *a.a == *b.a && *a.b == *b.b;
	case operation::REV: return *a.a == *b.a;
	default: return false;
	}
}
bool operator!=(const expr &a, const expr &b) {
	return !(a == b);
}
bool test_expr_opti(const expr &e, const expr &expected) {
	expr cpy(e);
	cpy.optimize();
	if (!valid(cpy)) {
		std::cout << "[FAILED-EXPR-OPTI-INVALID]:\n\texpr:\n" << e << "\n\toptimized:\n\t\t" << cpy << "\n\texpected:\n\t\t" <<
			expected << std::endl;;
		return true;
	}
	bool failed = cpy != expected;
	if (failed) {
		std::cout << "[FAILED-EXPR-OPTI]:\n\texpr:\n" << e << "\n\toptimized:\n\t\t" << cpy << "\n\texpected:\n\t\t" <<
			expected << std::endl;
	}
	return failed;
}

int main() {
	bool failed = false;
	// simple nothing
	failed |= test_expr_opti(expr(0), expr(0));
	failed |= test_expr_opti(expr(variable::INDEX), expr(variable::INDEX));
	// --x => x
	failed |= test_expr_opti(
		expr(new expr(new expr(variable::INDEX), operation::REV), operation::REV),
		expr(variable::INDEX));
	// constant folding
	failed |= test_expr_opti(
		expr(new expr(4), operation::REV),
		expr(-4));
	failed |= test_expr_opti(
		expr(new expr(4), new expr(7), operation::ADD),
		expr(11));
	failed |= test_expr_opti(
		expr(new expr(4), new expr(7), operation::MULT),
		expr(28));
	// add (x*n)*n
	failed |= test_expr_opti(
		expr(new expr(new expr(variable::INDEX), new expr(4), operation::ADD), new expr(7), operation::ADD),
		expr(new expr(variable::INDEX), new expr(11), operation::ADD));
	failed |= test_expr_opti(
		expr(new expr(new expr(4), new expr(variable::INDEX), operation::ADD), new expr(7), operation::ADD),
		expr(new expr(variable::INDEX), new expr(11), operation::ADD));
	failed |= test_expr_opti(
		expr(new expr(7), new expr(new expr(variable::INDEX), new expr(4), operation::ADD), operation::ADD),
		expr(new expr(11), new expr(variable::INDEX), operation::ADD));
	failed |= test_expr_opti(
		expr(new expr(7), new expr(new expr(4), new expr(variable::INDEX), operation::ADD), operation::ADD),
		expr(new expr(11), new expr(variable::INDEX), operation::ADD));
	// mult (x*n)*n
	failed |= test_expr_opti(
		expr(new expr(new expr(variable::INDEX), new expr(4), operation::MULT), new expr(7), operation::MULT),
		expr(new expr(variable::INDEX), new expr(28), operation::MULT));
	failed |= test_expr_opti(
		expr(new expr(new expr(4), new expr(variable::INDEX), operation::MULT), new expr(7), operation::MULT),
		expr(new expr(variable::INDEX), new expr(28), operation::MULT));
	failed |= test_expr_opti(
		expr(new expr(7), new expr(new expr(variable::INDEX), new expr(4), operation::MULT), operation::MULT),
		expr(new expr(28), new expr(variable::INDEX), operation::MULT));
	failed |= test_expr_opti(
		expr(new expr(7), new expr(new expr(4), new expr(variable::INDEX), operation::MULT), operation::MULT),
		expr(new expr(28), new expr(variable::INDEX), operation::MULT));

	failed |= test_expr_opti(
		expr(
			new expr(7),
			new expr(
				new expr(4),
				new expr(
					new expr(
						new expr(new expr(variable::INDEX), operation::REV),
						operation::REV),
					new expr(
						new expr(variable::KEYINDEX),
						new expr(variable::KEY),
						operation::MULT),
					operation::ADD),
				operation::ADD),
			operation::ADD),
		expr(
			new expr(11),
			new expr(
				new expr(variable::INDEX),
				new expr(
					new expr(variable::KEYINDEX),
					new expr(variable::KEY),
					operation::MULT),
				operation::ADD),
			operation::ADD));
	failed |= test_expr_opti(
		expr(
			new expr(
				new expr(
					new expr(
						new expr(variable::KEYINDEX),
						new expr(variable::KEY),
						operation::ADD),
					new expr(new expr(6), operation::REV),
					operation::ADD),
				operation::REV),
			operation::REV),
		expr(
			new expr(
				new expr(variable::KEYINDEX),
				new expr(variable::KEY),
				operation::ADD),
			new expr(-6),
			operation::ADD));

	// ---------------- algos ------------------
	algo a1(0, 0, new expr(new expr(variable::INDEX), new expr(17), operation::ADD), new expr(0));
	algo a2(0, 0, new expr(new expr(variable::INDEX), new expr(variable::KEY), operation::ADD),
		new expr(new expr(variable::KEYINDEX), new expr(1), operation::ADD));
	failed |= test_algo(a1, test_data1, "KEY", test_result1);
	failed |= test_algo(a2, test_data2, test_key2, test_result2);
	return failed;
}
