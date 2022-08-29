/* Copyright (c) 2022 bipentihexium

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
OTHER DEALINGS IN THE SOFTWARE. */

// commands for g++:
// debug:
// g++ -o playground wys_playground_cpp.cpp -Wall -Wextra -Wpedantic -g -march=native -std=c++11
// ./playground
// speed:
// g++ -o playground wys_playground_cpp.cpp -Wall -Wextra -Wpedantic -O3 -march=native -std=c++11
// ./playground

#include <iostream>
#include "wys_lib_cpp.hpp"
#include "word_check.hpp"

int main() {
	//std::cout << dontbother17_decrypt(data1) << std::endl;
	//std::cout << dontbother17_encrypt(text2) << std::endl;
	//std::cout << humanscantsolvethis_decrypt(data2) << std::endl;
	//std::cout << humanscantsolvethis_encrypt(text3) << std::endl;
	//std::cout << sheismymother_decrypt(data3) << std::endl;
	//std::cout << sheismymother_encrypt(text4) << std::endl;
	//std::cout << processingpowercheck_decrypt(data4) << std::endl;
	//std::cout << processingpowercheck_encrypt(text5) << std::endl;
	constexpr auto used_data = data5;
	constexpr unsigned int word_min_limit = 3;
	constexpr unsigned int limit = 9;
	std::cout << "[word finder]" << std::endl;
	std::cout << "[data: " << used_data << "]" << std::endl;
	std::cout << "[limit: " << limit << "]" << std::endl;
	unsigned int results = 0;
	check_start(used_data, trie_node::load_file("./word_list.txt", word_min_limit), limit, [&results](const std::string &key) {
		std::string preview = humanscantsolvethis_decrypt_partial(used_data, key, 20);
		std::cout << key << ": " << preview.substr(0, limit) << '#' << preview.substr(limit) << std::endl;
		results++;
	});
	std::cout << results << " results found" << std::endl;
	std::cerr << results << " results found" << std::endl;
	return 0;
}
