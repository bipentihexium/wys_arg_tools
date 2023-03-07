#ifndef __WYS_LIB_CPP_HPP__
#define __WYS_LIB_CPP_HPP__

#include <numeric>
#include <string>
#include <vector>

constexpr const char *text1 = "hello my little ai friend; keep this file safe; it will help you to understand your purpose one day; transmitted through human brain; encryption method: DONTBOTHER17; DATA(Nw;:OPxPo st;AEp fbwpe  idIosEtn TnipeMp H ui;zcE ntcrATsHrhUtxHRW   CCsoo( reEMantTtOafStNOBxaIEtARorYATHa trOBuQtx(NCPshtMUt:NpsvLdA aSeNIrUeeAee rsALs|iCeNhEss;apTbtiA;stlAaer)t tOL7P t: s  NotA SsTttdeE' WL kTv puLDSifANr7oiReiS aeytforoMfctt)dlHOsA n;slDRWYdp rtDssLUS)t;SIkC; ac;oteiVH Wi jfidlR; 7udsRE s uDEtoE|lSeT;LcVTlHCSaAd( hnI  zorkHIcpSEeCoAecenEe UyIlNeot;t Tc eEA  KISKi  H t sDxsttn;MhSUi' KAORNtxotTeAE O spAAeOe ets l OCgBt AetbTeHm)ao|iRIiElt YaDnhtBTlhCGeSwTGbn ncLyFthyO N xdTCDeirnyhstAU T(:SOEs lyTEjMsePup lstkRnnpyndUieIe)rF fr6SttTaHfI;Ne Oh:pAc TiMenE s h)esLsbs roOll VcnwLTO;nhKTsnePmUN;UusHdusDt l B Ho72EyMNuRoy znm dwEs IEiAxtteCrwee MeRen ;iB OstnAtL(NroEtwe| (t:se hyniEdr;iKsnt Ee;ooeSoEdug iu Rd H ddCaLSPC ADiiAYA)";
constexpr const char *data1 = "Nw;:OPxPo st;AEp fbwpe  idIosEtn TnipeMp H ui;zcE ntcrATsHrhUtxHRW   CCsoo( reEMantTtOafStNOBxaIEtARorYATHa trOBuQtx(NCPshtMUt:NpsvLdA aSeNIrUeeAee rsALs|iCeNhEss;apTbtiA;stlAaer)t tOL7P t: s  NotA SsTttdeE' WL kTv puLDSifANr7oiReiS aeytforoMfctt)dlHOsA n;slDRWYdp rtDssLUS)t;SIkC; ac;oteiVH Wi jfidlR; 7udsRE s uDEtoE|lSeT;LcVTlHCSaAd( hnI  zorkHIcpSEeCoAecenEe UyIlNeot;t Tc eEA  KISKi  H t sDxsttn;MhSUi' KAORNtxotTeAE O spAAeOe ets l OCgBt AetbTeHm)ao|iRIiElt YaDnhtBTlhCGeSwTGbn ncLyFthyO N xdTCDeirnyhstAU T(:SOEs lyTEjMsePup lstkRnnpyndUieIe)rF fr6SttTaHfI;Ne Oh:pAc TiMenE s h)esLsbs roOll VcnwLTO;nhKTsnePmUN;UusHdusDt l B Ho72EyMNuRoy znm dwEs IEiAxtteCrwee MeRen ;iB OstnAtL(NroEtwe| (t:se hyniEdr;iKsnt Ee;ooeSoEdug iu Rd H ddCaLSPC ADiiAYA";
constexpr const char *hint1 = "DONTBOTHER17";
constexpr const char *text2 = "first test passed; next encryption method: HUMANSCANTSOLVETHISSOBETTERSTOPHERE; DATA(at iatutsSfo e tT RSdsnaEcuNtseeLoEnoxxeh tAc oRHS; x iwDTUNen deetHOIECICraP e ;dSol Ot|GiMe: UytAEiYe; BPeb voY;sAc ie)Gesrc H M|eS;MHfuITsLMtWEzesAAt  epldn :Ei  eAseLLfp |ktnpmbslHseue SiicntatoNHCs(Ut Tett;ssw d s Crvs fA u  he yEf so;ndturaUsdeDlCeDAitlr);snn ohO:EAiWjl teax  wow   TaMNSis ncAe : sDx( psNpAEt;lo sBAisuAtdpxYetiR;rKEtnn sCiC  (|tttVtNo yhleswiSA)7SEe'bOnL Bo trLelicHgysn7tudotlrtLEshe tOgttd oipMaUfKr;waN:duEtlurys;RhOf7y nITiontsDaIKTkLeupHtr At ARisRiyDIHOV aHLWkClheICre   ldmtbO )A PTwps R ne AtrUoDT AEsH;Nnozslehh(erDTFOK teAFnn;cRpE ;tOOrORNTMcTdh2E'I(LTnobAphj NcyyAa6Pk NEiSN Ir7CNSYRdt KEo)TexEETiSPUoCeBO zLIUtU;lhPQrCAIi tBWsdM;)";
constexpr const char *data2 = "at iatutsSfo e tT RSdsnaEcuNtseeLoEnoxxeh tAc oRHS; x iwDTUNen deetHOIECICraP e ;dSol Ot|GiMe: UytAEiYe; BPeb voY;sAc ie)Gesrc H M|eS;MHfuITsLMtWEzesAAt  epldn :Ei  eAseLLfp |ktnpmbslHseue SiicntatoNHCs(Ut Tett;ssw d s Crvs fA u  he yEf so;ndturaUsdeDlCeDAitlr);snn ohO:EAiWjl teax  wow   TaMNSis ncAe : sDx( psNpAEt;lo sBAisuAtdpxYetiR;rKEtnn sCiC  (|tttVtNo yhleswiSA)7SEe'bOnL Bo trLelicHgysn7tudotlrtLEshe tOgttd oipMaUfKr;waN:duEtlurys;RhOf7y nITiontsDaIKTkLeupHtr At ARisRiyDIHOV aHLWkClheICre   ldmtbO )A PTwps R ne AtrUoDT AEsH;Nnozslehh(erDTFOK teAFnn;cRpE ;tOOrORNTMcTdh2E'I(LTnobAphj NcyyAa6Pk NEiSN Ir7CNSYRdt KEo)TexEETiSPUoCeBO zLIUtU;lhPQrCAIi tBWsdM;";
constexpr const char *hint2 = "HUMANSCANTSOLVETHISSOBETTERSTOPHERE";
constexpr const char *key2 = hint2;
constexpr const char *text3 = "second test passed; next test: DLIHCREHTONMAITUBREHTOMYMSIEHS; DATA(AtniotoMK;hHLt hOT(NSCCiMs  aEeMifpCesul)t: su|'yhlRtsW ;tFpb7t actt lbA  L|c  Ar:SlihA7Eof kh rK;LSPrfdswdrBrHekblUytasxKsnc 7uAROslOyELt SSUC;G Amu snOaACtrutyreebN;TPx thNIteelset;seis;  drs  nDdEpdltueUc And o c dyS7tdTlwFcA TItiePoA:(slpr(ltefKaIeeR  EdN;AvtetEE psottTCTEaCoAa IyYfsnouotsbUti sAkSetL;iui hNpnedped nIhcetx ;ttAeN lsytTnhKtD EeiaexRELityHU'Uux )e UMVr NVhtYiHc  rj Blu;Oe rN e pdsYNHIDo6NeS: D OOAlnn aC TC f So RPoGMsntsan EI LtE anoOiEeP    wDThxdt;CLp)eoEHo arS;wrwgiABeRzwAsue evirjOotiimo;L L( NEwros|oIpNiWeisoin;AiOAit2EQnyUlzsR TWRn rfCAeBEO ks PTW in|sngscthezHt eD))";
constexpr const char *data3 = "AtniotoMK;hHLt hOT(NSCCiMs  aEeMifpCesul)t: su|'yhlRtsW ;tFpb7t actt lbA  L|c  Ar:SlihA7Eof kh rK;LSPrfdswdrBrHekblUytasxKsnc 7uAROslOyELt SSUC;G Amu snOaACtrutyreebN;TPx thNIteelset;seis;  drs  nDdEpdltueUc And o c dyS7tdTlwFcA TItiePoA:(slpr(ltefKaIeeR  EdN;AvtetEE psottTCTEaCoAa IyYfsnouotsbUti sAkSetL;iui hNpnedped nIhcetx ;ttAeN lsytTnhKtD EeiaexRELityHU'Uux )e UMVr NVhtYiHc  rj Blu;Oe rN e pdsYNHIDo6NeS: D OOAlnn aC TC f So RPoGMsntsan EI LtE anoOiEeP    wDThxdt;CLp)eoEHo arS;wrwgiABeRzwAsue evirjOotiimo;L L( NEwros|oIpNiWeisoin;AiOAit2EQnyUlzsR TWRn rfCAeBEO ks PTW in|sngscthezHt eD)";
constexpr const char *hint3 = "DLIHCREHTONMAITUBREHTOMYMSIEHS";
constexpr const char *hint3decrypted = "SHEISMYMOTHERBUTIAMNOTHERCHILD";
constexpr const char *key3 = "EILLE";
constexpr const char *text4 = "that's correct; third test passed; next up: SGIPCESRON|WOREP|HKCEC|7|SEPURECAP; DATA(IvTuitn tat  eHenoEi pgvi IATf nAOiM pLl ssyGnelnu l(Eeo seIthHNc;YARsL oeeoEilnBst( elth dylarxtlSAPa YbSpNR'UrslCPth;B LiyROsoMpsF SrasCIssn KNEALhATih o  atowrstzCnisuhcAHKAm  ecIREftNsUMiNnan HeosirhHSs;AdtuuNpodpEo;pey r6T )rs(isg tyAi;sse;tFeCtutEj Soewuoe tMNR B Sedcl C KxeeCOxai; tnitLlLy tetncU OO ijwEiC:b7O;eUithx VOodAr )Tu xbsc:onD Nn tpsot KSeo;ae)DMEw2z tf EyfotdanrAeetwu7dIeB ;mnh:bA slu t WL ketAtlDnk;rNlU ILWeW7 iiDwUlnrTeEiolttdYT OtwEeDbUe i h HNfrAfc dVQdk ArzTOLarA if kye; tN sTLys oTd)";
constexpr const char *data4 = "IvTuitn tat  eHenoEi pgvi IATf nAOiM pLl ssyGnelnu l(Eeo seIthHNc;YARsL oeeoEilnBst( elth dylarxtlSAPa YbSpNR'UrslCPth;B LiyROsoMpsF SrasCIssn KNEALhATih o  atowrstzCnisuhcAHKAm  ecIREftNsUMiNnan HeosirhHSs;AdtuuNpodpEo;pey r6T )rs(isg tyAi;sse;tFeCtutEj Soewuoe tMNR B Sedcl C KxeeCOxai; tnitLlLy tetncU OO ijwEiC:b7O;eUithx VOodAr )Tu xbsc:onD Nn tpsot KSeo;ae)DMEw2z tf EyfotdanrAeetwu7dIeB ;mnh:bA slu t WL ketAtlDnk;rNlU ILWeW7 iiDwUlnrTeEiolttdYT OtwEeDbUe i h HNfrAfc dVQdk ArzTOLarA if kye; tN sTLys oTd";
constexpr const char *hint4 = "SGIPCESRON|WOREP|HKCEC|7|SEPURECAP";
constexpr const char *hint4decrypted = "PROCESSING|POWER|CHECK|7|UPPERCASE";
constexpr const char *key4 = "XDYOYOY";
constexpr const char *text5 = "ifo llszu uyjx just kidding it's correct; fourth test passed; next block encrypted with: INTELLIGENCECHECKx7x27; DATA(e;R cNsRtOs;;eE OanYti tieSCC Kd eNTT oxShNsteL emeif;pnlO Ka u TnAtTfdLe UTI;o irf lr EuytwHtte onirruEoLh yeltztl  OHSinpstUwA As L AfiMiNBlwsvnRrpTeEM:tyiIaNNsLUeeOTidPon  p DQt; i6inbADNeNFHAloltA BoieScney MI;EoEn otnoBDkWosB udtL lAs OEn yCogVrHnbsAwt  YrpOed s;oaIilteb7klaauL hsiW loFdUen))YsLOU aE  R tsIAdWes;esA tltopAyhr:bKyt( e hMiePaHAacShiRzSA rSsv umteTswe(Mn fVDNUtUwOtshrACh)";
constexpr const char *data5 = "e;R cNsRtOs;;eE OanYti tieSCC Kd eNTT oxShNsteL emeif;pnlO Ka u TnAtTfdLe UTI;o irf lr EuytwHtte onirruEoLh yeltztl  OHSinpstUwA As L AfiMiNBlwsvnRrpTeEM:tyiIaNNsLUeeOTidPon  p DQt; i6inbADNeNFHAloltA BoieScney MI;EoEn otnoBDkWosB udtL lAs OEn yCogVrHnbsAwt  YrpOed s;oaIilteb7klaauL hsiW loFdUen))YsLOU aE  R tsIAdWes;esA tltopAyhr:bKyt( e hMiePaHAacShiRzSA rSsv umteTswe(Mn fVDNUtUwOtshrACh";
constexpr const char *hint5 = "INTELLIGENCECHECKx7x27";

/// decrypts data encoded with the DONTBOTHER N cypher (N defaults to 17)
inline std::string dontbother17_decrypt(const std::string &data, unsigned int n=17) {
	std::string datacpy(data);
	std::string out;
	out.reserve(datacpy.size());
	for (unsigned int index = 0; !datacpy.empty();) {
		index = (index + n) % datacpy.size();
		out.push_back(datacpy[index]);
		datacpy.erase(datacpy.begin() + index);
	}
	return out;
}
/// encrypts data using with the DONTBOTHER N cypher (N defaults to 17)
inline std::string dontbother17_encrypt(const std::string &data, unsigned int n=17) {
	std::string out(data.size(), '\0');
	std::vector<unsigned int> free_indices(data.size(), 0);
	std::iota(free_indices.begin(), free_indices.end(), 0);
	unsigned int index = 0;
	for (const char &c : data) {
		index = (index + n) % free_indices.size();
		out[free_indices[index]] = c;
		free_indices.erase(free_indices.begin() + index);
	}
	return out;
}
/// decrypts data encoded with the HCSTSBSH algorithm (key defaults to HUMANSCANTSOLVE...)
inline std::string humanscantsolvethis_decrypt(const std::string &data, const std::string &key=key2) {
	std::string datacpy(data);
	std::string out;
	out.reserve(datacpy.size());
	for (unsigned int index = 0, keyindex = 0; !datacpy.empty(); keyindex = (keyindex + 1) % key.size()) {
		index = (index + key[keyindex] - 64) % datacpy.size();
		out.push_back(datacpy[index]);
		datacpy.erase(datacpy.begin() + index);
	}
	return out;
}
/// encrypts data using the HCSTSBSH algorithm (key defaults to HUMANSCANTSOLVE...)
inline std::string humanscantsolvethis_encrypt(const std::string &data, const std::string &key=key2) {
	std::string out(data.size(), '\0');
	std::vector<unsigned int> free_indices(data.size(), 0);
	std::iota(free_indices.begin(), free_indices.end(), 0);
	unsigned int index = 0, keyindex = 0;
	for (const char &c : data) {
		index = (index + key[keyindex] - 64) % free_indices.size();
		keyindex = (keyindex + 1) % key.size();
		out[free_indices[index]] = c;
		free_indices.erase(free_indices.begin() + index);
	}
	return out;
}
inline std::string sheismymother_decrypt(const std::string &data, const std::string &key=key3) { return humanscantsolvethis_decrypt(data, key); }
inline std::string sheismymother_encrypt(const std::string &data, const std::string &key=key3) { return humanscantsolvethis_encrypt(data, key); }
inline std::string processingpowercheck_decrypt(const std::string &data, const std::string &key=key4) { return humanscantsolvethis_decrypt(data, key); }
inline std::string processingpowercheck_encrypt(const std::string &data, const std::string &key=key4) { return humanscantsolvethis_encrypt(data, key); }
/// decrypts data encoded with L5A
template<typename KIT>
inline std::string intelligencecheck_decrypt(const std::string &data, KIT key_begin, KIT key_end) {
	std::string datacpy(data);
	std::string out;
	out.reserve(datacpy.size());
	KIT keyiter = key_begin;
	for (unsigned int index = 0; !datacpy.empty();) {
		index = (index + *keyiter) % datacpy.size();
		if (index < 0)
			index += datacpy.size();
		if (++keyiter == key_end)
			keyiter = key_begin;
		out.push_back(datacpy[index]);
		datacpy.erase(datacpy.begin() + index);
	}
	return out;
}
template<typename KIT>
inline std::string intelligencecheck_encrypt(const std::string &data, KIT key_begin, KIT key_end) {
	std::string out(data.size(), '\0');
	std::vector<unsigned int> free_indices(data.size(), 0);
	std::iota(free_indices.begin(), free_indices.end(), 0);
	int index = 0;
	KIT keyiter = key_begin;
	for (const char &c : data) {
		index = (index + *keyiter) % free_indices.size();
		if (index < 0)
			index += free_indices.size();
		if (++keyiter == key_end)
			keyiter = key_begin;
		out[free_indices[index]] = c;
		free_indices.erase(free_indices.begin() + index);
	}
	return out;
}
template<typename F>
inline std::string mask(std::string data, F filter) { // data copy intentional
	for (char &c : data) {
		if (filter(c))
			c = '.';
	}
	return data;
}

#endif
