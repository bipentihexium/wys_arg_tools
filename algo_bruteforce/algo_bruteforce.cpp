/*
Copyright (c) 2022 bipentihexium

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#include <array>
#include <chrono>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#include <random>
#include <string>
#include <thread>
#include "algo_bruteforce_cfg.hpp"
#include "algo_bruteforce_expr.hpp"

template<int N>
constexpr int const_strlength(char const (&)[N]) { return N-1; }
template<typename T, int N>
constexpr int const_arrlength(T const (&)[N]) { return N; }
constexpr int datalen = const_strlength(data);
constexpr int keycount = const_arrlength(keys);

#include "algo_bruteforce_algos.hpp"

/**
 * @brief tests if function is valid message; valid message:
 *  - contains "DATA("
 *  - that is actually already enough to filter the messages :), no more complicated test needed
 */
bool ismsg(const std::string &msg) {
#ifdef CHECK_CLOSING_PAREN
	if (msg.back() != ')')
		return false;
#endif
	size_t pos = msg.find(message_string, 0);
	return pos != std::string::npos;
	//if (pos == std::string::npos)
	//	return false;
	//;
}

unsigned long int searched = 0;
std::chrono::high_resolution_clock::time_point search_start;
bool do_search = true;
#ifdef OUTFILE
std::ofstream outfile;
std::mutex outfilemutex;
#endif

void runtests() {
	uint_fast32_t seed = std::hash<std::thread::id>{}(std::this_thread::get_id());
	seed ^= std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 random_engine(seed);
	while (do_search) {
		ALGO_INDET_GEN(algo) a = ALGO_INDET_GEN(randAlgo)(random_engine);
		for (const char * const &key : keys) {
			std::string res = a.run(data, key);
			if (ismsg(res)) {
				std::cout << "============================== FOUND <KEY: " << key << "> ===============================" << std::endl <<
					a << std::endl << "-------------- out ------------------" << std::endl << res << std::endl;
#ifdef OUTFILE
				outfilemutex.lock();
				outfile.open(OUTFILE, std::ios_base::app);
				if (outfile.good()) {
					outfile << "============================== FOUND <KEY: " << key << "> ===============================" << std::endl <<
						a << std::endl << "-------------- out ------------------" << std::endl << res << std::endl;
					outfile.close();
					outfile.clear();
				} else {
					std::cout << "[ERROR]: Failed to append output to " OUTFILE << std::endl;
				}
				outfilemutex.unlock();
#endif
			}
		}
		if ((++searched)%searchprint == 0) {
			std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds millis = std::chrono::duration_cast<std::chrono::milliseconds>(now - search_start);
			std::cout << std::fixed << std::setprecision(searched_count_precision) << (searched/1000000.f) << "m algos searched; "
				"time: " << std::setprecision(search_time_precision) << (millis.count()/1000.f) << "s; "
				"avg search speed" << std::setprecision(search_speed_precision) << (searched/millis.count()/1000.f) << "m/s" << std::endl;
#ifdef OUTFILE
			if (searched%(searchprint*filesearchprintmodifier) == 0) {
				outfilemutex.lock();
				outfile.open(OUTFILE, std::ios_base::app);
				if (outfile.good()) {
					outfile << std::fixed << std::setprecision(searched_count_precision) << (searched/1000000.f) << "m algos searched; "
						"time: " << std::setprecision(search_time_precision) << (millis.count()/1000.f) << "s; "
						"avg search speed" << std::setprecision(search_speed_precision) << (searched/millis.count()/1000.f) << "m/s" << std::endl;;
					outfile.close();
					outfile.clear();
				} else {
					std::cout << "[ERROR]: Failed to append output to " OUTFILE << std::endl;
				}
				outfilemutex.unlock();
			}
#endif
		}
	}
}

int main() {
	outfile.open(OUTFILE, std::ios_base::app);
	if (outfile.good()) {
		outfile << std::endl << ">========================================================== NEW SEARCH =====================================================<" << std::endl;
		outfile.close();
		outfile.clear();
	} else {
		std::cout << "[ERROR]: Failed to append output to " OUTFILE << std::endl;
	}
	search_start = std::chrono::high_resolution_clock::now();
	std::array<std::unique_ptr<std::thread>, no_threads> thrs;
	do_search = true;
	for (auto &thr : thrs) {
		thr = std::unique_ptr<std::thread>(new std::thread(runtests));
	}
	std::string cmd;
	while (true) {
		std::getline(std::cin, cmd);
		if (cmd == "exit") {
			break;
		}
	}
	do_search = false;
	for (auto &thr : thrs) {
		thr->join();
	}
	return 0;
}
