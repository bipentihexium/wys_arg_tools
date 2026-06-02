#!/usr/bin/python3
text6 = "fifth test passed; encryption: QUANTUMCHECK7THOUSANDTOTHEPOWEROFSEVEN; DATA(i Ihilfs6kdsRNot A gKBClr Mo;w; t tsEsnVpttzw O xiOhwTtubAaSDRl nesCelnBozuteLi afuiOnenSRa Olsrt iyiL iOTAid snehlw ;HAhoAiElkUi;a neAMh FrsoYatAetrDso:iSuLeeUo mLpt   bT ednfIh YbNt  n vdScpt lsltNee(I;iSeAsr;MULstaeoyM e  Bds ywr wWr too telrLsoyNsUiAiKeen;P yocel stdybteu  aeAnh) nREvNtHIAWLopaNuI eBtlo mnYrL )"
data6 = "i Ihilfs6kdsRNot A gKBClr Mo;w; t tsEsnVpttzw O xiOhwTtubAaSDRl nesCelnBozuteLi afuiOnenSRa Olsrt iyiL iOTAid snehlw ;HAhoAiElkUi;a neAMh FrsoYatAetrDso:iSuLeeUo mLpt   bT ednfIh YbNt  n vdScpt lsltNee(I;iSeAsr;MULstaeoyM e  Bds ywr wWr too telrLsoyNsUiAiKeen;P yocel stdybteu  aeAnh) nREvNtHIAWLopaNuI eBtlo mnYrL "
hint6 = "QUANTUMCHECK7THOUSANDTOTHEPOWEROFSEVEN"

def pw_to_key(pw: str) -> list:
	return [int(c) if c.isdigit() else ord(c) - 64 for c in pw.upper()]

def decrypt(data, key: list):
	index = 0
	result = data[:0]
	key_index = 0
	while data:
		index = (index + key[key_index]) % len(data)
		key_index = (key_index + 1) % len(key)
		result += data[index:index+1]
		data = data[:index] + data[index+1:]
	return result

#text2 = decrypt(data1, [17])
#text3 = decrypt(data2, pw_to_key("HUMANSCANTSOLVETHISSOBETTERSTOPHERE"))
#text4 = decrypt(data3, pw_to_key("EILLE"))
#text5 = decrypt(data4, pw_to_key("XDYOYOY"))
#key5_original = pw_to_key("INTELLIGENCECHECKx7x27")
#key5 = key5_original.copy()
#for _ in range(7):
#	key5 = decrypt(key5, key5_original)
#key5 = [x*27 for x in key5]
#text6 = decrypt(data5, key5)

