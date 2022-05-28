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

import os

data2 = "at iatutsSfo e tT RSdsnaEcuNtseeLoEnoxxeh tAc oRHS; x iwDTUNen deetHOIECICraP e ;dSol Ot|GiMe: UytAEiYe; BPeb voY;sAc ie)Gesrc H M|eS;MHfuITsLMtWEzesAAt  epldn :Ei  eAseLLfp |ktnpmbslHseue SiicntatoNHCs(Ut Tett;ssw d s Crvs fA u  he yEf so;ndturaUsdeDlCeDAitlr);snn ohO:EAiWjl teax  wow   TaMNSis ncAe : sDx( psNpAEt;lo sBAisuAtdpxYetiR;rKEtnn sCiC  (|tttVtNo yhleswiSA)7SEe'bOnL Bo trLelicHgysn7tudotlrtLEshe tOgttd oipMaUfKr;waN:duEtlurys;RhOf7y nITiontsDaIKTkLeupHtr At ARisRiyDIHOV aHLWkClheICre   ldmtbO )A PTwps R ne AtrUoDT AEsH;Nnozslehh(erDTFOK teAFnn;cRpE ;tOOrORNTMcTdh2E'I(LTnobAphj NcyyAa6Pk NEiSN Ir7CNSYRdt KEo)TexEETiSPUoCeBO zLIUtU;lhPQrCAIi tBWsdM;"
text3 = "second test passed; next test: DLIHCREHTONMAITUBREHTOMYMSIEHS; DATA(AtniotoMK;hHLt hOT(NSCCiMs  aEeMifpCesul)t: su|'yhlRtsW ;tFpb7t actt lbA  L|c  Ar:SlihA7Eof kh rK;LSPrfdswdrBrHekblUytasxKsnc 7uAROslOyELt SSUC;G Amu snOaACtrutyreebN;TPx thNIteelset;seis;  drs  nDdEpdltueUc And o c dyS7tdTlwFcA TItiePoA:(slpr(ltefKaIeeR  EdN;AvtetEE psottTCTEaCoAa IyYfsnouotsbUti sAkSetL;iui hNpnedped nIhcetx ;ttAeN lsytTnhKtD EeiaexRELityHU'Uux )e UMVr NVhtYiHc  rj Blu;Oe rN e pdsYNHIDo6NeS: D OOAlnn aC TC f So RPoGMsntsan EI LtE anoOiEeP    wDThxdt;CLp)eoEHo arS;wrwgiABeRzwAsue evirjOotiimo;L L( NEwros|oIpNiWeisoin;AiOAit2EQnyUlzsR TWRn rfCAeBEO ks PTW in|sngscthezHt eD))"
data3 = "AtniotoMK;hHLt hOT(NSCCiMs  aEeMifpCesul)t: su|'yhlRtsW ;tFpb7t actt lbA  L|c  Ar:SlihA7Eof kh rK;LSPrfdswdrBrHekblUytasxKsnc 7uAROslOyELt SSUC;G Amu snOaACtrutyreebN;TPx thNIteelset;seis;  drs  nDdEpdltueUc And o c dyS7tdTlwFcA TItiePoA:(slpr(ltefKaIeeR  EdN;AvtetEE psottTCTEaCoAa IyYfsnouotsbUti sAkSetL;iui hNpnedped nIhcetx ;ttAeN lsytTnhKtD EeiaexRELityHU'Uux )e UMVr NVhtYiHc  rj Blu;Oe rN e pdsYNHIDo6NeS: D OOAlnn aC TC f So RPoGMsntsan EI LtE anoOiEeP    wDThxdt;CLp)eoEHo arS;wrwgiABeRzwAsue evirjOotiimo;L L( NEwros|oIpNiWeisoin;AiOAit2EQnyUlzsR TWRn rfCAeBEO ks PTW in|sngscthezHt eD)"
data = data3

print_all = False

def humanscantsolvethis_decrypt(data, key):
	index = 0
	keyindex = 0
	result = ""
	while data:
		index = (index + ord(key[keyindex]) - 64) % len(data)
		keyindex = (keyindex + 1) % len(key)
		result += data[index]
		data = data[:index] + data[index+1:]
	return result
def humanscantsolvethis_encrypt(data, key):
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
pass_mod = lambda x: x
reverse_mod = lambda x: x[::-1]

test_methods = [humanscantsolvethis_decrypt, humanscantsolvethis_encrypt]
autotest_keys = ["DLIHCREHTONMAITUBREHTOMYMSIEHS"]
test_modifications = [pass_mod, reverse_mod]
def is_message(msg):
	return print_all or "passed; " in msg # "DATA(" in msg

def test_key(key):
	found = False
	for method in test_methods:
		for key_mod in test_modifications:
			for data_mod in test_modifications:
				unmodified_res = method(data_mod(data), key_mod(key))
				for result_mod in test_modifications:
					res = result_mod(unmodified_res)
					if is_message(res):
						print("--------------------- MESSAGE ------------------------")
						print(res)
						print("key: " + key_mod(key))
						print("data: " + data_mod(data))
						print("method: " + method.__name__)
						found = True
	if not found:
		print("Didn't find anything with key " + key)

for key in autotest_keys:
	test_key(key)
while True:
	key = input("another key (auto-capitalized)>")
	os.system("cls | clear")
	print("another key (auto-capitalized)> " + key)
	key = key.upper()
	if key == "EXIT":
		break
	elif key == "PRINTALL":
		print_all = not print_all
		continue
	test_key(key)

