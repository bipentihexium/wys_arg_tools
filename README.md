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

## What is this?

There is a game called "Will you snail?" (WYS) by Jonas Tyroller. If you go to the Squid's presentation room after fixing him, there is some binary, which turned out to be a puzzle, and is being solved on [WYS Discord (\#WYS binary decrypting (read pinned))](https://discord.gg/6Kk2FUHmgf). For more information look at the [doc](https://docs.google.com/document/d/1e_nOhSkTh9cchh8n5yDadvf-pnoi8CBZnHwZE0dsbcI/edit#).

## How to use?

I will go one by one here:

### wys_lib.py and wys_lib.c

`wys_lib.py` is a python module containing methods used to decrypt/encrypt previous levels as well as texts and data, there is also a bit of stuff for working with premutations. Use it as any other python module - just import it and then use it. Here are some examples with tha basic stuff in it. :)

This one prints L2 data decrypted using L2 algorithm with key `HUMANSCANTSOLVETHISSOBETTERSTOPHERE`. The commented print does the same thing as the L2 key is default value there.
```python
from wys_lib import *

print(humanscantsolvethis_decrypt(data2, "HUMANSCANTSOLVETHISSOBETTERSTOPHERE"))
#print(humanscantsolvethis_decrypt(data2))
```

This prints L5 data but all characters which are not in `DATA(` will be replaced by `.`.
```python
from wys_lib import *

print(mask_data(data5, "DATA("))
```

This script prints encrypted L4 text, then checks if it's equal to L3 data (which it should be).
```python
from wys_lib import *

encrypted = sheismymother_encrypt(text4)
print(encrypted)
if encrypted == data3:
	print("Yay, it works!")
else:
	print("Oh no, something went wrong!")
	raise ValueError("L3 encryption doesn't work :(")
```

The function names are: `dontbother17_`... for L1, `humanscantsolvethis_`... for L2, `sheismymother_`... for L3 and `processingpowercheck_`... for L4. 
Take a look at [wys_lib_doc.md](wys_lib_doc.md) for info about everything what's in it.

`wys_lib.c` is an optional part of it. If you have a c/c++ compiler, compile it into c_wys_lib.so (on UNIX) or c_wys_lib.dll (on Windows). `wys_lib.py` will load it and use the c functions instead of the python ones. `wys_lib.py` will also "complain" when the .so/.dll file is not found.

### wys_playground.py

This is just a script to play with :). It imports wys_lib and there is commented code which would decrypt and reencrypt prevoius levels (first directly, then through the permutation utilities).

### wys_freq.py

This script counts characters in data variable, replace the used data inside the script, then run it. It'll give you character frequencies of all characters inside it

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

Check out [it's own readme :)](ab_v2/README.md) (warning! It's unfinished!)
