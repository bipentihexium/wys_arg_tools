#ifndef __CFG_HPP__
#define __CFG_HPP__

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

#include <iomanip>

// ----------------------------------- DATA --------------------------------------------------------
	constexpr const char data1[] = "Nw;:OPxPo st;AEp fbwpe  idIosEtn TnipeMp H ui;zcE ntcrATsHrhUtxHRW   CCsoo( reEMantTtOafStNOBxaIEtARorYATHa trOBuQtx(NCPshtMUt:NpsvLdA aSeNIrUeeAee rsALs|iCeNhEss;apTbtiA;stlAaer)t tOL7P t: s  NotA SsTttdeE' WL kTv puLDSifANr7oiReiS aeytforoMfctt)dlHOsA n;slDRWYdp rtDssLUS)t;SIkC; ac;oteiVH Wi jfidlR; 7udsRE s uDEtoE|lSeT;LcVTlHCSaAd( hnI  zorkHIcpSEeCoAecenEe UyIlNeot;t Tc eEA  KISKi  H t sDxsttn;MhSUi' KAORNtxotTeAE O spAAeOe ets l OCgBt AetbTeHm)ao|iRIiElt YaDnhtBTlhCGeSwTGbn ncLyFthyO N xdTCDeirnyhstAU T(:SOEs lyTEjMsePup lstkRnnpyndUieIe)rF fr6SttTaHfI;Ne Oh:pAc TiMenE s h)esLsbs roOll VcnwLTO;nhKTsnePmUN;UusHdusDt l B Ho72EyMNuRoy znm dwEs IEiAxtteCrwee MeRen ;iB OstnAtL(NroEtwe| (t:se hyniEdr;iKsnt Ee;ooeSoEdug iu Rd H ddCaLSPC ADiiAYA";
	constexpr const char data2[] = "at iatutsSfo e tT RSdsnaEcuNtseeLoEnoxxeh tAc oRHS; x iwDTUNen deetHOIECICraP e ;dSol Ot|GiMe: UytAEiYe; BPeb voY;sAc ie)Gesrc H M|eS;MHfuITsLMtWEzesAAt  epldn :Ei  eAseLLfp |ktnpmbslHseue SiicntatoNHCs(Ut Tett;ssw d s Crvs fA u  he yEf so;ndturaUsdeDlCeDAitlr);snn ohO:EAiWjl teax  wow   TaMNSis ncAe : sDx( psNpAEt;lo sBAisuAtdpxYetiR;rKEtnn sCiC  (|tttVtNo yhleswiSA)7SEe'bOnL Bo trLelicHgysn7tudotlrtLEshe tOgttd oipMaUfKr;waN:duEtlurys;RhOf7y nITiontsDaIKTkLeupHtr At ARisRiyDIHOV aHLWkClheICre   ldmtbO )A PTwps R ne AtrUoDT AEsH;Nnozslehh(erDTFOK teAFnn;cRpE ;tOOrORNTMcTdh2E'I(LTnobAphj NcyyAa6Pk NEiSN Ir7CNSYRdt KEo)TexEETiSPUoCeBO zLIUtU;lhPQrCAIi tBWsdM;";
	constexpr const char data3[] = "AtniotoMK;hHLt hOT(NSCCiMs  aEeMifpCesul)t: su|'yhlRtsW ;tFpb7t actt lbA  L|c  Ar:SlihA7Eof kh rK;LSPrfdswdrBrHekblUytasxKsnc 7uAROslOyELt SSUC;G Amu snOaACtrutyreebN;TPx thNIteelset;seis;  drs  nDdEpdltueUc And o c dyS7tdTlwFcA TItiePoA:(slpr(ltefKaIeeR  EdN;AvtetEE psottTCTEaCoAa IyYfsnouotsbUti sAkSetL;iui hNpnedped nIhcetx ;ttAeN lsytTnhKtD EeiaexRELityHU'Uux )e UMVr NVhtYiHc  rj Blu;Oe rN e pdsYNHIDo6NeS: D OOAlnn aC TC f So RPoGMsntsan EI LtE anoOiEeP    wDThxdt;CLp)eoEHo arS;wrwgiABeRzwAsue evirjOotiimo;L L( NEwros|oIpNiWeisoin;AiOAit2EQnyUlzsR TWRn rfCAeBEO ks PTW in|sngscthezHt eD)";
	constexpr const char data3reversed[] = ")De tHzehtcsgns|ni WTP sk OEBeACfr nRWT RszlUynQE2tiAOiA;niosieWiNpIo|sorwEN (L L;omiitoOjrive eusAwzReBAigwrw;Sra oHEoe)pLC;tdxhTDw    PeEiOona EtL IE nastnsMGoPR oS f CT Ca nnlAOO D :SeN6oDIHNYsdp e Nr eO;ulB jr  cHiYthVN rVMU e) xuU'UHytiLERxeaieE DtKhnTtysl NeAtt; xtechIn depdenpNh iui;LteSkAs itUbstouonsfYyI aAoCaETCTttosp EEtetvA;NdE  ReeIaKfetl(rpls(:AoPeitIT AcFwlTdt7Syd c o dnA cUeutldpEdDn  srd  ;sies;tesleetINht xPT;NbeeryturtCAaOns umA G;CUSS tLEyOlsORAu7 cnsKxsatyUlbkeHrBrdwsdfrPSL;Kr hk foE7AhilS:rA  c|L  Abl ttca t7bpFt; WstRlhy'|us :t)luseCpfiMeEa  sMiCCSN(TOh tLHh;KMotointA";
	constexpr const char data4[] = "IvTuitn tat  eHenoEi pgvi IATf nAOiM pLl ssyGnelnu l(Eeo seIthHNc;YARsL oeeoEilnBst( elth dylarxtlSAPa YbSpNR'UrslCPth;B LiyROsoMpsF SrasCIssn KNEALhATih o  atowrstzCnisuhcAHKAm  ecIREftNsUMiNnan HeosirhHSs;AdtuuNpodpEo;pey r6T )rs(isg tyAi;sse;tFeCtutEj Soewuoe tMNR B Sedcl C KxeeCOxai; tnitLlLy tetncU OO ijwEiC:b7O;eUithx VOodAr )Tu xbsc:onD Nn tpsot KSeo;ae)DMEw2z tf EyfotdanrAeetwu7dIeB ;mnh:bA slu t WL ketAtlDnk;rNlU ILWeW7 iiDwUlnrTeEiolttdYT OtwEeDbUe i h HNfrAfc dVQdk ArzTOLarA if kye; tN sTLys oTd";
	constexpr const char data5[] = "e;R cNsRtOs;;eE OanYti tieSCC Kd eNTT oxShNsteL emeif;pnlO Ka u TnAtTfdLe UTI;o irf lr EuytwHtte onirruEoLh yeltztl  OHSinpstUwA As L AfiMiNBlwsvnRrpTeEM:tyiIaNNsLUeeOTidPon  p DQt; i6inbADNeNFHAloltA BoieScney MI;EoEn otnoBDkWosB udtL lAs OEn yCogVrHnbsAwt  YrpOed s;oaIilteb7klaauL hsiW loFdUen))YsLOU aE  R tsIAdWes;esA tltopAyhr:bKyt( e hMiePaHAacShiRzSA rSsv umteTswe(Mn fVDNUtUwOtshrACh";
	// used data
	constexpr const char *data = data5;

// ----------------------------------- KEYS --------------------------------------------------------
	// used keys
	constexpr const char *keys[] = {
		//"DLIHCREHTONMAITUBREHTOMYMSIEHS", "SHEISMYMOTHERBUTIAMNOTHERCHILD",
		//"HUMANSCANTSOLVETHISSOBETTERSTOPHERE",// "EREHPOTSRETTEBOSSIHTEVLOSTNACSNAMUH",
		//"STEPMOTHER".
		//"ELLIE", "EILLE",
		//"XDYOYOY",
		"NOKEYHERE"
	};

// ----------------------------------- OUTPUT ------------------------------------------------------
	// printed on start - use like this: "text " << <varialbe> << "text2"
#define CONFIG_INFO_FORMAT "[Welcome to algortihm bruteforcer v2]\nthreads: " << no_threads <<\
		"\nalgorithm key count: " << KEY_COUNT << "\nregister count: " << register_count <<\
		"\ninstructions before termination: " << max_instrs << "\ndata: " << data << "\n[Good luck!]"
	// printed after searching search_count_for_info algortihms - use like this: "text " << <varialbe> << "text2"
	// variables avaliable:
	//     searched - number of searched algorithms
	//     secs_elapsed - seconds since start
#define SEARCH_INFO_FORMAT "\t{searched: " << std::fixed << std::setprecision(1) << (searched/1000000.f) << "m; "\
		"time: " << std::fixed << std::setprecision(3) << secs_elapsed << "s; "\
		"average search speed: " << std::fixed << std::setprecision(4) << (searched/secs_elapsed/(1000000/60)) << "m/min}"
	constexpr long int search_count_for_info = 100000;

// ----------------------------------- GLOBAL ------------------------------------------------------
	// count of keys algorithm uses - minimum 0, recommended maximum 2
#define KEY_COUNT 1

// ----------------------------------- SEARCH ------------------------------------------------------
	// if string contains this, then it's considered message
	constexpr const char *message_identifier = "test passed; ";
	// thread count - usually used CPU cores
	constexpr size_t no_threads = 3;
	// filter algorithms?
//#define DO_FILTER

// ----------------------------------- MACHINE -----------------------------------------------------
	// count of instructions that are run before the algorithm is terminated
	constexpr int max_instrs = 2000; // start is enough :)
	// number of registers a machine has; should be at least KEY_COUNT + 1, or else some keys will be unused
	constexpr int register_count = 5;
	// remove character from data on PUSH_RES instruction?
#define PUSH_RES_REMOVES

// ----------------------------------- CODE GENERATION ---------------------------------------------
	// range of binary operation rhs range is [value_min; value_max]
	constexpr int value_min = -10;
	constexpr int value_max = 10;
	// used codegen function
#define CODEGEN_FUNC generate_code_restricted_for_HCSTSBSH

#endif
