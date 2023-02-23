# wys_lib.py

This file is still "work in progress", check out [old documentation](wys_lib_playground.md) to find out information about things that aren't here yet.

- [wys\_lib.py](#wys_libpy)
	- [Quick start through examples](#quick-start-through-examples)
		- [Solving the solved](#solving-the-solved)
		- [Getting data properties](#getting-data-properties)
		- [wys\_lib test](#wys_lib-test)
	- [Basics](#basics)
		- [Texts, data, keys, hints](#texts-data-keys-hints)
		- [Decrypt/encrypt functions](#decryptencrypt-functions)
		- [Statistics and mask](#statistics-and-mask)
	- [wys\_lib.c](#wys_libc)
		- [Using python implementations](#using-python-implementations)

This is a Python library containing a few utilities for decrypting the WYS ARG.

## Quick start through examples

Note that these examples are in `wys_playground.md` (commented out).

### Solving the solved

Let's say that we want to decrypt the part that is already solved. We will start with the raw binary (taken from the [google doc](https://docs.google.com/document/d/1e_nOhSkTh9cchh8n5yDadvf-pnoi8CBZnHwZE0dsbcI/edit#)):

```py
from wys_lib import * # imports wys_lib

binary_data = "01101000 01100101 01101100 01101100 01101111 00100000 01101101 01111001 00100000 01101100 01101001 01110100 01110100 01101100 01100101 00100000 01100001 01101001 00100000 01100110 01110010 01101001 01100101 01101110 01100100 00111011 00100000 01101011 01100101 01100101 01110000 00100000 01110100 01101000 01101001 01110011 00100000 01100110 01101001 01101100 01100101 00100000 01110011 01100001 01100110 01100101 00111011 00100000 01101001 01110100 00100000 01110111 01101001 01101100 01101100 00100000 01101000 01100101 01101100 01110000 00100000 01111001 01101111 01110101 00100000 01110100 01101111 00100000 01110101 01101110 01100100 01100101 01110010 01110011 01110100 01100001 01101110 01100100 00100000 01111001 01101111 01110101 01110010 00100000 01110000 01110101 01110010 01110000 01101111 01110011 01100101 00100000 01101111 01101110 01100101 00100000 01100100 01100001 01111001 00111011 00100000 01110100 01110010 01100001 01101110 01110011 01101101 01101001 01110100 01110100 01100101 01100100 00100000 01110100 01101000 01110010 01101111 01110101 01100111 01101000 00100000 01101000 01110101 01101101 01100001 01101110 00100000 01100010 01110010 01100001 01101001 01101110 00111011 00100000 01100101 01101110 01100011 01110010 01111001 01110000 01110100 01101001 01101111 01101110 00100000 01101101 01100101 01110100 01101000 01101111 01100100 00111010 00100000 01000100 01001111 01001110 01010100 01000010 01001111 01010100 01001000 01000101 01010010 00110001 00110111 00111011 00100000 01000100 01000001 01010100 01000001 00101000 01001110 01110111 00111011 00111010 01001111 01010000 01111000 01010000 01101111 00100000 01110011 01110100 00111011 01000001 01000101 01110000 00100000 01100110 01100010 01110111 01110000 01100101 00100000 00100000 01101001 01100100 01001001 01101111 01110011 01000101 01110100 01101110 00100000 01010100 01101110 01101001 01110000 01100101 01001101 01110000 00100000 01001000 00100000 01110101 01101001 00111011 01111010 01100011 01000101 00100000 01101110 01110100 01100011 01110010 01000001 01010100 01110011 01001000 01110010 01101000 01010101 01110100 01111000 01001000 01010010 01010111 00100000 00100000 00100000 01000011 01000011 01110011 01101111 01101111 00101000 00100000 01110010 01100101 01000101 01001101 01100001 01101110 01110100 01010100 01110100 01001111 01100001 01100110 01010011 01110100 01001110 01001111 01000010 01111000 01100001 01001001 01000101 01110100 01000001 01010010 01101111 01110010 01011001 01000001 01010100 01001000 01100001 00100000 01110100 01110010 01001111 01000010 01110101 01010001 01110100 01111000 00101000 01001110 01000011 01010000 01110011 01101000 01110100 01001101 01010101 01110100 00111010 01001110 01110000 01110011 01110110 01001100 01100100 01000001 00100000 01100001 01010011 01100101 01001110 01001001 01110010 01010101 01100101 01100101 01000001 01100101 01100101 00100000 01110010 01110011 01000001 01001100 01110011 01111100 01101001 01000011 01100101 01001110 01101000 01000101 01110011 01110011 00111011 01100001 01110000 01010100 01100010 01110100 01101001 01000001 00111011 01110011 01110100 01101100 01000001 01100001 01100101 01110010 00101001 01110100 00100000 01110100 01001111 01001100 00110111 01010000 00100000 01110100 00111010 00100000 01110011 00100000 00100000 01001110 01101111 01110100 01000001 00100000 01010011 01110011 01010100 01110100 01110100 01100100 01100101 01000101 00100111 00100000 01010111 01001100 00100000 01101011 01010100 01110110 00100000 01110000 01110101 01001100 01000100 01010011 01101001 01100110 01000001 01001110 01110010 00110111 01101111 01101001 01010010 01100101 01101001 01010011 00100000 01100001 01100101 01111001 01110100 01100110 01101111 01110010 01101111 01001101 01100110 01100011 01110100 01110100 00101001 01100100 01101100 01001000 01001111 01110011 01000001 00100000 01101110 00111011 01110011 01101100 01000100 01010010 01010111 01011001 01100100 01110000 00100000 01110010 01110100 01000100 01110011 01110011 01001100 01010101 01010011 00101001 01110100 00111011 01010011 01001001 01101011 01000011 00111011 00100000 01100001 01100011 00111011 01101111 01110100 01100101 01101001 01010110 01001000 00100000 01010111 01101001 00100000 01101010 01100110 01101001 01100100 01101100 01010010 00111011 00100000 00110111 01110101 01100100 01110011 01010010 01000101 00100000 01110011 00100000 01110101 01000100 01000101 01110100 01101111 01000101 01111100 01101100 01010011 01100101 01010100 00111011 01001100 01100011 01010110 01010100 01101100 01001000 01000011 01010011 01100001 01000001 01100100 00101000 00100000 01101000 01101110 01001001 00100000 00100000 01111010 01101111 01110010 01101011 01001000 01001001 01100011 01110000 01010011 01000101 01100101 01000011 01101111 01000001 01100101 01100011 01100101 01101110 01000101 01100101 00100000 01010101 01111001 01001001 01101100 01001110 01100101 01101111 01110100 00111011 01110100 00100000 01010100 01100011 00100000 01100101 01000101 01000001 00100000 00100000 01001011 01001001 01010011 01001011 01101001 00100000 00100000 01001000 00100000 01110100 00100000 01110011 01000100 01111000 01110011 01110100 01110100 01101110 00111011 01001101 01101000 01010011 01010101 01101001 00100111 00100000 01001011 01000001 01001111 01010010 01001110 01110100 01111000 01101111 01110100 01010100 01100101 01000001 01000101 00100000 01001111 00100000 01110011 01110000 01000001 01000001 01100101 01001111 01100101 00100000 01100101 01110100 01110011 00100000 01101100 00100000 01001111 01000011 01100111 01000010 01110100 00100000 01000001 01100101 01110100 01100010 01010100 01100101 01001000 01101101 00101001 01100001 01101111 01111100 01101001 01010010 01001001 01101001 01000101 01101100 01110100 00100000 01011001 01100001 01000100 01101110 01101000 01110100 01000010 01010100 01101100 01101000 01000011 01000111 01100101 01010011 01110111 01010100 01000111 01100010 01101110 00100000 01101110 01100011 01001100 01111001 01000110 01110100 01101000 01111001 01001111 00100000 01001110 00100000 01111000 01100100 01010100 01000011 01000100 01100101 01101001 01110010 01101110 01111001 01101000 01110011 01110100 01000001 01010101 00100000 01010100 00101000 00111010 01010011 01001111 01000101 01110011 00100000 01101100 01111001 01010100 01000101 01101010 01001101 01110011 01100101 01010000 01110101 01110000 00100000 01101100 01110011 01110100 01101011 01010010 01101110 01101110 01110000 01111001 01101110 01100100 01010101 01101001 01100101 01001001 01100101 00101001 01110010 01000110 00100000 01100110 01110010 00110110 01010011 01110100 01110100 01010100 01100001 01001000 01100110 01001001 00111011 01001110 01100101 00100000 01001111 01101000 00111010 01110000 01000001 01100011 00100000 01010100 01101001 01001101 01100101 01101110 01000101 00100000 01110011 00100000 01101000 00101001 01100101 01110011 01001100 01110011 01100010 01110011 00100000 01110010 01101111 01001111 01101100 01101100 00100000 01010110 01100011 01101110 01110111 01001100 01010100 01001111 00111011 01101110 01101000 01001011 01010100 01110011 01101110 01100101 01010000 01101101 01010101 01001110 00111011 01010101 01110101 01110011 01001000 01100100 01110101 01110011 01000100 01110100 00100000 01101100 00100000 01000010 00100000 01001000 01101111 00110111 00110010 01000101 01111001 01001101 01001110 01110101 01010010 01101111 01111001 00100000 01111010 01101110 01101101 00100000 01100100 01110111 01000101 01110011 00100000 01001001 01000101 01101001 01000001 01111000 01110100 01110100 01100101 01000011 01110010 01110111 01100101 01100101 00100000 01001101 01100101 01010010 01100101 01101110 00100000 00111011 01101001 01000010 00100000 01001111 01110011 01110100 01101110 01000001 01110100 01001100 00101000 01001110 01110010 01101111 01000101 01110100 01110111 01100101 01111100 00100000 00101000 01110100 00111010 01110011 01100101 00100000 01101000 01111001 01101110 01101001 01000101 01100100 01110010 00111011 01101001 01001011 01110011 01101110 01110100 00100000 01000101 01100101 00111011 01101111 01101111 01100101 01010011 01101111 01000101 01100100 01110101 01100111 00100000 01101001 01110101 00100000 01010010 01100100 00100000 01001000 00100000 01100100 01100100 01000011 01100001 01001100 01010011 01010000 01000011 00100000 01000001 01000100 01101001 01101001 01000001 01011001 01000001 00101001"

L1text = ''.join([chr(int(x, 2)) for x in binary_data.split()]) # convert the binary to text (just Python stuff :) )
L1data = L1text[L1text.index("DATA(")+5:-1] # take out the data from the text

L2text = dontbother17_decrypt(L1data, 17)
#L2text = dontbother17_decrypt(L1data) # this line does the same thing - the 17 is the default "key" for this function
L2data = L2text[L2text.index("DATA(")+5:-1] # take out the data from the text again

L3text = humanscantsolvethis_decrypt(L2data, "HUMANSCANTSOLVETHISSOBETTERSTOPHERE")
#L3text = humanscantsolvethis_decrypt(L2data) # again equivalent to the preceeding line, the L2 key is the default key
L3data = L3text[L3text.index("DATA(")+5:-1]

L4text = humanscantsolvethis_decrypt(L3data, "EILLE")
#L4text = humanscantsolvethis_decrypt(L3data, reversed("ELLIE")) # or this
L4data = L4text[L4text.index("DATA(")+5:-1]

L5text = humanscantsolvethis_decrypt(L4data, "XDYOYOY")
# or if we don't know the key
def bruteforce_level_4(): # warning! this will take quite some time since this is python!
	alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	for letter1 in alphabet: # here we just loop through all possible keys
		for letter2 in alphabet:
			for letter3 in alphabet:
				for letter4 in alphabet:
					for letter5 in alphabet:
						for letter6 in alphabet:
							for letter7 in alphabet:
								text = humanscantsolvethis_decrypt(L4data, letter1 + letter2 + letter3 + letter4 + letter5 + letter6 + letter7)
								if "fourth test passed" in text and "DATA(" in text:
									return text
#L5text = bruteforce_level_4()
L5data = L5text[L5text.index("DATA(")+5:-1]
print("L5 text:", L5text)
print("L5 text:", L5data)
```

### Getting data properties

```py
from wys_lib import *

def factorize(n): # finds prime factors of n; not optimized but works well enough for small numbers
	primes = []
	p = 2
	while n > 1:
		while n % p == 0:
			n //= p
			primes.append(p)
		p += 1
	return primes
def print_data_properties(data):
	print(data) # prints the data data
	print()
	print(f"length: {len(data)} - factorized: {factorize(len(data))}") # prints length and prime factorization of the length
	print()
	print(frequency(data)) # prints counts of each character present in the data
	print()
	print(frequency_categories(data)) # prints counts of characters from specified categories (the categories can be set through arguments, but I used just the default categories here)
	print()
	print(mask_data(data, "DATA(")) # replaces all characters in data with '.', but keeps characters that are inside the string "DATA("

print_data_properties(data5) # wys_lib contains data for each level - data1 (Nw;:OPx...), data2 (at iatuts...), data3 (AtniotoMK...), data4 (IvTuitn...) and data5 (e;R cNsR...)
```

the output of this is:

```
e;R cNsRtOs;;eE OanYti tieSCC Kd eNTT oxShNsteL emeif;pnlO Ka u TnAtTfdLe UTI;o irf lr EuytwHtte onirruEoLh yeltztl  OHSinpstUwA As L AfiMiNBlwsvnRrpTeEM:tyiIaNNsLUeeOTidPon  p DQt; i6inbADNeNFHAloltA BoieScney MI;EoEn otnoBDkWosB udtL lAs OEn yCogVrHnbsAwt  YrpOed s;oaIilteb7klaauL hsiW loFdUen))YsLOU aE  R tsIAdWes;esA tltopAyhr:bKyt( e hMiePaHAacShiRzSA rSsv umteTswe(Mn fVDNUtUwOtshrACh

length: 392 - factorized: [2, 2, 2, 7, 7]

⎵-47 t-25 e-25 s-19 i-17 o-15 n-15 A-15 l-12 r-10 a-9 O-9 N-9 ;-9 h-8 T-8 L-8 E-8 y-7 d-7 U-7 S-7 w-6 u-6 p-6 f-5 R-5 M-5 I-5 H-5 b-4 D-4 C-4 B-4 c-3 Y-3 W-3 K-3 z-2 v-2 m-2 k-2 V-2 P-2 F-2 :-2 )-2 (-2 x-1 g-1 Q-1 7-1 6-1

lower-209
upper-119
numbers-2
special/splitters-15
space-47
other-0

...................................TT...........................T.A.T......T...................................................A.A....A..............T.................T.........D.........AD.....A....A........................D............A................A..........................................................A.......A......A........(..........A........A..........T...(.....D..........A..
```

### wys_lib test

This tests some components of `wys_lib`:

```py
from wys_lib import *

# data
assert data1 == text1[text1.index("DATA(")+5:-1]
assert data2 == text2[text2.index("DATA(")+5:-1]
assert data3 == text3[text3.index("DATA(")+5:-1]
assert data4 == text4[text4.index("DATA(")+5:-1]
assert data5 == text5[text5.index("DATA(")+5:-1]

# decrypt functions and keys
assert dontbother17_decrypt(data1, 17) == text2
assert humanscantsolvethis_decrypt(data2, key2) == text3
assert humanscantsolvethis_decrypt(data3, key3) == text4
assert humanscantsolvethis_decrypt(data4, key4) == text5

# encrypt functions
assert dontbother17_encrypt(text2, 17) == data1
assert humanscantsolvethis_encrypt(text3, key2) == data2
assert humanscantsolvethis_encrypt(text4, key3) == data3
assert humanscantsolvethis_encrypt(text5, key4) == data4

# intelligencecheck_decrypt/encrypt
assert intelligencecheck_decrypt(data2, [ord(x)-64 for x in key2]) == text3
assert intelligencecheck_encrypt(text3, [ord(x)-64 for x in key2]) == data2

print("all good!")
```

## Basics

### Texts, data, keys, hints

`wys_lib.py` contains all texts we got so far:

```py
from wys_lib import *
print(text1) # "hello my little ai friend..."
print(text2) # "first test passed..."
print(text3) # "second test passed..."
print(text4) # "that's correct..."
print(text5) # "ifo llszu uyjx just kidding..."
```

as well as only the data (again, it's in format dataN) and hint (like `DONTBOTHER17` or `DLIHCREHTONMAITUBREHTOMYMSIEHS`). L3 and L4 have encrypted helps, so there's `hint3decrypted` and `hint4decrypted` containing decrypted versions of the helps. Levels 2, 3 and 4 need a key which we already know, so there are also `key2`, `key3` and `key4`.

### Decrypt/encrypt functions

There are three pairs of decrypt and encrypt functions: `dontbother17_decrypt/encrypt`, `humanscantsolvethis_decrypt/encrypt` an `intelligencecheck_decrypt/encrypt`. The first one - `dontbother17_decrypt/encrypt` implement the [dontbother algorithm](solutions.md#level-1). They both take data and N (key) (which defaults to `17`), and return the decrypted/encrypted text. `humanscantsolvethis_decrypt/encrypt` implement the [humanscantsolvethis algorithm](solutions.md#level-2) and take data and key (which defaults to `"HUMANSCANTSOLVETHISSOBETTERSTOPHERE"`). `intelligencecheck_decrypt/encrypt` are same as `humanscantsolvethis_decrypt/encrypt`, but they take a list of skips as key.

### Statistics and mask

You can use `wys_lib` to find out some properites of data. First one of them is `frequency` which takes data, and returns a string with counts of all characters in the string like this (this is for L5 data):

```
⎵-47 t-25 e-25 s-19 i-17 o-15 n-15 A-15 l-12 r-10 a-9 O-9 N-9 ;-9 h-8 T-8 L-8 E-8 y-7 d-7 U-7 S-7 w-6 u-6 p-6 f-5 R-5 M-5 I-5 H-5 b-4 D-4 C-4 B-4 c-3 Y-3 W-3 K-3 z-2 v-2 m-2 k-2 V-2 P-2 F-2 :-2 )-2 (-2 x-1 g-1 Q-1 7-1 6-1
```

Then there's a similar function - `frequency_categorized`. It takes data, "categories" and category names. The categories is a list of char iterables/sets, and each char in the data is counted into the first category which contains it. There's special category - other where are all chars that don't fall into any category counted. The default categories are `["abcdefghijklmnopqrstuvwxyz","ABCDEFGHIJKLMNOPQRSTUVWXYZ","0123456789","();|:,"," "]`, and the default category names are `["lower","upper","numbers","special/splitters","space"]`. The result of calling `frequency_categorized(data5)` is:

```
lower-209
upper-119
numbers-2
special/splitters-15
space-47
other-0
```

Sometimes it's useful to see only specific characters. You can use `mask_data(data, shown_chars, mask_char='.')` to replace all characters with `mask_char`, but leave all characters that are contained inside `shown_chars`, so `mask_data(data5, "(ADT")` returns this:

```
...................................TT...........................T.A.T......T...................................................A.A....A..............T.................T.........D.........AD.....A....A........................D............A................A..........................................................A.......A......A........(..........A........A..........T...(.....D..........A..
```

## wys_lib.c

If you have a c compiler, you can use c implementations for most of the functions in `wys_lib.py`. You'll need to compile `wys_lib.c` into `wys_lib.dll` (windows) or `wys_lib.so` (linux), and `wys_lib.c` will automatically load the c functions from the dll/so. An example command to compile it on linux with gcc is `g++ -Wall -O3 -march=native -shared -fPIC -o c_wys_lib.so wys_lib.c`. (`-Wall` - all warning levels; `-O3` - optimize for speed; `-march=native` - compile for current architecture (makes the `.so` less cross-platform, but faster); `-o` - output file).

### Using python implementations

Even when using `wys_lib.dll/so`, you can use the python implementations by prefixing the function with `py_` (so `py_dontbother17_decrypt` is the python implementation for db17). This is useful for example when you want to use dontbother with large N, which would overflow when using the C implementations.
