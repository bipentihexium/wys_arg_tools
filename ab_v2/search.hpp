#ifndef __SEARCH_HPP__
#define __SEARCH_HPP__

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

#include <string.h>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include "cfg.hpp"
#include "codegen.hpp"
#include "filter.hpp"
#include "machine.hpp"
#include "util.hpp"

bool do_search = true;
unsigned long int searched = 0;

bool is_message(const std::string &potential_message) {
	auto it = potential_message.find(message_identifier);
	return it != std::string::npos;
}

void print_search_info(float secs_elapsed) {
	std::cout << SEARCH_INFO_FORMAT << std::endl;
}
void print_found_info() {
	;
}

std::vector<std::vector<int>> preprocess_keys() {
	std::vector<std::vector<int>> preprocessed_keys;
	preprocessed_keys.reserve(static_arrlen(keys));
	for (const auto &key : keys) {
		std::vector<int> preprocessed;
		preprocessed.reserve(strlen(key));
		for (const char *it = key; *it; ++it) {
			preprocessed.push_back(*it - ('A' - 1));
		}
		preprocessed_keys.push_back(preprocessed);
	};
	return preprocessed_keys;
}

template<bool inverse=false>
void found(const machine &mach, const code_block &block,
	const std::vector<const std::vector<int> *> &current_keys,
	const std::string &message) {
	std::cout << "------------------------ FOUND ---------------------------\n" <<
		"inverted: " << inverse <<
		"\tcode:\n" << block.to_str() <<
		"\tmessage:\n\t\t" << message <<
		"\n\tkeys:\n\t\t";
	for (const auto &i : current_keys) {
		for (const auto &j : *i) {
			std::cout << static_cast<char>(j + 'A' - 1);
		}
		std::cout << " ";
	}
	std::cout << "\n\tpermutation:\n\t\t";
	for (const auto &i : mach.res) { std::cout << i << " "; }
	std::cout << std::endl;
}

void try_keys(const std::vector<std::vector<int>> &preprocessed_keys,
	std::vector<const std::vector<int> *> &current_keys, machine &mach,
	const code_block &block, std::mt19937 &rand, size_t datalen, size_t depth=0) {
	if (depth >= KEY_COUNT) {
		mach.reset_key_ptrs(datalen, current_keys.begin(), current_keys.end());
		mach.run_code(block);
		if (!mach.res.empty()) {
			std::string message = resolve_permutation(data, mach.res);
			std::string message_inv = resolve_inverse_permutation(data, mach.res);
			if (is_message(message)) {
				found(mach, block, current_keys, message);
			}
			if (is_message(message_inv)) {
				found<true>(mach, block, current_keys, message_inv);
			}
		}
	} else {
		for (const auto &key : preprocessed_keys) {
			current_keys[depth] = &key;
			try_keys(preprocessed_keys, current_keys, mach, block, rand, datalen, depth + 1);
		}
	}
}

void search() {
	machine mach;
	std::random_device rd;
	std::mt19937 rand(rd());
	std::chrono::high_resolution_clock::time_point search_start = std::chrono::high_resolution_clock::now();
	size_t datalen = strlen(data);
	std::vector<std::vector<int>> preprocessed_keys = preprocess_keys();
	while (do_search) {
		code_block block = CODEGEN_FUNC(rand);
#ifdef DO_FILTER
		if (filter_out(block))
			continue;
#endif
		std::vector<const std::vector<int> *> current_keys(KEY_COUNT);
		try_keys(preprocessed_keys, current_keys, mach, block, rand, datalen);
		if (++searched % search_count_for_info == 0) {
			std::chrono::high_resolution_clock::time_point curr_time = std::chrono::high_resolution_clock::now();
			float elapsed_secs = std::chrono::duration_cast<std::chrono::microseconds>(curr_time - search_start).count() * 0.000001f;
			print_search_info(elapsed_secs);
		}
	}
}

#endif
