# WYS "ARG" tools

Warning: WYS spoilers ahead :)

- [WYS "ARG" tools](#wys-arg-tools)
	- [What is this?](#what-is-this)
	- [How to use?](#how-to-use)
		- [wys_freq.py](#wys_freqpy)
		- [wys_indextable.py](#wys_indextablepy)
		- [wys_test.py](#wys_testpy)
		- [wys_lib.py and wys_lib.c](#wys_libpy-and-wys_libc)
		- [wys_playground.py](#wys_playgroundpy)
		- [algo_bruteforce](#algo_bruteforce)
		- [ab_v2](#ab_v2)
	- [deprecated, but with historical significance](#deprecated-but-with-historical-significance)
		- [wys_decrypt.py (replaced by wys_lib.py and wys_playground.py)](#wys_decryptpy-replaced-by-wys_libpy-and-wys_playgroundpy)

## What is this?

There is a game called "Will you snail?" (WYS) by Jonas Tyroller. If you go to the Squid's presentation room after fixing him, there is some binary, which turned out to be a puzzle, and is being solved on [WYS Discord (\#WYS binary decrypting (read pinned))](https://discord.gg/6Kk2FUHmgf). For more information look at the [doc](https://docs.google.com/document/d/1e_nOhSkTh9cchh8n5yDadvf-pnoi8CBZnHwZE0dsbcI/edit#).

## How to use?

I will go one by one here:

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

### wys_lib.py and wys_lib.c

`wys_lib.py` is a python module containing methods used to decrypt/encrypt previous levels as well as texts and data, there is also a bit of stuff for working with premutations.
Use it as any other python module - just import it and then use it.
`wys_lib.c` is an optional part of it. If you have a c/c++ compiler, compile it into c_wys_lib.so (on UNIX) or c_wys_lib.dll (on Windows). `wys_lib.py` will load it and use the c functions instead of the python ones. `wys_lib.py` will also "complain" when the .so/.dll file is not found.

### wys_playground.py

This is just a script to play with :). It imports wys_lib and there is commented code which would decrypt and reencrypt prevoius levels (first directly, then through the permutation utilities).

### algo_bruteforce

Check out [it's own readme :)](algo_bruteforce/README.md)

### ab_v2

It has no readme :/

## deprecated, but with historical significance

### wys_decrypt.py (replaced by wys_lib.py and wys_playground.py)

This is a script containing functions to solve the solved part of the cypher. You can modify it to test new ideas, hopefully getting to next level! Use it as any other python3 script.
