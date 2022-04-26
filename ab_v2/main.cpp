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
#include <iostream>
#include <memory>
#include <thread>
#include "cfg.hpp"
#include "search.hpp"

int main() {
	std::cout << CONFIG_INFO_FORMAT << std::endl;
	std::array<std::unique_ptr<std::thread>, no_threads> threads;
	for (auto &thr : threads) {
		thr = std::unique_ptr<std::thread>(new std::thread(search));
	}
	std::string in;
	do {
		std::getline(std::cin, in);
	} while (in != "exit");
	do_search = false;
	for (auto &thr : threads) {
		thr->join();
	}
	return 0;
}
