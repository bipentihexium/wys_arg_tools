# key_bruteforce.c

This is the most basic key bruteforcer here. It searches all keys with L2 algorithm and checks for `; DATA(` in the result. To use it, replace the data (on line 5). It's written in C, so you'll need to compile it before running it.

With `g++`, I'd recommend this command: `g++ -Wall -O3 -march=native -o key_bruteforce.exe key_bruteforce.c` (Windows+MinGW) `g++ -Wall -O3 -march=native -o key_bruteforce key_bruteforce.c` (linux) - `-Wall` turns on warnings, `-O3` optimizes for speed and `-march=native` uses local architecture (which makes the executable less cross-platform tho).
