# wys_test.py

This scripts is for testing keys.
For each key you give it (at runtime + everyting in `autotest_keys` variable), it tries to use every method from `test_methods` variable. It also tries to use every modifier in the variable `test_modifications` on all of data, key, and result. The modifications are functions which take a string and return modified one.
If you use `PRINTALL` as a key, it'll show you every message it got (there's a lot of them). If you use `EXIT`, the script will terminate.
example input/output (with level3 data, `[humanscantsolvethis_decrypt, humanscantsolvethis_encrypt]` as `test_methods` and `[pass_mod, reverse_mod]` as `test_modifications`):
```
$ python3 wys_test.py
Could not find ./c_wys_lib.so. Using Python implementations...
another key (auto-capitalized)>amelia
Didn't find anything with key AMELIA
another key (auto-capitalized)>ellie
--------------------- MESSAGE ------------------------
that's correct; third test passed; next up: SGIPCESRON|WOREP|HKCEC|7|SEPURECAP; DATA(IvTuitn tat  eHenoEi pgvi IATf nAOiM pLl ssyGnelnu l(Eeo seIthHNc;YARsL oeeoEilnBst( elth dylarxtlSAPa YbSpNR'UrslCPth;B LiyROsoMpsF SrasCIssn KNEALhATih o  atowrstzCnisuhcAHKAm  ecIREftNsUMiNnan HeosirhHSs;AdtuuNpodpEo;pey r6T )rs(isg tyAi;sse;tFeCtutEj Soewuoe tMNR B Sedcl C KxeeCOxai; tnitLlLy tetncU OO ijwEiC:b7O;eUithx VOodAr )Tu xbsc:onD Nn tpsot KSeo;ae)DMEw2z tf EyfotdanrAeetwu7dIeB ;mnh:bA slu t WL ketAtlDnk;rNlU ILWeW7 iiDwUlnrTeEiolttdYT OtwEeDbUe i h HNfrAfc dVQdk ArzTOLarA if kye; tN sTLys oTd)
key: EILLE
data: AtniotoMK;hHLt hOT(NSCCiMs  aEeMifpCesul)t: su|'yhlRtsW ;tFpb7t actt lbA  L|c  Ar:SlihA7Eof kh rK;LSPrfdswdrBrHekblUytasxKsnc 7uAROslOyELt SSUC;G Amu snOaACtrutyreebN;TPx thNIteelset;seis;  drs  nDdEpdltueUc And o c dyS7tdTlwFcA TItiePoA:(slpr(ltefKaIeeR  EdN;AvtetEE psottTCTEaCoAa IyYfsnouotsbUti sAkSetL;iui hNpnedped nIhcetx ;ttAeN lsytTnhKtD EeiaexRELityHU'Uux )e UMVr NVhtYiHc  rj Blu;Oe rN e pdsYNHIDo6NeS: D OOAlnn aC TC f So RPoGMsntsan EI LtE anoOiEeP    wDThxdt;CLp)eoEHo arS;wrwgiABeRzwAsue evirjOotiimo;L L( NEwros|oIpNiWeisoin;AiOAit2EQnyUlzsR TWRn rfCAeBEO ks PTW in|sngscthezHt eD)
method: humanscantsolvethis_decrypt
another key (auto-capitalized)>exit
```
