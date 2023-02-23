# WYS "ARG" tools

Warning: WYS spoilers ahead :)

- [WYS "ARG" tools](#wys-arg-tools)
	- [What is this?](#what-is-this)
	- [WYS lib](#wys-lib)
	- [GUI](#gui)
	- [Setup](#setup)
	- [Scripts](#scripts)
	- [algorithm bruteforcers](#algorithm-bruteforcers)
	- [key bruteforcers](#key-bruteforcers)

## What is this?

If you're here, you have probably played the game "Will you snail?" made by Jonas Tytoller. When you go into Squid's presentation room after completing alternative ending, you're met with some binary data. It turned out to be a multi-level puzzle, and we are currently on level 5 out of 7 levels. If you are interested, you can read a bit [about how we get to the point where we are](history.md), or [about solutions to levels we solved already](solutions.md) (which is highly recommended if you want to help us). You can join us on [WYS Discord (\#WYS binary decrypting (read pinned))](https://discord.gg/6Kk2FUHmgf). You can also take a look at the [google doc](https://docs.google.com/document/d/1e_nOhSkTh9cchh8n5yDadvf-pnoi8CBZnHwZE0dsbcI/edit#) we use to collect all that we know.

There are multiple tools. Most importantly there's wys_lib, but there are some scripts and multiple bruteforcers I wrote while trying to decrypt the message. You can also find raw texts and data for each level in the [data](data/) subfolder.

## WYS lib

`wys_lib.py` is a Python library which contains some data and functions to aid you with solving. Check out [it's own documentation](wys_lib_py.md) to learn more! `wys_playground.py` is just a script which imports `wys_lib` and contains a few examples on how you could use it. `wys_lib.c` contains optional c implementation for many of the functions in `wys_lib.py`. You can learn more about it in `wys_lib.py`'s doc.

## GUI

To make functions of `wys_lib.py` more accessibe, there's also [a gui](gui/), which could be used to try decrypting.

## Setup

The [setup manual](setup.md) is in it's own file :) .

## Scripts

Scripts include [key tester](scripts/wys_test.py) ([doc](scripts/doc/wys_test.md)) and [index table with L2 key finder](scripts/wys_indextable.py) ([doc](scripts/doc/wys_indextable.md)).

## algorithm bruteforcers

There are two algortihm bruteforces, niether of them has good documentation :/. Both are written in C++ and each one has it's own folder and readme. There's not probably much use in trying to do something with them though.

[algo_bruteforce's readme](bruteforcers/algo_bruteforce/README.md) - algo_bruteforce tries random expressions and checks if it makes a valid message.

[ab_v2's readme](bruteforcers/ab_v2/README.md) - ab_v2 tries random instructions and checks if it makes a valid message.

## key bruteforcers

The [only documented key bruteforcer](bruteforcers/key_bruteforce/key_bruteforce.c) ([doc](bruteforcers/key_bruteforce/doc/key_bruteforce_c.md)) is simple one-threaded L2 key bruteforcer written in C.

TODO: other key bruteforcers - doc
