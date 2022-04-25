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
#include "../cfg.hpp"
#include "../code.hpp"
#include "../codegen.hpp"

bool test_code(code *c) {
	switch (c->type) {
	case code::codetype::SWITCH_REG:{
		reg_op *r = dynamic_cast<reg_op *>(c);
		return r == nullptr || r->reg < 0 || r->reg >= register_count;
	}
	case code::codetype::ADD:
	case code::codetype::SUB:
	case code::codetype::MUL:
	case code::codetype::DIV:
	case code::codetype::MOD:
	case code::codetype::MOV:
	case code::codetype::TEST_EQ:
	case code::codetype::TEST_GT:{
		binary_op *b = dynamic_cast<binary_op *>(c);
		if (b == nullptr)
			return true;
		switch (b->rhs_type) {
		case binary_op::value_type::VALUE: return b->rhs_value < value_min || b->rhs_value > value_max;
		case binary_op::value_type::REG: return b->rhs_value < 0 || b->rhs_value >= register_count;
		case binary_op::value_type::KEY: return b->rhs_value < 0 || b->rhs_value >= KEY_COUNT;
		case binary_op::value_type::DATALEN: return false;
		case binary_op::value_type::KEYLEN: return b->rhs_value < 0 || b->rhs_value >= KEY_COUNT;
		}
		return true;
	}
	case code::codetype::PUSH_RES:
	case code::codetype::REMOVE_DATA:
		return dynamic_cast<binary_op *>(c) != nullptr || dynamic_cast<code_block *>(c) != nullptr || dynamic_cast<reg_op *>(c) != nullptr;
	case code::codetype::IF:
	case code::codetype::WHILE:
	case code::codetype::IFNOT:
	case code::codetype::WHILENOT:
	case code::codetype::LAST:{
		code_block *block = dynamic_cast<code_block *>(c);
		if (block == nullptr)
			return true;
		bool fail = false;
		for (const auto &i : block->instructions) {
			fail |= test_code(i.get());
		}
		return fail;
	}
	};
	return true;
}
bool test_codegen(const std::string &msg) {
	std::random_device rd;
	std::mt19937 rand(rd());
	code_block generated = generate_code(rand);
	bool fail = test_code(&generated);
	if (fail) {
		std::cout << "[TEST-CODEGEN::FAIL]: " << msg << "\n\tcode:\n" << generated.to_str() << std::endl;
	}
	return fail;
}

int main() {
	for (size_t i = 0; i < 10000; ++i) {
		if (test_codegen("codegen test " + std::to_string(i)))
			return 1;
	}
	return 0;
}
