from collections import Counter

__all__ = ["text1", "data1", "hint1", "text2", "data2", "hint2", "key2",\
	"text3", "data3", "hint3", "hint3decrypted", "key3", "text4", "data4", "hint4", "hint4decrypted", "key4",\
	"text5", "data5", "hint5",\
	"dontbother17_decrypt", "dontbother17_encrypt", "humanscantsolvethis_decrypt", "humanscantsolvethis_encrypt",\
	"sheismymother_decrypt","sheismymother_encrypt", "processingpowercheck_decrypt","processingpowercheck_encrypt",\
	"intelligencecheck_decrypt", "intelligencecheck_encrypt",\
	"rev5", "rev5_full",\
	"mask_data", "frequency", "frequency_categories", "l2_min_remove"]

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
def intelligencecheck_decrypt(data:str, key:list) -> str:
	"""decrypts data encoded with the L5 algorithm"""
	index = 0
	keyindex = 0
	result = ""
	while data:
		index = ((index + key[keyindex]) % len(data) + len(data)) % len(data)
		keyindex = (keyindex + 1) % len(key)
		result += data[index]
		data = data[:index] + data[index+1:]
	return result
def intelligencecheck_encrypt(data:str, key:list) -> str:
	"""encrypts data using the L5 algorithm"""
	keyindex = 0
	index = 0
	result = "-" * len(data)
	places = [i for i in range(len(result))]
	for char in data:
		index = ((index + key[keyindex]) % len(places) + len(places)) % len(places)
		keyindex = (keyindex + 1) % len(key)
		result = result[:places[index]] + char + result[places[index]+1:]
		del places[index]
	return result

def mask_data(data:str, shown_chars:str, mask_char:str='.') -> str:
	"""replaces all characters that aren't in shown__hars with mask_char"""
	return "".join([c if c in shown_chars else mask_char for c in data])
def frequency(data:str) -> str:
	"""generates a formatted string with character frequencies in data (it's the format used in the doc)"""
	counter = Counter(sorted(data))
	counts = [(counter[char], char) for char in counter]
	return " ".join([('⎵' if char == ' ' else char) + "-" + str(count) for count, char in reversed(sorted(counts))])
def frequency_categories(data:str, categories:list=["abcdefghijklmnopqrstuvwxyz","ABCDEFGHIJKLMNOPQRSTUVWXYZ","0123456789","();|:,"," "],
		category_names:list=["lower","upper","numbers","special/splitters","space"]) -> str:
	"""generates a formatted string with character frequencies in data, but characters are clumped into categories
	(format from doc for this, so far only in L5 - DATA properties)"""
	result = {cat:0 for cat in categories}
	result["*"] = 0
	category_names.append("other")
	for c in data:
		for k in result:
			if c in k:
				result[k] += 1
				break
		else:
			result["*"] += 1
	neat_out = [category_names[i] + "-" + str(result[k]) for i, k in enumerate(result)]
	return "\n".join(neat_out)
def l2_min_remove(data:str, result:str) -> int:
	"""finds out the amount of used up characters requied in order to make the result appear for the first time
	(note that this function can be pretty resource intensive (exponentially), use with short results, which contain nonfrequent characters)"""
	all_indices = []
	for resc in result:
		all_indices.append([i for i, c in enumerate(data) if c == resc])
	def calc_remove(path:list) -> int:
		delta = [x-path[i-1] for i, x in list(enumerate(path))[1:]]
		delta = [x+len(data) if x < 0 else x for x in delta]
		rem_needed = [max(x-27, 0) for x in delta]
		return sum(rem_needed)
	min_remove_yet = len(data)
	path = []
	def search(depth:int=0):
		nonlocal path
		if depth >= len(all_indices) - 1:
			nonlocal min_remove_yet
			for i in all_indices[depth]:
				rem = calc_remove([*path, i])
				if rem < min_remove_yet:
					min_remove_yet = rem
		else:
			for i in all_indices[depth]:
				if i not in path:
					path.append(i)
					search(depth + 1)
					path.pop()
				if min_remove_yet == 0:
					break # early exit
	search()
	return min_remove_yet

def rev5(data:str, req:str) -> list:
	out = []
	at = 0
	for x in req:
		i = data.index(x)
		out.append((i-at)%len(data))
		at = i
		data = data[:at] + data[at+1:]
	return out
def overflow_range(minimum:int, maximum:int, value:int, mod:int):
	while value > minimum + mod:
		value -= mod
	while value < minimum:
		value += mod
	return range(value, maximum, mod)
def rev5_full(data:str, result:str, min_skip:int=1, max_skip:int=26, at:int=0):
	if len(result) == 1:
		for s in [skp for i, letter in enumerate(data) for skp in overflow_range(min_skip, max_skip, i-at, len(data)) if letter == result[0]]:
			yield [s%len(data)]
	else:
		for s in [skp for i, letter in enumerate(data) for skp in overflow_range(min_skip, max_skip, i-at, len(data)) if letter == result[0]]:
			i = at+s%len(data)
			for n in rev5_full(data[:i] + data[i+1:], result[1:], min_skip, max_skip, i):
				yield [s, *n]

#
# copy python impls:
#

py_dontbother17_decrypt = dontbother17_decrypt
py_dontbother17_encrypt = dontbother17_encrypt
py_humanscantsolvethis_decrypt = humanscantsolvethis_decrypt
py_humanscantsolvethis_encrypt = humanscantsolvethis_encrypt
py_sheismymother_decrypt = sheismymother_decrypt
py_sheismymother_encrypt = sheismymother_encrypt
py_processingpowercheck_decrypt = processingpowercheck_decrypt
py_processingpowercheck_encrypt = processingpowercheck_encrypt
py_intelligencecheck_decrypt = intelligencecheck_decrypt
py_intelligencecheck_encrypt = intelligencecheck_encrypt
py_mask_data = mask_data
py_frequency = frequency
py_frequency_categories = frequency_categories
py_min_remove = l2_min_remove
py_rev5 = rev5
py_rev5_full = rev5_full
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
	c_wys_lib.dontbother17_decrypt.argtypes = [ctypes.c_char_p, ctypes.c_uint, ctypes.c_char_p, ctypes.c_uint]
	c_wys_lib.dontbother17_encrypt.argtypes = [ctypes.c_char_p, ctypes.c_uint, ctypes.c_char_p, ctypes.c_uint]
	c_wys_lib.humanscantsolvethis_decrypt.argtypes = [ctypes.c_char_p, ctypes.c_uint, ctypes.c_char_p, ctypes.c_uint, ctypes.c_char_p]
	c_wys_lib.humanscantsolvethis_encrypt.argtypes = [ctypes.c_char_p, ctypes.c_uint, ctypes.c_char_p, ctypes.c_uint, ctypes.c_char_p]
	
	c_wys_lib.dontbother17_decrypt.restype = None
	c_wys_lib.dontbother17_encrypt.restype = None
	c_wys_lib.humanscantsolvethis_decrypt.restype = None
	c_wys_lib.humanscantsolvethis_encrypt.restype = None
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
