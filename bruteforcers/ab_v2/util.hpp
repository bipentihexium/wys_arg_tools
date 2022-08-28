#ifndef __UTIL_HPP__
#define __UTIL_HPP__

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

#include <stdint.h>
#include <chrono>
#include <string>
#include <thread>

std::string resolve_permutation(const std::string &data, const std::vector<int> &permutation) {
	std::string res;
	res.reserve(permutation.size());
	for (const auto &i : permutation) {
		res.push_back(data[i]);
	}
	return res;
}
std::string resolve_inverse_permutation(const std::string &data, const std::vector<int> &permutation) {
	std::string res(data.size(), '-');
	for (size_t i = 0; i < permutation.size(); ++i) {
		res[permutation[i]] = data[i];
	}
	return res;
}

template<typename T, size_t N>
constexpr size_t static_arrlen(T (&arr)[N]) { (void)arr; return N; }

#endif
