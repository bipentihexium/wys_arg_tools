#ifndef __FILTER_HPP__
#define __FILTER_HPP__

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

#include "code.hpp"

bool filter_out(const code_block &block);
bool filter_out(const code *code) {
	switch (code->type) {
	case code::codetype::SWITCH_REG:
	case code::codetype::ADD:
	case code::codetype::SUB:
	case code::codetype::MUL:
	case code::codetype::DIV:
	case code::codetype::MOD:
	case code::codetype::MOV: return true;
	case code::codetype::PUSH_RES:
#ifndef PUSH_RES_REMOVES
	case code::codetype::REMOVE_DATA:
#endif
		return false;
	case code::codetype::TEST_EQ:
	case code::codetype::TEST_GT: return true;
	case code::codetype::IF:
	case code::codetype::WHILE:
	case code::codetype::IFNOT:
	case code::codetype::WHILENOT: return filter_out(*(const code_block *)code);
	case code::codetype::LAST: return true;
	}
	return true;
}
bool filter_out(const code_block &block) {
	for (const auto &i : block.instructions) {
		if (!filter_out(i.get())) {
			return false;
		}
	}
	return true;
}

#endif
