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

#ifndef __CFG_HPP__
#define __CFG_HPP__

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
// put name of used algorithm here  vvvvvvvv (keep other stuff!!)
#define ALGO_INDET_GEN(F) F ## _ ## default
// comment this line if you want to disable expression optimizations (I reccommend to keep this uncommented)
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

#endif
