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
#include "../cfg.hpp"
#undef KEY_COUNT
#define KEY_COUNT 0
#include "../code.hpp"
#include "../machine.hpp"

bool test_machine(machine &m, const code_block &block, const std::vector<int> &expected, const std::string &msg) {
	m.reset(expected.size(), { });
	m.run(block);
	bool fail = m.res.size() != expected.size() || !std::equal(m.res.begin(), m.res.end(), expected.begin());
	if (fail) {
		std::cout << "[TEST-MACHINE-0-KEYS::FAIL]: " << msg << "\n\tcode:\n" << block.to_str() << "\n\tresult:\n\t\t";
		for (const auto &i : m.res) { std::cout << i << " "; }
		std::cout << "\n\texpected:\n\t\t";
		for (const auto &i : expected) { std::cout << i << " "; }
		std::cout << std::endl;
	}
	return fail;
}

int main() {
	bool fail = false;
	machine m;
	fail |= test_machine(m,
		code_block(code::codetype::LAST, {
			new code_block(code::codetype::WHILENOT, {
				new code(code::codetype::PUSH_RES),
#ifndef PUSH_RES_REMOVES
				new code(code::codetype::REMOVE_DATA),
#endif
			})
		}),
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }, "~{ < # } - keep");
	fail |= test_machine(m,
		code_block(code::codetype::LAST, {
			new code_block(code::codetype::WHILENOT, {
				new binary_op(code::codetype::ADD, binary_op::value_type::VALUE, 1),
				new binary_op(code::codetype::MOD, binary_op::value_type::DATALEN, 0),
				new code(code::codetype::PUSH_RES),
#ifndef PUSH_RES_REMOVES
				new code(code::codetype::REMOVE_DATA),
#endif
			})
		}),
		{ 1, 3, 5, 7, 9, 11, 13, 15, 2, 6, 10, 14, 4, 12, 8, 0 }, "~{ +1 %. < # } - dontbother1");
	return fail;
}
