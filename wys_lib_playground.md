# wys arg decrypting toolkit

The core of this toolkit (and also of some scripts) is the `wys_lib`. It's made in python, so you'll need python 3 to run it (not sure what version is needed, but 3.6+ should work fine). It is a module containing data and useful functions. Apart from `wys_lib.py`, there's also `wys_playground.py`. `wys_playground.py` imports `wys_lib.py` and is meant for experimenting.

- [wys arg decrypting toolkit](#wys-arg-decrypting-toolkit)
	- [Quick start](#quick-start)
	- [wys_lib.c](#wys_libc)
	- [all data](#all-data)
	- [decrypt and encrypt functions](#decrypt-and-encrypt-functions)
	- [permutations](#permutations)
	- [L2A key finding](#l2a-key-finding)
	- [character frequency](#character-frequency)
	- [mask, first possible occurence](#mask-first-possible-occurence)

## Quick start

If you know python (at least a bit) this section should be enough to get you started with main utilities in `wys_lib`. (note: you can try these examples in `wys_playground.py`, which already includes `wys_lib` import :)  ) I'd recommend trying out all the stuff here yourself, you'll learn how to use it better :)  .
The most basic things `wys_lib` provides is the data we got at various levels:

```python
from wys_lib import *

print(data1) # prints data for the first level (Nw;:OPxPo st;AEp fb...)
print(data4) # prints data for the fourth level (IvTuitn tat  eHeno...)
print(text3) # prints text for the first level (second test passed;...)
```

Maybe you want to decrypt the data you can find in `wys_lib`. It also contains the algorithms used for decrypting!

```python
from wys_lib import *

print(dontbother17_decrypt(data1)) # decrypts the first level and prints the result
print(humanscantsolvethis_decrypt(data2)) # decrypts the second level
```

But both of these algorithms take something along data, like a key. The trick is that the values actually used in that level are default values for the functions.

```python
from wys_lib import *

print(dontbother17_decrypt(data1, 5)) # decrypts the first level using DONTBOTHER5 and prints the result
print(humanscantsolvethis_decrypt(data3, "EILLE")) # decrypts the third level - L3 uses L2 algorithm, just with a different key
```

Of course there are functions for the levels which use algorithm from previous level too. (They are actually `lambda`s but who cares :D)

```python
from wys_lib import *

print(sheismymother_decrypt(data3)) # decrypts L3
print(processingpower_decrypt(data4)) # decrypts L4
```

What if you want to encrypt some text using theese algorithms? Every `..._decrypt` function has also `..._encrypt` version which does exactly that.

```python
from wys_lib import *

encrypted = sheismymother_encrypt(text4) # encrypted L4 text should be same as L3 data
print(encrypted)
if encrypted == data3:
	print("Yay, it works!")
else:
	print("Oh no, something went wrong!")
	raise ValueError("L3 encryption doesn't work :(")
```

`wys_lib` can still do a lot more things. Take a look at the other parts of the documentation to find out about them! There is a sneek peak :)

```python
from wys_lib import *

print(" ".join(humanscantsolvethis_keys_from_result(data2, "second"))) # prints keys which would give you "second" at te start when you use L2A on data2
print(mask_data(data5, "DATA(")) # prints data5, but everyting except chars in "DATA(" are replaced by dots
print(frequency(data5)) # character frequencies of data5
```

and here are some examples of what you can do with `wys_lib` :)

```python
from wys_lib import *

# bruteforce of dontbothers on data5 up to dontbother len(data5)
for i in range(len(data5)):
	d = dontbother17_decrypt(data5, i)
	if "DATA" in d:
		print(d)

# key bruteforcer - length 5, data3
# it's python, so it's slow; but it should be viable with the help of wys_lib.c (it's doc us just under this)
alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
for a in alpha:
	for b in alpha:
		for c in alpha:
			for d in alpha:
				for e in alpha:
					decrypted = humanscantsolvethis_decrypt(data3, a+b+c+d+e)
					if "; DATA(" in decrypted:
						print(a+b+c+d+e, decrypted)
```

## wys_lib.c

`wys_lib.c` is an **optional** part of `wys_lib.py`. If you have a c/c++ compiler, compile it into `c_wys_lib.so` (on UNIX) or `c_wys_lib.dll` (on Windows). `wys_lib.py` will load it and use the c functions instead of the python ones. `wys_lib.py` will also "complain" when the .so/.dll file is not found. It should make most functions faster, but not all functions are implemented in `wys_lib.c` for now.

For compilation on Windows with `g++` from MinGW, you can use `g++ -Wall -O3 -march=native -o c_wys_lib.dll wys_lib.c` (note that the only difference from the linux command is the output file extension).
For compilation on Linux with `g++`, I'd recommend this command: `g++ -Wall -O3 -march=native -o c_wys_lib.so wys_lib.c`. (`-Wall` - all warning levels; `-O3` - optimize for speed; `-march=native` - compile for current architecture (makes the `.so` less cross-platform, but faster); `-o` - output file).

When you are using `c_wys_lib.so`/`c_wys_lob.dll`, you can still use the python versions of those functions (for example when you need to do dontbother with really big numbers) by prefixing the name of the function with `py_` (like `py_dontbother17_decrypt(data5, 90321812343133523243524123901375431232)`). Note that those funtions are not imported by `from wys_lib import *`, so you need to import them explicitly or through importing `wys_lib` directly.

## all data

`wys_lib` contains data for all levels - `data1` contains L1 data, `data2` contains L2 data and so on. Apart from data, there are also full messages - `text1` to `text5`. There are also hints - `hint1` to `hint5`. L3 and L4 hints were encrypted, so there are decrypted versions - `hint3decrypted` and `hint4decrypted`. There are also keys - `key2` to `key4`.

## decrypt and encrypt functions

In `wys_lib`, there are functions for decrypting and encrypting any level:

```python
from wys_lib import *

print(dontbother17_decrypt(data1)) # L1
print(humanscantsolvethis_decrypt(data2)) # decrypts L2
print(sheismymother_decrypt(data3)) # decrypts L3
print(processingpowercheck_encrypt(text5)) # encrypts L4
print(humanscantsolvethis_encrypt(text5, "XDYOYOY")) # also encrypts L4 - the keys/constants (the 17) are default in each function
```

## permutations

Every level so far was a transposition cipher and it's expected to be like that for all levels. Because of that, there is `TranspositionCipher` class for working with permutations. There are `..._gen` functions for each [`..._decrypt`/`..._encrypt` function](#decrypt-and-encrypt-functions), which are permutation generators for each method. The generators are functions taking `data` and other arguments (like `key`) and returning list of ints (where item `n` should be at `p[n]` (`p` is the list) after applying the permutation).

```python
from wys_lib import *

tc = TranspositionCipher(data4, processingpowercheck_gen) # constructor takes data and generator, then generator arguments (without data)
#tc = TranspositionCipher(data4, humanscantsolvethis_gen, key4) # this does the same thing
```

It then can be applied on the data it contains on other collection (like another data, some string or list)

```python
# ...

print(tc.apply()) # prints result of applying tc's permutation on tc's data
print(tc.apply_on(list(range(len(data4))))) # applies tc's permutation onto a list containing [0,1,2,3,...]
```

The permutations can be inversed, combined, or you can take a power of the permutation:

```python
# ...

tc2 = TranspositionCipher(data4, humanscantsolvethis_gen, "SOMEKEY")
print((tc * tc2).apply()) # combined
print(tc.apply_on(tc2.apply())) # this should be the same as the one above
print((~tc).apply_on(text5)) # encrypts L4 (remember, the tc is from previous example :D )
print((tc ** 4).apply()) # applies tc 4 times on it's data
```

Note that the power operation is pretty fast - it uses the square and multiply algorithm :) .

## L2A key finding

Sometimes we want to try to reverse engineer the keys for the L2 algorithm. There is a function which does that too. `humanscantsolvethis_keys_from_result` takes data and a result, and it will return list of keys which will give you result at the beginning when L2A is used on data. There's also a third argument - offsets. It's an iterable of offsets at which it should start the search; it defaults to `[0]`, which is the beggining mentioned before.

```python
from wys_lib import *

print(humanscantsolvethis_keys_from_result(data2, "second"))
# prints ['UHMANA', 'UHMANS', 'UILANA', 'UILANS', 'UQDANA', 'UQDANS', 'HDKJXA', 'HDKJXS', 'HDKTNA', 'HDKTNS', 'HUMANA', 'HUMANS', 'HVLANA', 'HVLANS']

print(humanscantsolvethis_keys_from_result(data4, "just kidd", [305]))
# prints ['DYOYOYMOY', 'DYOYOYNNY', 'DYOYOYXDY', 'DYOYOQUOY', 'DYOYOQVNY', 'DYOYWQMOY', 'DYOYWQNNY', 'DYOYWQXDY', 'DYOYWIUOY', 'DYOYWIVNY', 'DYORVYMOY', 'DYORVYNNY', 'DYORVYXDY', 'DYORVQUOY', 'DYORVQVNY']
```

It can handle wrapping around now :) .

TODO: document this part better
When it cannot find anything, it returns a tuple like this: `(last_letter_index, [(key1, position1), ...])`.

```python
from wys_lib import *

print(humanscantsolvethis_keys_from_condition(data2, lambda c: c.isupper(), 4, range(10))) # all keys which produce 4-letter long uppercase starting at any index between 0 and 9 (both inclusive)
```

## character frequency

`wys_lib` contains some utilies for getting properties of data. There is frequency function which returns counts of all characters in the string you give it; they are separated by spaces in a format `char-count`, and space is replaced by `⎵`.

```python
from wys_lib import *

print(frequency(data5))
```

gives

```
⎵-47 t-25 e-25 s-19 i-17 o-15 n-15 A-15 l-12 r-10 a-9 O-9 N-9 ;-9 h-8 T-8 L-8 E-8 y-7 d-7 U-7 S-7 w-6 u-6 p-6 f-5 R-5 M-5 I-5 H-5 b-4 D-4 C-4 B-4 c-3 Y-3 W-3 K-3 z-2 v-2 m-2 k-2 V-2 P-2 F-2 :-2 )-2 (-2 x-1 g-1 Q-1 7-1 6-1
```

Sometimes it's useful to group the characters in groups - `frequency_categories(data, categories, category_names)` does that! The categories argument is a list of iterables of chars (usually list of strings), which each category contains. It's default value is `["abcdefghijklmnopqrstuvwxyz","ABCDEFGHIJKLMNOPQRSTUVWXYZ","0123456789","();|:,"," "]`. The category_names is just a name for each category (default: `["lower","upper","numbers","special/splitters","space"]`). So let's take a look at an example!

```python
from wys_lib import *

print(frequency_categories(data5))
```

prints

```
lower-209
upper-119
numbers-2
special/splitters-15
space-47
```

## mask, first possible occurence

There's also a `mask_data(data, shown_chars, mask_char='.')` function. It replaces all characters which are not in `shown_chars` with `mask_char`.

```python
from wys_lib import *

print(mask_data(data5, "DATA("))
```

prints

```
...................................TT...........................T.A.T......T...................................................A.A....A..............T.................T.........D.........AD.....A....A........................D............A................A..........................................................A.......A......A........(..........A........A..........T...(.....D..........A..
```

As one can notice, you'd need to use up a pretty big chunk of the data in order to make `DATA(`. `wys_lib` actually contains a function which calculates minimum amount of used up characters needed to make a desired result - it's `min_remove(data, result)`!

```python
from wys_lib import *

print(min_remove(data5, "DATA("))
```

gives you `243` - my handmade calculation I made a while ago said `244`. I have probably made a little error in my calculation, but still take the result with a grain of salt :) .
