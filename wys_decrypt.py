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

import sys

def dontbother17_decrypt(data, n=17):
	index = 0
	result = ""
	while data:
		index = (index + n) % len(data)
		result += data[index]
		data = data[:index] + data[index+1:]
	return result
def dontbother17_encrypt(data, n=17):
	index = -1
	result = "-" * len(data)
	for char in data:
		skip = n
		while skip >= 0:
			index = (index + 1) % len(data)
			if result[index] == "-":
				skip -= 1
		result = result[:index] + char + result[index+1:]
	return result
def humanscantsolvethis_decrypt(data, key):
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
def humanscantsolvethis_encrypt(data, key):
	key = [ord(c)-64 for c in key]
	keyindex = 0
	index = -1
	result = "-" * len(data)
	for char in data:
		skip = key[keyindex]
		while skip >= 0:
			index = (index + 1) % len(data)
			if result[index] == "-":
				skip -= 1
		keyindex = (keyindex + 1) % len(key)
		result = result[:index] + char + result[index+1:]
	return result
def sheismymother_decrypt(data, key):
	return data
"""
text1 = "hello my little ai friend; keep this file safe; it will help you to understand your purpose one day; transmitted through human brain; encryption method: DONTBOTHER17; DATA(Nw;:OPxPo st;AEp fbwpe  idIosEtn TnipeMp H ui;zcE ntcrATsHrhUtxHRW   CCsoo( reEMantTtOafStNOBxaIEtARorYATHa trOBuQtx(NCPshtMUt:NpsvLdA aSeNIrUeeAee rsALs|iCeNhEss;apTbtiA;stlAaer)t tOL7P t: s  NotA SsTttdeE' WL kTv puLDSifANr7oiReiS aeytforoMfctt)dlHOsA n;slDRWYdp rtDssLUS)t;SIkC; ac;oteiVH Wi jfidlR; 7udsRE s uDEtoE|lSeT;LcVTlHCSaAd( hnI  zorkHIcpSEeCoAecenEe UyIlNeot;t Tc eEA  KISKi  H t sDxsttn;MhSUi' KAORNtxotTeAE O spAAeOe ets l OCgBt AetbTeHm)ao|iRIiElt YaDnhtBTlhCGeSwTGbn ncLyFthyO N xdTCDeirnyhstAU T(:SOEs lyTEjMsePup lstkRnnpyndUieIe)rF fr6SttTaHfI;Ne Oh:pAc TiMenE s h)esLsbs roOll VcnwLTO;nhKTsnePmUN;UusHdusDt l B Ho72EyMNuRoy znm dwEs IEiAxtteCrwee MeRen ;iB OstnAtL(NroEtwe| (t:se hyniEdr;iKsnt Ee;ooeSoEdug iu Rd H ddCaLSPC ADiiAYA)"
data1 = text1[len("hello my little ai friend; keep this file safe; it will help you to understand your purpose one day; transmitted through human brain; encryption method: DONTBOTHER17; DATA("):-1]
text2 = dontbother17_decrypt(data1, 17)
key2 = text2[len("first test passed; next encryption method: "):len("first test passed; next encryption method: HUMANSCANTSOLVETHISSOBETTERSTOPHERE")]
data2 = text2[len("first test passed; next encryption method: HUMANSCANTSOLVETHISSOBETTERSTOPHERE; DATA("):-1]
text3 = humanscantsolvethis_decrypt(data2, key2)
key3 = text3[len("second test passed; next test: "):len("second test passed; next test: DLIHCREHTONMAITUBREHTOMYMSIEHS")]
data3 = text3[len("second test passed; next test: DLIHCREHTONMAITUBREHTOMYMSIEHS; DATA("):-1]
"""
key3 = "DLIHCREHTONMAITUBREHTOMYMSIEHS"
data3 = "AtniotoMK;hHLt hOT(NSCCiMs  aEeMifpCesul)t: su|'yhlRtsW ;tFpb7t actt lbA  L|c  Ar:SlihA7Eof kh rK;LSPrfdswdrBrHekblUytasxKsnc 7uAROslOyELt SSUC;G Amu snOaACtrutyreebN;TPx thNIteelset;seis;  drs  nDdEpdltueUc And o c dyS7tdTlwFcA TItiePoA:(slpr(ltefKaIeeR  EdN;AvtetEE psottTCTEaCoAa IyYfsnouotsbUti sAkSetL;iui hNpnedped nIhcetx ;ttAeN lsytTnhKtD EeiaexRELityHU'Uux )e UMVr NVhtYiHc  rj Blu;Oe rN e pdsYNHIDo6NeS: D OOAlnn aC TC f So RPoGMsntsan EI LtE anoOiEeP    wDThxdt;CLp)eoEHo arS;wrwgiABeRzwAsue evirjOotiimo;L L( NEwros|oIpNiWeisoin;AiOAit2EQnyUlzsR TWRn rfCAeBEO ks PTW in|sngscthezHt eD)"
#"""

try:
	with open("word_list.txt", "r") as f:
		wl = [x.strip() for x in f.readlines()]
except IOError:
	sys.stderr.write("word_list.txt not found - try_wl function will not work\n")
	wl = []
def try_wl(method, range, *args, **kw):
	if args:
		for i in range:
			try_wl(method, *args, **{**kw, chr(len(kw)+ord('0')):i})
	else:
		for i in range:
			text = eval(method)
			if "DATA(" in text and text.split(' ')[0] and text.split(' ')[0] in wl:
				print(f"<<<<<<<<<<<<<< {' '.join([str(v) for k, v in kw.items()])} {'; '.join([str(k)+'-'+str(v) for k, v in kw.items()])} {i} >>>>>>>>>>>>>>>>>>")
				print(text)
print(sheismymother_decrypt(data3, key3))
print("======================================================== NORM ===================================================")
keys = ["DLIHCREHTONMAITUBREHTOMYMSIEHS", "STEPMOM", "STEPMOTHER", "STEPSON", "STEPDAUGHTER", "HEISMYCHILDBUTIMNOTHISMOTHER", "SHEISMYCHILDBUTIMNOTHERMOTHER", "HUMANSCANTSOLVETHISSOBETTERSTOPHERE"]
try_wl("sheismymother_decrypt(data3, i)", keys)
print("======================================================== REV ====================================================")
try_wl("sheismymother_decrypt(data3, i[::-1])", keys)
