# WYS "ARG" tools

Warning: WYS spoilers ahead :)

- [WYS "ARG" tools](#wys-arg-tools)
	- [What is this?](#what-is-this)
	- [Main features](#main-features)
		- [wys\_lib](#wys_lib)
		- [Simple L2A key bruteforcer in C](#simple-l2a-key-bruteforcer-in-c)
		- [Python GUI](#python-gui)
	- [Full feature list.](#full-feature-list)

## What is this?

If you're here, you have probably played the game "Will you snail?" made by Jonas Tyroller. When you go into Squid's presentation room after completing alternative ending, you're met with some binary data. It turned out to be a multi-level puzzle, and we are currently on level 5 out of 7 levels. If you are interested, you can read a bit [about how we get to the point where we are](history.md), or [about solutions to levels we solved already](solutions.md) (which is highly recommended if you want to help us). You can join us on [WYS Discord (\#WYS binary decrypting (read pinned))](https://discord.gg/6Kk2FUHmgf). You can also take a look at the [google doc](https://docs.google.com/document/d/1e_nOhSkTh9cchh8n5yDadvf-pnoi8CBZnHwZE0dsbcI/edit#) we use to collect all that we know.

This repository contains some useful tools for solving the WYS ARG. Since we all like different programming languages, some things here are written in multiple languages, (yet some things are written in only one language).

## Main features

### wys_lib

wys_lib is a library that should be present in most of the languages. Check out the folder named after your favorite language (of those present) to find what it can do. That's because not all wys_libs can do the same things. But all of them should be able to:

 - perform the dontbother, humanscantsolvethis and intelligencecheck algorithms
 - provide all data we got so far
 - provide keys we got so far

In a pair with each wys_lib, there's wys_playground, which is just an empty program, which imports/includes... wys_lib (it can contain some commented out examples).

### Simple L2A key bruteforcer in C

There's [c/simple_l2_key_bruteforce.c](c/simple_l2_key_bruteforce.c). It runs a simple depth-first search on all L2A keys (with iterative deepening) and it was made to try to solve L4.

### Python GUI

There's also a GUI made in python. Learn more about it in [it's doc](python/gui/gui.md).

## Full feature list.

 - raw data and texts in [data](data/) subfolder
 - wys_libs
 - simple L2 key bruteforcer in C
 - GUI in Python (using tkinter)
 - algorithm visualizer in Python (using pygame)
 - "key modification" bruteforcer in C++
