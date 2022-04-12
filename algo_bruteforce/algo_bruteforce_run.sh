#!/bin/bash
# Copyright (c) 2022 bipentihexium
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.

RESET="\x1b[0m"
CYAN="\x1b[96m"
LIME="\x1b[92m"
RED="\x1b[91m"

LPTHREAD="-lpthread"

do_debug_build=0
ignore_tests=0
use_gdb=0
regen_algo=1
while getopts "adgi" opt
do
    case $opt in
	(a) regen_algo=0 ;;
    (d) do_debug_build=1 ;;
    (i) ignore_tests=1 ;;
    (g) do_debug_build=1; use_gdb=1 ;;
    esac
done

if [ ${regen_algo} -eq 1 ]; then
	echo -e "${CYAN}Running algo_cpp_gen.py${RESET}"
	python3 ./algo_cpp_gen.py
	if [ $? -eq 0 ]; then
		echo -e "${LIME}Algo generation successful${RESET}"
	else
		echo -e "${RED}Algo generation failed${RESET}"
		exit -1
	fi
else
	echo -e "${CYAN}Skipping running algo_cpp_gen.py${RESET}"
fi

echo -e "${CYAN}building algo_bruteforce.cpp${RESET}"
if [ ${do_debug_build} -eq 1 ]; then
	g++ ./algo_bruteforce.cpp -o ./algo -g ${LPTHREAD} -std=c++17
else
	g++ ./algo_bruteforce.cpp -o ./algo -O3 ${LPTHREAD} -std=c++17
fi
if [ $? -eq 0 ]; then
    echo -e "${LIME}Built algo_bruteforce.cpp${RESET}"
else
    echo -e "${RED}Failed to build algo_bruteforce.cpp${RESET}"
	exit -1
fi

if [ ${ignore_tests} -eq 0 ]; then
	echo -e "${CYAN}building algo_bruteforce_test.cpp${RESET}"
	g++ ./algo_bruteforce_test.cpp -o ./algo_test -g ${LPTHREAD} -std=c++17
	if [ $? -eq 0 ]; then
		echo -e "${LIME}Built algo_bruteforce_test.cpp${RESET}"
	else
		echo -e "${RED}Failed to build algo_bruteforce_test.cpp${RESET}"
		exit -1
	fi

	./algo_test
	if [ $? -eq 0 ]; then
	    echo -e "${LIME}Test successful${RESET}"
	else
	    echo -e "${RED}Test failed${RESET}"
		exit -1
	fi
fi

if [ ${use_gdb} -eq 1 ]; then
	gdb algo
else
	./algo
fi

