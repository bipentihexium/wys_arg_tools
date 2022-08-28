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

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <string>
#include "../util.hpp"

bool test_permutation_resolve(const std::string &msg, const std::string &data,
	const std::vector<int> &permutation, const std::string &expected) {
	std::string res = resolve_permutation(data, permutation);
	bool fail = res != expected;
	if (fail) {
		std::cout << "[TEST-PERMUTATION-RESOLVE::FAIL]: " << msg << 
			"\n\tgot:\n\t\t" << res << 
			"\n\texpected:\n\t\t" << expected <<
			"\n\tdata:\n\t\t" << data <<
			"\n\tpermutation:\n\t\t";
		for (const auto &i : permutation) { std::cout << i << " "; }
		std::cout << std::endl;
	}
	return fail;
}
bool test_permutation_resolve_inverse(const std::string &msg, const std::string &data,
	const std::vector<int> &permutation, const std::string &expected) {
	std::string res = resolve_inverse_permutation(data, permutation);
	bool fail = res != expected;
	if (fail) {
		std::cout << "[TEST-PERMUTATION-RESOLVE-INVERSE::FAIL]: " << msg << 
			"\n\tgot:\n\t\t" << res << 
			"\n\texpected:\n\t\t" << expected <<
			"\n\tdata:\n\t\t" << data <<
			"\n\tpermutation:\n\t\t";
		for (const auto &i : permutation) { std::cout << i << " "; }
		std::cout << std::endl;
	}
	return fail;
}

int main() {
	test_permutation_resolve("simple-res", "abcd", { 1, 2, 0, 3 }, "bcad");
	test_permutation_resolve("simple-res2", "elhol", { 2, 0, 1, 4, 3 }, "hello");
	test_permutation_resolve_inverse("simple-inv-res", "hello", { 2, 0, 1, 4, 3 }, "elhol");
	test_permutation_resolve_inverse("simple-inv-res-short-perm", "some long garbage string d", { 26, 1, 6, 8 }, "good");
	return 0;
}
