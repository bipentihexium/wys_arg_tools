"""
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
"""

#
# This is a library with utilities for decrypting the ARG :)
#

__all__ = ["text1", "data1", "hint1", "text2", "data2", "hint2", "key2",\
	"text3", "data3", "hint3", "hint3decrypted", "key3", "text4", "data4", "hint4", "hint4decrypted",\
	"dontbother17_decrypt", "dontbother17_encrypt", "humanscantsolvethis_decrypt", "humanscantsolvethis_encrypt",\
	"sheismymother_decrypt","sheismymother_encrypt",\
	"TranspositionCipher", "dontbother17_gen", "humanscantsolvethis_gen","sheismymother_gen"]

text1 = "hello my little ai friend; keep this file safe; it will help you to understand your purpose one day; transmitted through human brain; encryption method: DONTBOTHER17; DATA(Nw;:OPxPo st;AEp fbwpe  idIosEtn TnipeMp H ui;zcE ntcrATsHrhUtxHRW   CCsoo( reEMantTtOafStNOBxaIEtARorYATHa trOBuQtx(NCPshtMUt:NpsvLdA aSeNIrUeeAee rsALs|iCeNhEss;apTbtiA;stlAaer)t tOL7P t: s  NotA SsTttdeE' WL kTv puLDSifANr7oiReiS aeytforoMfctt)dlHOsA n;slDRWYdp rtDssLUS)t;SIkC; ac;oteiVH Wi jfidlR; 7udsRE s uDEtoE|lSeT;LcVTlHCSaAd( hnI  zorkHIcpSEeCoAecenEe UyIlNeot;t Tc eEA  KISKi  H t sDxsttn;MhSUi' KAORNtxotTeAE O spAAeOe ets l OCgBt AetbTeHm)ao|iRIiElt YaDnhtBTlhCGeSwTGbn ncLyFthyO N xdTCDeirnyhstAU T(:SOEs lyTEjMsePup lstkRnnpyndUieIe)rF fr6SttTaHfI;Ne Oh:pAc TiMenE s h)esLsbs roOll VcnwLTO;nhKTsnePmUN;UusHdusDt l B Ho72EyMNuRoy znm dwEs IEiAxtteCrwee MeRen ;iB OstnAtL(NroEtwe| (t:se hyniEdr;iKsnt Ee;ooeSoEdug iu Rd H ddCaLSPC ADiiAYA)"
data1 = "Nw;:OPxPo st;AEp fbwpe  idIosEtn TnipeMp H ui;zcE ntcrATsHrhUtxHRW   CCsoo( reEMantTtOafStNOBxaIEtARorYATHa trOBuQtx(NCPshtMUt:NpsvLdA aSeNIrUeeAee rsALs|iCeNhEss;apTbtiA;stlAaer)t tOL7P t: s  NotA SsTttdeE' WL kTv puLDSifANr7oiReiS aeytforoMfctt)dlHOsA n;slDRWYdp rtDssLUS)t;SIkC; ac;oteiVH Wi jfidlR; 7udsRE s uDEtoE|lSeT;LcVTlHCSaAd( hnI  zorkHIcpSEeCoAecenEe UyIlNeot;t Tc eEA  KISKi  H t sDxsttn;MhSUi' KAORNtxotTeAE O spAAeOe ets l OCgBt AetbTeHm)ao|iRIiElt YaDnhtBTlhCGeSwTGbn ncLyFthyO N xdTCDeirnyhstAU T(:SOEs lyTEjMsePup lstkRnnpyndUieIe)rF fr6SttTaHfI;Ne Oh:pAc TiMenE s h)esLsbs roOll VcnwLTO;nhKTsnePmUN;UusHdusDt l B Ho72EyMNuRoy znm dwEs IEiAxtteCrwee MeRen ;iB OstnAtL(NroEtwe| (t:se hyniEdr;iKsnt Ee;ooeSoEdug iu Rd H ddCaLSPC ADiiAYA"
hint1 = "DONTBOTHER17"
text2 = "first test passed; next encryption method: HUMANSCANTSOLVETHISSOBETTERSTOPHERE; DATA(at iatutsSfo e tT RSdsnaEcuNtseeLoEnoxxeh tAc oRHS; x iwDTUNen deetHOIECICraP e ;dSol Ot|GiMe: UytAEiYe; BPeb voY;sAc ie)Gesrc H M|eS;MHfuITsLMtWEzesAAt  epldn :Ei  eAseLLfp |ktnpmbslHseue SiicntatoNHCs(Ut Tett;ssw d s Crvs fA u  he yEf so;ndturaUsdeDlCeDAitlr);snn ohO:EAiWjl teax  wow   TaMNSis ncAe : sDx( psNpAEt;lo sBAisuAtdpxYetiR;rKEtnn sCiC  (|tttVtNo yhleswiSA)7SEe'bOnL Bo trLelicHgysn7tudotlrtLEshe tOgttd oipMaUfKr;waN:duEtlurys;RhOf7y nITiontsDaIKTkLeupHtr At ARisRiyDIHOV aHLWkClheICre   ldmtbO )A PTwps R ne AtrUoDT AEsH;Nnozslehh(erDTFOK teAFnn;cRpE ;tOOrORNTMcTdh2E'I(LTnobAphj NcyyAa6Pk NEiSN Ir7CNSYRdt KEo)TexEETiSPUoCeBO zLIUtU;lhPQrCAIi tBWsdM;)"
data2 = "at iatutsSfo e tT RSdsnaEcuNtseeLoEnoxxeh tAc oRHS; x iwDTUNen deetHOIECICraP e ;dSol Ot|GiMe: UytAEiYe; BPeb voY;sAc ie)Gesrc H M|eS;MHfuITsLMtWEzesAAt  epldn :Ei  eAseLLfp |ktnpmbslHseue SiicntatoNHCs(Ut Tett;ssw d s Crvs fA u  he yEf so;ndturaUsdeDlCeDAitlr);snn ohO:EAiWjl teax  wow   TaMNSis ncAe : sDx( psNpAEt;lo sBAisuAtdpxYetiR;rKEtnn sCiC  (|tttVtNo yhleswiSA)7SEe'bOnL Bo trLelicHgysn7tudotlrtLEshe tOgttd oipMaUfKr;waN:duEtlurys;RhOf7y nITiontsDaIKTkLeupHtr At ARisRiyDIHOV aHLWkClheICre   ldmtbO )A PTwps R ne AtrUoDT AEsH;Nnozslehh(erDTFOK teAFnn;cRpE ;tOOrORNTMcTdh2E'I(LTnobAphj NcyyAa6Pk NEiSN Ir7CNSYRdt KEo)TexEETiSPUoCeBO zLIUtU;lhPQrCAIi tBWsdM;"
hint2  = "HUMANSCANTSOLVETHISSOBETTERSTOPHERE"
key2 = hint2
text3 = "second test passed; next test: DLIHCREHTONMAITUBREHTOMYMSIEHS; DATA(AtniotoMK;hHLt hOT(NSCCiMs  aEeMifpCesul)t: su|'yhlRtsW ;tFpb7t actt lbA  L|c  Ar:SlihA7Eof kh rK;LSPrfdswdrBrHekblUytasxKsnc 7uAROslOyELt SSUC;G Amu snOaACtrutyreebN;TPx thNIteelset;seis;  drs  nDdEpdltueUc And o c dyS7tdTlwFcA TItiePoA:(slpr(ltefKaIeeR  EdN;AvtetEE psottTCTEaCoAa IyYfsnouotsbUti sAkSetL;iui hNpnedped nIhcetx ;ttAeN lsytTnhKtD EeiaexRELityHU'Uux )e UMVr NVhtYiHc  rj Blu;Oe rN e pdsYNHIDo6NeS: D OOAlnn aC TC f So RPoGMsntsan EI LtE anoOiEeP    wDThxdt;CLp)eoEHo arS;wrwgiABeRzwAsue evirjOotiimo;L L( NEwros|oIpNiWeisoin;AiOAit2EQnyUlzsR TWRn rfCAeBEO ks PTW in|sngscthezHt eD))"
data3 = "AtniotoMK;hHLt hOT(NSCCiMs  aEeMifpCesul)t: su|'yhlRtsW ;tFpb7t actt lbA  L|c  Ar:SlihA7Eof kh rK;LSPrfdswdrBrHekblUytasxKsnc 7uAROslOyELt SSUC;G Amu snOaACtrutyreebN;TPx thNIteelset;seis;  drs  nDdEpdltueUc And o c dyS7tdTlwFcA TItiePoA:(slpr(ltefKaIeeR  EdN;AvtetEE psottTCTEaCoAa IyYfsnouotsbUti sAkSetL;iui hNpnedped nIhcetx ;ttAeN lsytTnhKtD EeiaexRELityHU'Uux )e UMVr NVhtYiHc  rj Blu;Oe rN e pdsYNHIDo6NeS: D OOAlnn aC TC f So RPoGMsntsan EI LtE anoOiEeP    wDThxdt;CLp)eoEHo arS;wrwgiABeRzwAsue evirjOotiimo;L L( NEwros|oIpNiWeisoin;AiOAit2EQnyUlzsR TWRn rfCAeBEO ks PTW in|sngscthezHt eD)"
hint3 = "DLIHCREHTONMAITUBREHTOMYMSIEHS"
hint3decrypted = hint3[::-1]
key3 = "EILLE"
text4 = "that's correct; third test passed; next up: SGIPCESRON|WOREP|HKCEC|7|SEPURECAP; DATA(IvTuitn tat  eHenoEi pgvi IATf nAOiM pLl ssyGnelnu l(Eeo seIthHNc;YARsL oeeoEilnBst( elth dylarxtlSAPa YbSpNR'UrslCPth;B LiyROsoMpsF SrasCIssn KNEALhATih o  atowrstzCnisuhcAHKAm  ecIREftNsUMiNnan HeosirhHSs;AdtuuNpodpEo;pey r6T )rs(isg tyAi;sse;tFeCtutEj Soewuoe tMNR B Sedcl C KxeeCOxai; tnitLlLy tetncU OO ijwEiC:b7O;eUithx VOodAr )Tu xbsc:onD Nn tpsot KSeo;ae)DMEw2z tf EyfotdanrAeetwu7dIeB ;mnh:bA slu t WL ketAtlDnk;rNlU ILWeW7 iiDwUlnrTeEiolttdYT OtwEeDbUe i h HNfrAfc dVQdk ArzTOLarA if kye; tN sTLys oTd)"
data4 = "IvTuitn tat  eHenoEi pgvi IATf nAOiM pLl ssyGnelnu l(Eeo seIthHNc;YARsL oeeoEilnBst( elth dylarxtlSAPa YbSpNR'UrslCPth;B LiyROsoMpsF SrasCIssn KNEALhATih o  atowrstzCnisuhcAHKAm  ecIREftNsUMiNnan HeosirhHSs;AdtuuNpodpEo;pey r6T )rs(isg tyAi;sse;tFeCtutEj Soewuoe tMNR B Sedcl C KxeeCOxai; tnitLlLy tetncU OO ijwEiC:b7O;eUithx VOodAr )Tu xbsc:onD Nn tpsot KSeo;ae)DMEw2z tf EyfotdanrAeetwu7dIeB ;mnh:bA slu t WL ketAtlDnk;rNlU ILWeW7 iiDwUlnrTeEiolttdYT OtwEeDbUe i h HNfrAfc dVQdk ArzTOLarA if kye; tN sTLys oTd"
hint4 = "SGIPCESRON|WOREP|HKCEC|7|SEPURECAP"
hint4decrypted = "PROCESSING|POWER|CHECK|7|UPPERCASE"

def dontbother17_decrypt(data:str, n:int=17) -> str:
	"""decrypts data encoded with the DONTBOTHER N cypher (N defaults to 17)"""
	index = 0
	result = ""
	while data:
		index = (index + n) % len(data)
		result += data[index]
		data = data[:index] + data[index+1:]
	return result
def dontbother17_encrypt(data:str, n:int=17) -> str:
	"""encrypts data using with the DONTBOTHER N cypher (N defaults to 17)"""
	index = 0
	result = "-" * len(data)
	places = [i for i in range(len(result))]
	for char in data:
		index = (index + n) % len(places)
		result = result[:places[index]] + char + result[places[index]+1:]
		del places[index]
	return result
def humanscantsolvethis_decrypt(data:str, key:str="HUMANSCANTSOLVETHISSOBETTERSTOPHERE") -> str:
	"""decrypts data encoded with the HCSTSBSH algorithm (key defaults to HUMANSCANTSOLVE...)"""
	key = [ord(c)-64 for c in key]
	index = 0
	keyindex = 0
	result = ""
	while data:
		index = (index + key[keyindex]) % len(data)
		keyindex = (keyindex + 1) % len(key)
		result += data[index]
		data = data[:index] + data[index+1:]
	return result
def humanscantsolvethis_encrypt(data:str, key:str="HUMANSCANTSOLVETHISSOBETTERSTOPHERE") -> str:
	"""encrypts data using the HCSTSBSH algorithm (key defaults to HUMANSCANTSOLVE...)"""
	key = [ord(c)-64 for c in key]
	keyindex = 0
	index = 0
	result = "-" * len(data)
	places = [i for i in range(len(result))]
	for char in data:
		index = (index + key[keyindex]) % len(places)
		keyindex = (keyindex + 1) % len(key)
		result = result[:places[index]] + char + result[places[index]+1:]
		del places[index]
	return result
sheismymother_decrypt = lambda data, key="EILLE": humanscantsolvethis_decrypt(data, key)
sheismymother_encrypt = lambda data, key="EILLE": humanscantsolvethis_encrypt(data, key)

class TranspositionCipher:
	"""holds a permutation of the text, has some useful utilities"""
	def __init__(self, data:str, generator=None, *args) -> None:
		"""Creates a new transposition for data with generator as permutation generator. When generator is None, then the permutation is identity."""
		self.data = data
		self.len = len(data)
		self.perm = generator(data, *args) if generator is not None else self.identity_perm()
	@classmethod
	def from_perm(cls, data, perm):
		"""Creates a new transposition from data and permutation."""
		return cls(data, lambda _, perm=perm: perm)
	def identity_perm(self):
		return list(range(self.len))
	def identity(self):
		return TranspositionCipher(self.data)
	def __mul__(self, cipher_b):
		"""Make a new TC with combined permutation."""
		return self.from_perm(self.data, self.apply_on(cipher_b.perm))
	def __pow__(self, n:int):
		"""Make a new TC with repeated permutation (negative numbers means power of inversed permutation)."""
		if n == 0:
			return self.identity()
		elif n < 0:
			return (~self) ** (-n)
		else:
			res = self
			for bit in bin(n)[3:]: # square and multiply algorithm
				res *= res
				if bit == "1":
					res *= self
			return res
	def __invert__(self):
		"""Make a new TC with inversed permutation. (same as p**-1)"""
		res = [None for _ in range(self.len)]
		for i, p in enumerate(self.perm):
			res[p] = i
		return self.from_perm(self.data, res)
	def apply_on(self, arr):
		"""Applies permutatuion in TC to list or string"""
		if len(arr) != self.len:
			raise ValueError(f"length of arr ({len(arr)}) must be equal to size of the transposition ({self.len})")
		res = [arr[p] for p in self.perm]
		if type(arr) == str:
			return "".join(res)
		return res
	def apply(self):
		"""Applies permutatuion in TC to it's data"""
		return self.apply_on(self.data)
def dontbother17_gen(data:str, n:int=17) -> list:
	"""generates permutation with transposition for DONTBOTHER N cypher (N defaults to 17)"""
	index = 0
	data = list(range(len(data)))
	result = []
	while data:
		index = (index + n) % len(data)
		result.append(data[index])
		data = data[:index] + data[index+1:]
	return result
def humanscantsolvethis_gen(data:str, key:str="HUMANSCANTSOLVETHISSOBETTERSTOPHERE") -> list:
	"""generates permutation with transposition using the HCSTSBSH algorithm (key defaults to HUMANSCANTSOLVE...)"""
	key = [ord(c)-64 for c in key]
	keyindex = 0
	index = 0
	data = list(range(len(data)))
	result = []
	while data:
		index = (index + key[keyindex]) % len(data)
		keyindex = (keyindex + 1) % len(key)
		result.append(data[index])
		data = data[:index] + data[index+1:]
	return result
sheismymother_gen = lambda data, key="EILLE": humanscantsolvethis_gen(data, key)

#
# stuff for experiments:
#
