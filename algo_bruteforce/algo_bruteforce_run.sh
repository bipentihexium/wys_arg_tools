#!/bin/bash
RESET="\x1b[0m"
CYAN="\x1b[96m"
LIME="\x1b[92m"
RED="\x1b[91m"

LPTHREAD="-lpthread"

do_debug_build=0
ignore_tests=0
use_gdb=0
while getopts "dig" opt
do
    case $opt in
    (d) do_debug_build=1 ;;
    (i) ignore_tests=1 ;;
    (g) do_debug_build=1; use_gdb=1 ;;
    esac
done

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
