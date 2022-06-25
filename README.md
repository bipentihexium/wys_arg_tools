# WYS "ARG" tools

Warning: WYS spoilers ahead :)

- [WYS "ARG" tools](#wys-arg-tools)
	- [What is this?](#what-is-this)
	- [How to use?](#how-to-use)
		- [scripts](#scripts)
		- [algorithm bruteforcers](#algorithm-bruteforcers)
		- [key bruteforcers](#key-bruteforcers)

## What is this?

There is a game called "Will you snail?" (WYS) by Jonas Tyroller. If you go to the Squid's presentation room after fixing him, there is some binary, which turned out to be a puzzle, and is being solved on [WYS Discord (\#WYS binary decrypting (read pinned))](https://discord.gg/6Kk2FUHmgf). For more information look at the [doc](https://docs.google.com/document/d/1e_nOhSkTh9cchh8n5yDadvf-pnoi8CBZnHwZE0dsbcI/edit#).

**[wys arg decrypting toolkit](wys_lib_playground.md)** is probably the part that you came here for - the other stuff are small scripts and bruteforcers.

## How to use?

There is a lot of tools. The main part is **[wys arg decrypting toolkit :)](wys_lib_playground.md)**, but there are two [algorithm bruteforcers](#algorithm-bruteforcers), some [key bruteforcers](#key-bruteforcers) and multiple [scripts](#scripts).

### scripts

Scripts include [key tester](scripts/wys_test.py) ([doc](scripts/doc/wys_test.md)) and [index table with L2 key finder](scripts/wys_indextable.py) ([doc](scripts/doc/wys_indextable.md)).

### algorithm bruteforcers

There are two algortihm bruteforces, niether of them has good documentation :/. Each one has it's own folder and readme.
[algo_bruteforce's readme](algo_bruteforce/README.md) - algo_bruteforce tries random expressions and checks if it makes a valid message.
[ab_v2's readme](ab_v2/README.md) - ab_v2 tries random instructions and checks if it makes a valid message.

### key bruteforcers

There are ~~multiple~~ (now three, but two of them are unfinished and one of those is not even in the repo) key bruteforcers. The [first one](key_bruteforce/key_bruteforce.c) ([doc](key_bruteforce/doc/key_bruteforce_c.md)) is simple one-threaded C key bruteforcer.

TODO: other key bruteforcers - doc
