# WYS "ARG" tools

Warning: WYS spoilers ahead :)

## What is this?

There is a game called "Will you snail?" (WYS) by Jonas Tyroller. If you go to the Squid's presentation room after fixing him, there is some binary, which turned out to be a puzzle, and is being solved on WYS Discord (\#WYS binary decrypting (read pinned)). For more information look at the [doc](https://docs.google.com/document/d/1e_nOhSkTh9cchh8n5yDadvf-pnoi8CBZnHwZE0dsbcI/edit#).

## How to use?

I will go one by one here:

### wys_decrypt.py

This is a script containing functions to solve the solved part of the cypher. You can modify it to test new ideas, hopefully getting to next level! Use it as any other python3 script.

### wys_freq.py

This script counts characters in data variable, replace the string assigned to data inside the script, then run it.

### wys_indextable.py

This script will find all occurences of characters inside string and will print them in a table. It will ask you for data and string at runtime.

### algo_bruteforce.cpp

Probably the most interesting program here. It is written in C++ so you will need a C++ compiler to use it. On Linux you can use g++:

```shell
g++ algo_bruteforce.cpp -o algo -O3
./algo
```

on Windows it is a bit more complicated. You need to use Visual Studio or MinGW (with MinGW it's basically same as on Linux; I don't know how to use VS for C++).
I recommend using this program only if you know C++ at least a bit, so you know how to change the constants, in best case the algorithm. I might make something here about how to change constants and their meaning in the future.
