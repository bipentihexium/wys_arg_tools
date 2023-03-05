# WYS ARG - what we already solved

- [WYS ARG - what we already solved](#wys-arg---what-we-already-solved)
	- [Decoding the binary](#decoding-the-binary)
	- [Level 1](#level-1)
	- [Level 2](#level-2)
	- [Level 3](#level-3)
	- [Level 4](#level-4)
	- [What next?](#what-next)

## Decoding the binary

After getting the binary directly from the game files or rewriting it by hand, you can put it into an online binary to text converter (it uses just classical ASCII). After that, you'll get this:

```
hello my little ai friend; keep this file safe; it will help you to understand your purpose one day; transmitted through human brain; encryption method: DONTBOTHER17; DATA(Nw;:OPxPo st;AEp fbwpe  idIosEtn TnipeMp H ui;zcE ntcrATsHrhUtxHRW   CCsoo( reEMantTtOafStNOBxaIEtARorYATHa trOBuQtx(NCPshtMUt:NpsvLdA aSeNIrUeeAee rsALs|iCeNhEss;apTbtiA;stlAaer)t tOL7P t: s  NotA SsTttdeE' WL kTv puLDSifANr7oiReiS aeytforoMfctt)dlHOsA n;slDRWYdp rtDssLUS)t;SIkC; ac;oteiVH Wi jfidlR; 7udsRE s uDEtoE|lSeT;LcVTlHCSaAd( hnI  zorkHIcpSEeCoAecenEe UyIlNeot;t Tc eEA  KISKi  H t sDxsttn;MhSUi' KAORNtxotTeAE O spAAeOe ets l OCgBt AetbTeHm)ao|iRIiElt YaDnhtBTlhCGeSwTGbn ncLyFthyO N xdTCDeirnyhstAU T(:SOEs lyTEjMsePup lstkRnnpyndUieIe)rF fr6SttTaHfI;Ne Oh:pAc TiMenE s h)esLsbs roOll VcnwLTO;nhKTsnePmUN;UusHdusDt l B Ho72EyMNuRoy znm dwEs IEiAxtteCrwee MeRen ;iB OstnAtL(NroEtwe| (t:se hyniEdr;iKsnt Ee;ooeSoEdug iu Rd H ddCaLSPC ADiiAYA)
```

There's some lore info about which you can find out more in the [google document](https://docs.google.com/document/d/1e_nOhSkTh9cchh8n5yDadvf-pnoi8CBZnHwZE0dsbcI/edit#).

## Level 1

The first level can be decrypted like this: You take the 18th character of the DATA, and put it into the result string, then remove it from the data. Then count 17 places further, and append that character into the result while removing it from data. Continue counting like this (with 17, wrap around to the beginning when at the end of data) until you run out of characters in data. The algorithm can be written like this using Python:

```py
data = "..."
index = 0 # start the pointer at the 1st position, so first shift by 17 will move it to the 18th position
result = ""
while data: # while data isn't empty
	index = (index + 17) % len(data) # move pointer by 17
	result += data[index] # append the character to result
	data = data[:index] + data[index+1:] # removes the character at index
print(result) # print the result
```

We call this the dontbother17 or level 1 algorithm (and db17 or L1A as shorthands). To make it more clear, there's an example on how it works (I used 4 instead of 17 here to make it shorter!):

```
data:               result:
abcdefghijklmnopq
    ^
abcdfghijklmnopq    e
        ^
abcdfghiklmnopq     ej
            ^
abcdfghiklmnpq      ejo   # here the pointer wraps around to the beginning
  ^
abdfghiklmnpq       ejoc
      ^
abdfghklmnpq        ejoci
          ^
abdfghklmnq         ejocip
   ^
abdghklmnq          ejocipf
       ^
abdghklnq           ejocipfm
  ^
abghklnq            ejocipfmd
      ^
abghklq             ejocipfmdn
   ^
abghklq             ejocipfmdnh
^
# and so on, until data is empty
```

If you have Python with Pygame installed, you can run [visualizer/a_vis.py](visualizer/a_vis.py) from it's folder to see animated "version" of the algorithm.

After applying this algorithm on the data, you'll get this:

```
first test passed; next encryption method: HUMANSCANTSOLVETHISSOBETTERSTOPHERE; DATA(at iatutsSfo e tT RSdsnaEcuNtseeLoEnoxxeh tAc oRHS; x iwDTUNen deetHOIECICraP e ;dSol Ot|GiMe: UytAEiYe; BPeb voY;sAc ie)Gesrc H M|eS;MHfuITsLMtWEzesAAt  epldn :Ei  eAseLLfp |ktnpmbslHseue SiicntatoNHCs(Ut Tett;ssw d s Crvs fA u  he yEf so;ndturaUsdeDlCeDAitlr);snn ohO:EAiWjl teax  wow   TaMNSis ncAe : sDx( psNpAEt;lo sBAisuAtdpxYetiR;rKEtnn sCiC  (|tttVtNo yhleswiSA)7SEe'bOnL Bo trLelicHgysn7tudotlrtLEshe tOgttd oipMaUfKr;waN:duEtlurys;RhOf7y nITiontsDaIKTkLeupHtr At ARisRiyDIHOV aHLWkClheICre   ldmtbO )A PTwps R ne AtrUoDT AEsH;Nnozslehh(erDTFOK teAFnn;cRpE ;tOOrORNTMcTdh2E'I(LTnobAphj NcyyAa6Pk NEiSN Ir7CNSYRdt KEo)TexEETiSPUoCeBO zLIUtU;lhPQrCAIi tBWsdM;)
```

## Level 2

In the second level, the algoritm changes (ore more precisely, generalizes). Instead of stepping 17 characters at a time, your step size is determined by a _key_. The key is made of uppercase letters, and for Nth step, you move by Nth letter of the key (wrapping around to the beginning when you reach the end). The step size for `A` is 1, step size for `B` is 2, step size for `C` is 3 and so on. We call these _letter numbers_. This can be implemented in Python like this:

```py
key = "..."
data = "..."
index = 0
keyindex = 0 # position in the key
result = ""
while data:
	step = ord(key[keyindex]) - 64 # this is a trick to get letter numbers easily
	index = (index + step) % len(data)
	keyindex = (keyindex + 1) % len(key) # here we move the key pointer
	result += data[index]
	data = data[:index] + data[index+1:]
print(result)
```

As you can see, it's really similar to db17. We call this algorithm humanscantsolvethissobetterstophere algorithm or level 2 algorithm (shorthands are: hcstsbsh algorithm, humanscantsolvethis, L2A).

The key for this level is `HUMANSCANTSOLVETHISSOBETTERSTOPHERE`. By decrypting the data using this key, you'll get:

```
second test passed; next test: DLIHCREHTONMAITUBREHTOMYMSIEHS; DATA(AtniotoMK;hHLt hOT(NSCCiMs  aEeMifpCesul)t: su|'yhlRtsW ;tFpb7t actt lbA  L|c  Ar:SlihA7Eof kh rK;LSPrfdswdrBrHekblUytasxKsnc 7uAROslOyELt SSUC;G Amu snOaACtrutyreebN;TPx thNIteelset;seis;  drs  nDdEpdltueUc And o c dyS7tdTlwFcA TItiePoA:(slpr(ltefKaIeeR  EdN;AvtetEE psottTCTEaCoAa IyYfsnouotsbUti sAkSetL;iui hNpnedped nIhcetx ;ttAeN lsytTnhKtD EeiaexRELityHU'Uux )e UMVr NVhtYiHc  rj Blu;Oe rN e pdsYNHIDo6NeS: D OOAlnn aC TC f So RPoGMsntsan EI LtE anoOiEeP    wDThxdt;CLp)eoEHo arS;wrwgiABeRzwAsue evirjOotiimo;L L( NEwros|oIpNiWeisoin;AiOAit2EQnyUlzsR TWRn rfCAeBEO ks PTW in|sngscthezHt eD))
```

## Level 3

This level uses the same algorithm as the previous one - L2A. Here, if you reverse the _hint_ - `DLIHCREHTONMAITUBREHTOMYMSIEHS`, you'll get `SHEISMYMOTHERBUTIAMNOTHERCHILD`. That is a "riddle" that is needed to be solved in order to get the key (She is my mother, but I am not her child.). The answer to this is Ellie (lore thing :) ) giving us the key `ELLIE`. But we need to reverse it, because the hint was reversed, so the key is `EILLE`. Decrypting the data gives you the following:

```
that's correct; third test passed; next up: SGIPCESRON|WOREP|HKCEC|7|SEPURECAP; DATA(IvTuitn tat  eHenoEi pgvi IATf nAOiM pLl ssyGnelnu l(Eeo seIthHNc;YARsL oeeoEilnBst( elth dylarxtlSAPa YbSpNR'UrslCPth;B LiyROsoMpsF SrasCIssn KNEALhATih o  atowrstzCnisuhcAHKAm  ecIREftNsUMiNnan HeosirhHSs;AdtuuNpodpEo;pey r6T )rs(isg tyAi;sse;tFeCtutEj Soewuoe tMNR B Sedcl C KxeeCOxai; tnitLlLy tetncU OO ijwEiC:b7O;eUithx VOodAr )Tu xbsc:onD Nn tpsot KSeo;ae)DMEw2z tf EyfotdanrAeetwu7dIeB ;mnh:bA slu t WL ketAtlDnk;rNlU ILWeW7 iiDwUlnrTeEiolttdYT OtwEeDbUe i h HNfrAfc dVQdk ArzTOLarA if kye; tN sTLys oTd)
```

## Level 4

Here the words of the hint are shuffled. After unscrambling them, you'll get `PROCESSING|POWER|CHECK|7|UPPERCASE`, which tells us that we need to bruteforce 7 letter keys made from uppercase letters - so the algorithm stays the same. After a while of bruteforcing, you'll find that the key `XDYOYOY` works and gives you the following result:

```
ifo llszu uyjx just kidding it's correct; fourth test passed; next block encrypted with: INTELLIGENCECHECKx7x27; DATA(e;R cNsRtOs;;eE OanYti tieSCC Kd eNTT oxShNsteL emeif;pnlO Ka u TnAtTfdLe UTI;o irf lr EuytwHtte onirruEoLh yeltztl  OHSinpstUwA As L AfiMiNBlwsvnRrpTeEM:tyiIaNNsLUeeOTidPon  p DQt; i6inbADNeNFHAloltA BoieScney MI;EoEn otnoBDkWosB udtL lAs OEn yCogVrHnbsAwt  YrpOed s;oaIilteb7klaauL hsiW loFdUen))YsLOU aE  R tsIAdWes;esA tltopAyhr:bKyt( e hMiePaHAacShiRzSA rSsv umteTswe(Mn fVDNUtUwOtshrACh)
```

## What next?

And that's where we are now. We have been stuck on L5 for quite some time, and we've gotten some hints. From them we know that the algorithm is now generalized even more - instead of the key, we now need to know the step sizes themselves (which are still in a list, where the pointer wraps around), so it's a lot harder to bruteforce it now. It has names already - level 5 algorithm (L5A), and intelligencecheck.

Congratulations! Now you are qualified to join our [decrypting discord server](https://discord.gg/6qR2KP83JC) :) !