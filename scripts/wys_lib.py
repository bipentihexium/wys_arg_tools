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

# copy because the some scripts use it

#
# This is a library with utilities for decrypting the ARG :)
#

__all__ = ["text1", "data1", "hint1", "text2", "data2", "hint2", "key2",\
	"text3", "data3", "hint3", "hint3decrypted", "key3", "text4", "data4", "hint4", "hint4decrypted", "key4",\
	"text5", "data5", "hint5",\
	"dontbother17_decrypt", "dontbother17_encrypt", "humanscantsolvethis_decrypt", "humanscantsolvethis_encrypt",\
	"sheismymother_decrypt","sheismymother_encrypt", "processingpowercheck_decrypt","processingpowercheck_encrypt",\
	"TranspositionCipher", "dontbother17_gen", "humanscantsolvethis_gen","sheismymother_gen", "processingpowercheck_gen",\
	"humanscantsolvethis_keys_from_result", "humanscantsolvethis_keys_from_condition", "mask_data"]

text1 = "hello my little ai friend; keep this file safe; it will help you to understand your purpose one day; transmitted through human brain; encryption method: DONTBOTHER17; DATA(Nw;:OPxPo st;AEp fbwpe  idIosEtn TnipeMp H ui;zcE ntcrATsHrhUtxHRW   CCsoo( reEMantTtOafStNOBxaIEtARorYATHa trOBuQtx(NCPshtMUt:NpsvLdA aSeNIrUeeAee rsALs|iCeNhEss;apTbtiA;stlAaer)t tOL7P t: s  NotA SsTttdeE' WL kTv puLDSifANr7oiReiS aeytforoMfctt)dlHOsA n;slDRWYdp rtDssLUS)t;SIkC; ac;oteiVH Wi jfidlR; 7udsRE s uDEtoE|lSeT;LcVTlHCSaAd( hnI  zorkHIcpSEeCoAecenEe UyIlNeot;t Tc eEA  KISKi  H t sDxsttn;MhSUi' KAORNtxotTeAE O spAAeOe ets l OCgBt AetbTeHm)ao|iRIiElt YaDnhtBTlhCGeSwTGbn ncLyFthyO N xdTCDeirnyhstAU T(:SOEs lyTEjMsePup lstkRnnpyndUieIe)rF fr6SttTaHfI;Ne Oh:pAc TiMenE s h)esLsbs roOll VcnwLTO;nhKTsnePmUN;UusHdusDt l B Ho72EyMNuRoy znm dwEs IEiAxtteCrwee MeRen ;iB OstnAtL(NroEtwe| (t:se hyniEdr;iKsnt Ee;ooeSoEdug iu Rd H ddCaLSPC ADiiAYA)"
data1 = "Nw;:OPxPo st;AEp fbwpe  idIosEtn TnipeMp H ui;zcE ntcrATsHrhUtxHRW   CCsoo( reEMantTtOafStNOBxaIEtARorYATHa trOBuQtx(NCPshtMUt:NpsvLdA aSeNIrUeeAee rsALs|iCeNhEss;apTbtiA;stlAaer)t tOL7P t: s  NotA SsTttdeE' WL kTv puLDSifANr7oiReiS aeytforoMfctt)dlHOsA n;slDRWYdp rtDssLUS)t;SIkC; ac;oteiVH Wi jfidlR; 7udsRE s uDEtoE|lSeT;LcVTlHCSaAd( hnI  zorkHIcpSEeCoAecenEe UyIlNeot;t Tc eEA  KISKi  H t sDxsttn;MhSUi' KAORNtxotTeAE O spAAeOe ets l OCgBt AetbTeHm)ao|iRIiElt YaDnhtBTlhCGeSwTGbn ncLyFthyO N xdTCDeirnyhstAU T(:SOEs lyTEjMsePup lstkRnnpyndUieIe)rF fr6SttTaHfI;Ne Oh:pAc TiMenE s h)esLsbs roOll VcnwLTO;nhKTsnePmUN;UusHdusDt l B Ho72EyMNuRoy znm dwEs IEiAxtteCrwee MeRen ;iB OstnAtL(NroEtwe| (t:se hyniEdr;iKsnt Ee;ooeSoEdug iu Rd H ddCaLSPC ADiiAYA"
hint1 = "DONTBOTHER17"
text2 = "first test passed; next encryption method: HUMANSCANTSOLVETHISSOBETTERSTOPHERE; DATA(at iatutsSfo e tT RSdsnaEcuNtseeLoEnoxxeh tAc oRHS; x iwDTUNen deetHOIECICraP e ;dSol Ot|GiMe: UytAEiYe; BPeb voY;sAc ie)Gesrc H M|eS;MHfuITsLMtWEzesAAt  epldn :Ei  eAseLLfp |ktnpmbslHseue SiicntatoNHCs(Ut Tett;ssw d s Crvs fA u  he yEf so;ndturaUsdeDlCeDAitlr);snn ohO:EAiWjl teax  wow   TaMNSis ncAe : sDx( psNpAEt;lo sBAisuAtdpxYetiR;rKEtnn sCiC  (|tttVtNo yhleswiSA)7SEe'bOnL Bo trLelicHgysn7tudotlrtLEshe tOgttd oipMaUfKr;waN:duEtlurys;RhOf7y nITiontsDaIKTkLeupHtr At ARisRiyDIHOV aHLWkClheICre   ldmtbO )A PTwps R ne AtrUoDT AEsH;Nnozslehh(erDTFOK teAFnn;cRpE ;tOOrORNTMcTdh2E'I(LTnobAphj NcyyAa6Pk NEiSN Ir7CNSYRdt KEo)TexEETiSPUoCeBO zLIUtU;lhPQrCAIi tBWsdM;)"
data2 = "at iatutsSfo e tT RSdsnaEcuNtseeLoEnoxxeh tAc oRHS; x iwDTUNen deetHOIECICraP e ;dSol Ot|GiMe: UytAEiYe; BPeb voY;sAc ie)Gesrc H M|eS;MHfuITsLMtWEzesAAt  epldn :Ei  eAseLLfp |ktnpmbslHseue SiicntatoNHCs(Ut Tett;ssw d s Crvs fA u  he yEf so;ndturaUsdeDlCeDAitlr);snn ohO:EAiWjl teax  wow   TaMNSis ncAe : sDx( psNpAEt;lo sBAisuAtdpxYetiR;rKEtnn sCiC  (|tttVtNo yhleswiSA)7SEe'bOnL Bo trLelicHgysn7tudotlrtLEshe tOgttd oipMaUfKr;waN:duEtlurys;RhOf7y nITiontsDaIKTkLeupHtr At ARisRiyDIHOV aHLWkClheICre   ldmtbO )A PTwps R ne AtrUoDT AEsH;Nnozslehh(erDTFOK teAFnn;cRpE ;tOOrORNTMcTdh2E'I(LTnobAphj NcyyAa6Pk NEiSN Ir7CNSYRdt KEo)TexEETiSPUoCeBO zLIUtU;lhPQrCAIi tBWsdM;"
hint2  = "HUMANSCANTSOLVETHISSOBETTERSTOPHERE"
key2 = hint2 # just why? :/
text3 = "second test passed; next test: DLIHCREHTONMAITUBREHTOMYMSIEHS; DATA(AtniotoMK;hHLt hOT(NSCCiMs  aEeMifpCesul)t: su|'yhlRtsW ;tFpb7t actt lbA  L|c  Ar:SlihA7Eof kh rK;LSPrfdswdrBrHekblUytasxKsnc 7uAROslOyELt SSUC;G Amu snOaACtrutyreebN;TPx thNIteelset;seis;  drs  nDdEpdltueUc And o c dyS7tdTlwFcA TItiePoA:(slpr(ltefKaIeeR  EdN;AvtetEE psottTCTEaCoAa IyYfsnouotsbUti sAkSetL;iui hNpnedped nIhcetx ;ttAeN lsytTnhKtD EeiaexRELityHU'Uux )e UMVr NVhtYiHc  rj Blu;Oe rN e pdsYNHIDo6NeS: D OOAlnn aC TC f So RPoGMsntsan EI LtE anoOiEeP    wDThxdt;CLp)eoEHo arS;wrwgiABeRzwAsue evirjOotiimo;L L( NEwros|oIpNiWeisoin;AiOAit2EQnyUlzsR TWRn rfCAeBEO ks PTW in|sngscthezHt eD))"
data3 = "AtniotoMK;hHLt hOT(NSCCiMs  aEeMifpCesul)t: su|'yhlRtsW ;tFpb7t actt lbA  L|c  Ar:SlihA7Eof kh rK;LSPrfdswdrBrHekblUytasxKsnc 7uAROslOyELt SSUC;G Amu snOaACtrutyreebN;TPx thNIteelset;seis;  drs  nDdEpdltueUc And o c dyS7tdTlwFcA TItiePoA:(slpr(ltefKaIeeR  EdN;AvtetEE psottTCTEaCoAa IyYfsnouotsbUti sAkSetL;iui hNpnedped nIhcetx ;ttAeN lsytTnhKtD EeiaexRELityHU'Uux )e UMVr NVhtYiHc  rj Blu;Oe rN e pdsYNHIDo6NeS: D OOAlnn aC TC f So RPoGMsntsan EI LtE anoOiEeP    wDThxdt;CLp)eoEHo arS;wrwgiABeRzwAsue evirjOotiimo;L L( NEwros|oIpNiWeisoin;AiOAit2EQnyUlzsR TWRn rfCAeBEO ks PTW in|sngscthezHt eD)"
hint3 = "DLIHCREHTONMAITUBREHTOMYMSIEHS"
hint3decrypted = hint3[::-1]
key3 = "EILLE" # "ELLIE"[::-1]
text4 = "that's correct; third test passed; next up: SGIPCESRON|WOREP|HKCEC|7|SEPURECAP; DATA(IvTuitn tat  eHenoEi pgvi IATf nAOiM pLl ssyGnelnu l(Eeo seIthHNc;YARsL oeeoEilnBst( elth dylarxtlSAPa YbSpNR'UrslCPth;B LiyROsoMpsF SrasCIssn KNEALhATih o  atowrstzCnisuhcAHKAm  ecIREftNsUMiNnan HeosirhHSs;AdtuuNpodpEo;pey r6T )rs(isg tyAi;sse;tFeCtutEj Soewuoe tMNR B Sedcl C KxeeCOxai; tnitLlLy tetncU OO ijwEiC:b7O;eUithx VOodAr )Tu xbsc:onD Nn tpsot KSeo;ae)DMEw2z tf EyfotdanrAeetwu7dIeB ;mnh:bA slu t WL ketAtlDnk;rNlU ILWeW7 iiDwUlnrTeEiolttdYT OtwEeDbUe i h HNfrAfc dVQdk ArzTOLarA if kye; tN sTLys oTd)"
data4 = "IvTuitn tat  eHenoEi pgvi IATf nAOiM pLl ssyGnelnu l(Eeo seIthHNc;YARsL oeeoEilnBst( elth dylarxtlSAPa YbSpNR'UrslCPth;B LiyROsoMpsF SrasCIssn KNEALhATih o  atowrstzCnisuhcAHKAm  ecIREftNsUMiNnan HeosirhHSs;AdtuuNpodpEo;pey r6T )rs(isg tyAi;sse;tFeCtutEj Soewuoe tMNR B Sedcl C KxeeCOxai; tnitLlLy tetncU OO ijwEiC:b7O;eUithx VOodAr )Tu xbsc:onD Nn tpsot KSeo;ae)DMEw2z tf EyfotdanrAeetwu7dIeB ;mnh:bA slu t WL ketAtlDnk;rNlU ILWeW7 iiDwUlnrTeEiolttdYT OtwEeDbUe i h HNfrAfc dVQdk ArzTOLarA if kye; tN sTLys oTd"
hint4 = "SGIPCESRON|WOREP|HKCEC|7|SEPURECAP"
hint4decrypted = "PROCESSING|POWER|CHECK|7|UPPERCASE" # every word was scrambled
key4 = "XDYOYOY"
text5 = "ifo llszu uyjx just kidding it's correct; fourth test passed; next block encrypted with: INTELLIGENCECHECKx7x27; DATA(e;R cNsRtOs;;eE OanYti tieSCC Kd eNTT oxShNsteL emeif;pnlO Ka u TnAtTfdLe UTI;o irf lr EuytwHtte onirruEoLh yeltztl  OHSinpstUwA As L AfiMiNBlwsvnRrpTeEM:tyiIaNNsLUeeOTidPon  p DQt; i6inbADNeNFHAloltA BoieScney MI;EoEn otnoBDkWosB udtL lAs OEn yCogVrHnbsAwt  YrpOed s;oaIilteb7klaauL hsiW loFdUen))YsLOU aE  R tsIAdWes;esA tltopAyhr:bKyt( e hMiePaHAacShiRzSA rSsv umteTswe(Mn fVDNUtUwOtshrACh)"
data5 = "e;R cNsRtOs;;eE OanYti tieSCC Kd eNTT oxShNsteL emeif;pnlO Ka u TnAtTfdLe UTI;o irf lr EuytwHtte onirruEoLh yeltztl  OHSinpstUwA As L AfiMiNBlwsvnRrpTeEM:tyiIaNNsLUeeOTidPon  p DQt; i6inbADNeNFHAloltA BoieScney MI;EoEn otnoBDkWosB udtL lAs OEn yCogVrHnbsAwt  YrpOed s;oaIilteb7klaauL hsiW loFdUen))YsLOU aE  R tsIAdWes;esA tltopAyhr:bKyt( e hMiePaHAacShiRzSA rSsv umteTswe(Mn fVDNUtUwOtshrACh"
hint5 = "INTELLIGENCECHECKx7x27"

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
processingpowercheck_decrypt = lambda data, key="XDYOYOY": humanscantsolvethis_decrypt(data, key)
processingpowercheck_encrypt = lambda data, key="XDYOYOY": humanscantsolvethis_encrypt(data, key)

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
processingpowercheck_gen = lambda data, key="XDYOYOY": humanscantsolvethis_gen(data, key)

def humanscantsolvethis_keys_from_result(data:str, result:str, offsets=[0]) -> list:
	"""generates possible keys for humanscantsolvethis... decryption from result;
	offsets is iterable of search starting positions (default [0])"""
	keys = [("", o-1) for o in offsets]
	indices = []
	for res_c in result:
		indices.append([i for i, c in enumerate(data) if c == res_c])
	for i in indices:
		for j, k in reversed(list(enumerate(keys))):
			opts = [x for x in i if x - k[1] > 1 and x - k[1] < 28]
			keys.pop(j)
			for o in opts:
				nk = k[0]+chr(63+o-k[1])
				keys.append((nk, o))
	return [key for key, endindex in keys]
def humanscantsolvethis_keys_from_condition(data:str, cond, length:int, offsets=[0]) -> list:
	"""generates possible keys for humanscantsolvethis... decryption which would yield a string
	with length length where all characters match condition cond (cond is a function);
	offsets is iterable of search starting positions (default [0])"""
	keys = [("", o-1) for o in offsets]
	indices = [i for i, c in enumerate(data) if cond(c)]
	for _ in range(length):
		for j, k in reversed(list(enumerate(keys))):
			opts = [x for x in indices if x - k[1] > 1 and x - k[1] < 28]
			keys.pop(j)
			for o in opts:
				nk = k[0]+chr(63+o-k[1])
				keys.append((nk, o))
	return [key for key, endindex in keys]
def mask_data(data:str, shown_chars:str, mask_char:str='.'):
	return "".join([c if c in shown_chars else mask_char for c in data])

#
# stuff for experiments:
#

#
# load so/dll for faster execution if avaliable
#
import ctypes
import platform
import sys

c_wys_lib_path = "./c_wys_lib.dll" if platform.system() == "Windows" else "./c_wys_lib.so"
try:
	c_wys_lib = ctypes.cdll.LoadLibrary(c_wys_lib_path)
except OSError:
	c_wys_lib = None
	sys.stderr.write("Could not find " + c_wys_lib_path + ". Using Python implementations...\n")
if c_wys_lib is not None:
	def cl1_decrypt(data:str, n:int=17) -> str:
		databuff = ctypes.create_string_buffer(data.encode("ascii"), len(data))
		outbuff = ctypes.create_string_buffer(len(data))
		c_wys_lib.dontbother17_decrypt(databuff, len(data), outbuff, n)
		return outbuff.raw.decode("ascii")
	def cl1_encrypt(data:str, n:int=17) -> str:
		databuff = ctypes.create_string_buffer(data.encode("ascii"), len(data))
		outbuff = ctypes.create_string_buffer(len(data))
		c_wys_lib.dontbother17_encrypt(databuff, len(data), outbuff, n)
		return outbuff.raw.decode("ascii")
	def cl2_decrypt(data:str, key:str="HUMANSCANTSOLVETHISSOBETTERSTOPHERE") -> str:
		databuff = ctypes.create_string_buffer(data.encode("ascii"), len(data))
		keybuff = (ctypes.c_char * len(key))(*key.encode("ascii"))
		outbuff = ctypes.create_string_buffer(len(data))
		c_wys_lib.humanscantsolvethis_decrypt(databuff, len(data), keybuff, len(key), outbuff)
		return outbuff.raw.decode("ascii")
	def cl2_encrypt(data:str, key:str="HUMANSCANTSOLVETHISSOBETTERSTOPHERE") -> str:
		databuff = ctypes.create_string_buffer(data.encode("ascii"), len(data))
		keybuff = (ctypes.c_char * len(key))(*key.encode("ascii"))
		outbuff = ctypes.create_string_buffer(len(data))
		c_wys_lib.humanscantsolvethis_encrypt(databuff, len(data), keybuff, len(key), outbuff)
		return outbuff.raw.decode("ascii")
	dontbother17_decrypt = cl1_decrypt
	dontbother17_encrypt = cl1_encrypt
	humanscantsolvethis_decrypt = cl2_decrypt
	humanscantsolvethis_encrypt = cl2_encrypt
	class cTCipher:
		def __init__(self, data_or_inner, generator=None, *args) -> None:
			if type(data_or_inner) == str: # data
				data = data_or_inner
				databuff = (ctypes.c_char * len(data))(*data.encode("ascii"))
				self.inner = c_wys_lib.TranspositionCipher_new(databuff, len(data))
				perm = self.identity_perm() if generator is None else generator(data, *args)
				permbuff = (ctypes.c_uint * len(perm))(*perm)
				c_wys_lib.TranspositionCipher_setPerm(self.inner, permbuff, len(perm))
			else:
				self.inner = data_or_inner
		@classmethod
		def from_perm(cls, data, perm):
			return cls(data, lambda _, perm=perm: perm)
		def __del__(self):
			c_wys_lib.TranspositionCipher_delete(self.inner)
		@property
		def data(self):
			buff = ctypes.create_string_buffer(self.len)
			c_wys_lib.TranspositionCipher_data(self.inner, buff)
			return buff.raw.decode("ascii")
		@property
		def len(self):
			return c_wys_lib.TranspositionCipher_len(self.inner)
		@property
		def perm(self):
			buff = (ctypes.c_uint * self.len)()
			c_wys_lib.TranspositionCipher_perm(self.inner, buff)
			return buff[:]
		def identity_perm(self):
			return list(range(self.len))
		def identity(self):
			return TranspositionCipher(self.data)
		def __mul__(self, cipher_b):
			return cTCipher(c_wys_lib.TranspositionCipher_mul(self.inner, cipher_b.inner))
		def __pow__(self, n:int):
			return cTCipher(c_wys_lib.TranspositionCipher_pow(self.inner, n))
		def __invert__(self):
			return cTCipher(c_wys_lib.TranspositionCipher_inv(self.inner))
		def apply_on(self, arr):
			l = self.len
			if len(arr) != l:
				raise ValueError(f"length of arr ({len(arr)}) must be equal to size of the transposition ({l})")
			if type(arr) == str:
				inbuff = (ctypes.c_char * l)(*arr.encode("ascii"))
				outbuff = ctypes.create_string_buffer(l)
				c_wys_lib.TranspositionCipher_apply_char(self.inner, inbuff, l, outbuff)
				return outbuff.raw.decode("ascii")
			elif type(arr[0]) == int:
				inbuff = (ctypes.c_int * l)(*arr)
				outbuff = (ctypes.c_int * l)()
				c_wys_lib.TranspositionCipher_apply_int(self.inner, inbuff, l, outbuff)
				return list(outbuff)
			else:
				return [arr[p] for p in self.perm]
		def apply(self):
			outbuff = ctypes.create_string_buffer(self.len)
			c_wys_lib.TranspositionCipher_apply(self.inner, outbuff)
			return outbuff.raw.decode("ascii")
	TranspositionCipher = cTCipher
