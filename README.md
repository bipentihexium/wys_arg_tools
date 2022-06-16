# WYS "ARG" tools

Warning: WYS spoilers ahead :)

- [WYS "ARG" tools](#wys-arg-tools)
	- [What is this?](#what-is-this)
	- [How to use?](#how-to-use)
		- [wys_lib.py and wys_lib.c](#wys_libpy-and-wys_libc)
		- [wys_playground.py](#wys_playgroundpy)
		- [wys_freq.py](#wys_freqpy)
		- [wys_indextable.py](#wys_indextablepy)
		- [wys_test.py](#wys_testpy)
		- [algo_bruteforce](#algo_bruteforce)
		- [ab_v2](#ab_v2)
	- [deprecated, but with historical significance](#deprecated-but-with-historical-significance)
		- [wys_decrypt.py (replaced by wys_lib.py and wys_playground.py)](#wys_decryptpy-replaced-by-wys_libpy-and-wys_playgroundpy)

## What is this?

There is a game called "Will you snail?" (WYS) by Jonas Tyroller. If you go to the Squid's presentation room after fixing him, there is some binary, which turned out to be a puzzle, and is being solved on [WYS Discord (\#WYS binary decrypting (read pinned))](https://discord.gg/6Kk2FUHmgf). For more information look at the [doc](https://docs.google.com/document/d/1e_nOhSkTh9cchh8n5yDadvf-pnoi8CBZnHwZE0dsbcI/edit#).

## How to use?

I will go one by one here:

### wys_lib.py and wys_lib.c

`wys_lib.py` is a python module containing methods used to decrypt/encrypt previous levels as well as texts and data, there is also a bit of stuff for working with premutations.
Use it as any other python module - just import it and then use it. It contains:  
`text1`, `text2`, ... `text4` - message (with data) for each level  
`data1`, `data2`, ... `data4` - data for each level  
`hint1`, `hint2`, ... `hint4` - hint for each level  
`hint3decrypted`, `hint4decrypted` - decrypted versions of hints for levels 3 (reverse) and 4 (solved acronyms)  
`key2`, `key3` - keys for levels 2 and 3  
`uppercase` - just uppercase alphabet (because `UPPERCASE` in L4 hint)  
`dontbother17_decrypt(data, n=17)` and `dontbother17_encrypt(data, n=17)` - functions to decrypt/encrypt data using the dontbother method; n is the step size (17 for dontbother17)  
`humanscantsolvethis_decrypt(data, key="HUMANSCANTSOLVETHISSOBETTERSTOPHERE")` and `humanscantsolvethis_encrypt(data, key="HUMANSCANTSOLVETHISSOBETTERSTOPHERE")` - functions to decrypt/encrypt data using the humanscantsolvethis... method  
`sheismymother_decrypt(data, key="EILLE")` and `sheismymother_encrypt(data, key="EILLE")` - just lambdas calling `humanscantsolvethis_decrypt`/`encrypt` as L3 used the same algotithm as L2; only the key defaults are different  
`dontbother17_gen`, `humanscantsolvethis_gen`, `sheismymother_gen` - permutation generators (returns list containing the permutation) for each method (arguments same as for the `decrypt`/`encrypt` functions)  
`TranspositionCipher` - class for permutation fun :)  
`TranspositionCipher.__init__(self, data, generator=None, *args)` - TC constructor, generator is permutation generator, which is called with `generator(data,*args)`. If the generator is `None` (default), then the permutation will be identity.  
`TranspositionCipher.from_perm(cls, data, perm)` (class method) - creates TC from data and permutation list  
`TranspositionCipher.data` - gets TC data  
`TranspositionCipher.perm` - permutation contained in the TC  
`TranspositionCipher.len` - length of TC data  
`TranspositionCipher.identity_perm(self)` - makes a new identity permutation list (with length `len`)  
`TranspositionCipher.identity(self)` - makes a new identity TC  
`TranspositionCipher.apply_on(self, arr)` - applies the permutation to the `arr` (`arr` can be any iterable, it returns string for string `arr` and list for all other types)  
`TranspositionCipher.apply(self)` - applies the permutation to contained `data`  
`TranspositionCipher.__invert__(self)` (`~tc`) - returns a new TC with inversed permutation (`~tc(tc(x)) == x`)  
`TranspositionCipher.__mul__(self, cipher_b)` (`tca * tcb`) - returns a new TC with combined permutation (`(tca * tcb)(x) == tca(tcb(x))`)  
`TranspositionCipher.__pow__(self, n)` (`tc ** n` (`n` is an integer)) - returns a new TC with some power of the permutation (`tc ** n == ~tc ** -n`, `tc ** 0 == identity`, `tc ** n == tc * tc * tc ... tc` (`tc is there n times`))  
`mask_data(data, shown_chars, mask_char='.')` - masks out characters, which are not in `shown_chars`, with `mask_char` from `data`  
`humanscantsolvethis_keys_from_result(data, result, offets)` - returns a list of keys for L2 algorithm which make result at any of the offsets  
`humanscantsolvethis_keys_from_condition(data, cond, length, offets)` - returns a list of keys for L2 algorithm which make a string of length `length` where all characters obey `cond` at any of the offsets

`wys_lib.c` is an optional part of it. If you have a c/c++ compiler, compile it into c_wys_lib.so (on UNIX) or c_wys_lib.dll (on Windows). `wys_lib.py` will load it and use the c functions instead of the python ones. `wys_lib.py` will also "complain" when the .so/.dll file is not found.

### wys_playground.py

This is just a script to play with :). It imports wys_lib and there is commented code which would decrypt and reencrypt prevoius levels (first directly, then through the permutation utilities).

### wys_freq.py

This script counts characters in data variable, replace the string assigned to data inside the script, then run it.

### wys_indextable.py

This script will find all occurences of characters inside string and will print them in a table. It will ask you for data and string at runtime.
It also prints possible keys for HCSTSBSH decryption (warning, there can be lots of them).

### wys_test.py

This scripts is for testing keys/methods on data. For configuring this script, take a look at the lines with

```python
test_methods = [humanscantsolvethis_decrypt]
autotest_keys = ["DLIHCREHTONMAITUBREHTOMYMSIEHS"]
test_modifications = [pass_mod, reverse_mod]
def is_message(msg):
	return "passed; "in msg # "DATA(" in msg
```

There you can add/change methods, keys, modifications and message filter. It will ask you for more keys at runtime, use "EXIT" to end the script.

### algo_bruteforce

Check out [it's own readme :)](algo_bruteforce/README.md)

### ab_v2

It has no readme :/

## deprecated, but with historical significance

### wys_decrypt.py (replaced by wys_lib.py and wys_playground.py)

DO NOT USE THIS NOW (IT'S OUTDATED)! USE wys_lib.py AND wys_playground.py!
This is a script containing functions to solve the solved part of the cypher. You can modify it to test new ideas, hopefully getting to next level! Use it as any other python3 script.
