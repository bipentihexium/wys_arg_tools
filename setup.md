# Setup

- [Setup](#setup)
	- [Windows](#windows)
		- [Python scripts](#python-scripts)
			- [Installing Python](#installing-python)
			- [Using the scripts](#using-the-scripts)
		- [C and C++ programs](#c-and-c-programs)
			- [Compiler setup](#compiler-setup)
				- [Installing MinGW-w64](#installing-mingw-w64)
			- [Compiling](#compiling)
			- [CMake](#cmake)
	- [Linux](#linux)
		- [Python scripts](#python-scripts-1)
		- [C and C++ programs](#c-and-c-programs-1)
			- [Compiling](#compiling-1)
			- [CMake](#cmake-1)


## Windows

### Python scripts

To run the Python scripts, you need to have Python installed. It should be at least Python 3.6.

#### Installing Python

If you don't have Python installed already, you can download and install it from [www.python.org/downloads/](https://www.python.org/downloads/). It should be pretty straightforward to use :) .

#### Using the scripts

To run the python script, you can either run them from console - `python.exe <script>` or `py.exe <script>`, open them in Python IDLE (comes with Python on Windows) and run it using F5 / Run>Run module, or run it using IDE of your choice if it supports that.

### C and C++ programs

There is also stuff written in C/C++.

#### Compiler setup

It's trickier to setup on Windows, and there are many ways to do it. I'll cover here the one I'd recommend - MinGW-w64, but feel free to get/use your own compiler. Just note that I'll use commands for `gcc`/`g++` here.

##### Installing MinGW-w64

You can get the latest release in [releases for mingw-builds-binaries on github](https://github.com/niXman/mingw-builds-binaries/releases). Chose the version with posix and dwarf (dwarf exception handling + posix thread model), then i686 or x86_64 depending on your architecture. After downloading it, extract it (you may need 7zip for that). Then add the bin subdirectory to your PATH and you should be ready to use `gcc`/`g++` :) .

#### Compiling

The commands for each C/C++ program are in the doc for the program, like wys_lib.c has the command in it's [doc](wys_lib_playground.md#wys_libc).

#### CMake

TODO: setup - windows - cmake

## Linux

### Python scripts

On Linux, Python is usually preinstalled. Just check that your `python3` is at least Python 3.6 (you cen see the version by either running `python3` or `python3 --version` and update it with your package manager). To use the scripts, you can run them from console (`python3 <script>`) or using IDE of your choice if it supports that.

### C and C++ programs

A C/C++ compuler is usually preinstalled on Linux too - it's `gcc`/`g++`, which is the compiler I use here.

#### Compiling

The commands for each C/C++ program are in the doc for the program, like wys_lib.c has the command in it's [doc](wys_lib_playground.md#wys_libc).

#### CMake

TODO: setup - linux - cmake