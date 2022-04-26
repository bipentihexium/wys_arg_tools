#ifndef __CODEGEN_HPP__
#define __CODEGEN_HPP__

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

#include <memory>
#include <random>
#include "cfg.hpp"
#include "code.hpp"

namespace {
	template<typename R_T>
	inline int generate_val(R_T &random_engine, binary_op::value_type &rhs_reg) {
		rhs_reg = static_cast<binary_op::value_type>(
			std::uniform_int_distribution<int>(0, KEY_COUNT > 0
				? static_cast<int>(binary_op::value_type::KEYLEN)
				: static_cast<int>(binary_op::value_type::DATALEN))(random_engine));
		switch (rhs_reg) {
		case binary_op::value_type::VALUE: return std::uniform_int_distribution<int>(value_min, value_max)(random_engine);
		case binary_op::value_type::REG: return std::uniform_int_distribution<int>(0, register_count - 1)(random_engine);
		case binary_op::value_type::DATALEN: return 0;
		case binary_op::value_type::KEY:
		case binary_op::value_type::KEYLEN: return std::uniform_int_distribution<int>(0, KEY_COUNT - 1)(random_engine);
		}
		return 0;
	}

	template<typename R_T>
	inline void generate_block(R_T &random_engine, code_block &block, int depth);

	template<typename R_T>
	inline std::unique_ptr<code> generate_instr(R_T &random_engine, int depth) {
		int max = depth < 4 ? static_cast<int>(code::codetype::LAST)-1 : static_cast<int>(code::codetype::IF)-1;
		code::codetype inst_type = static_cast<code::codetype>(std::uniform_int_distribution<int>(0, max)(random_engine));
		switch (inst_type) {
		case code::codetype::SWITCH_REG:{
			int rg = std::uniform_int_distribution<int>(0, register_count - 1)(random_engine);
			return std::unique_ptr<code>(new reg_op(inst_type, rg));
		}
		case code::codetype::ADD:
		case code::codetype::SUB:
		case code::codetype::MUL:
		case code::codetype::DIV:
		case code::codetype::MOD:
		case code::codetype::MOV:{
			binary_op::value_type rhs_type;
			int rhs_val = generate_val(random_engine, rhs_type);
			return std::unique_ptr<code>(new binary_op(inst_type, rhs_type, rhs_val));
		}
		case code::codetype::PUSH_RES:
#ifndef PUSH_RES_REMOVES
		case code::codetype::REMOVE_DATA:
#endif
			return std::unique_ptr<code>(new code(inst_type));
		case code::codetype::TEST_GT:
		case code::codetype::TEST_EQ:{
			binary_op::value_type rhs_type;
			int rhs_val = generate_val(random_engine, rhs_type);
			return std::unique_ptr<code>(new binary_op(inst_type, rhs_type, rhs_val));
		}
		case code::codetype::IF:
		case code::codetype::WHILE:
		case code::codetype::IFNOT:
		case code::codetype::WHILENOT:{
			auto block = std::unique_ptr<code>(new code_block(inst_type));
			generate_block(random_engine, *(code_block *)block.get(), depth);
			return block;
		}
		case code::codetype::LAST:
			return std::unique_ptr<code>(nullptr);
		}
		return std::unique_ptr<code>(nullptr);
	}

	template<typename R_T>
	inline void generate_block(R_T &random_engine, code_block &block, int depth) {
		static const int instr_count_mins[] = { 3, 1, 1, 1, 1 };
		static const int instr_count_maxs[] = { 9, 4, 3, 2, 1 };

		int instrs = std::uniform_int_distribution<int>(instr_count_mins[depth], instr_count_maxs[depth])(random_engine);
		block.instructions.reserve(instrs);
		for (int i = 0; i < instrs; ++i) {
			block.instructions.push_back(std::move(generate_instr(random_engine, depth + 1)));
		}
	}
}

template<typename R_T>
inline code_block generate_code(R_T &random_engine) {
	code_block out(code::codetype::LAST);
	generate_block(random_engine, out, 0);
	return out;
}
template<typename R_T>
inline code_block generate_code_restricted_for_HCSTSBSH(R_T &random_engine) {
	code_block out(code::codetype::LAST);

	out.instructions.reserve(12);
	int instrs = std::uniform_int_distribution<int>(0, 3)(random_engine);
	for (int i = 0; i < instrs; ++i) {
		out.instructions.push_back(std::move(generate_instr(random_engine, 1)));
	}
	out.instructions.emplace_back(new reg_op(code::codetype::SWITCH_REG, 1));
	instrs = std::uniform_int_distribution<int>(0, 3)(random_engine);
	for (int i = 0; i < instrs; ++i) {
		out.instructions.push_back(std::move(generate_instr(random_engine, 1)));
	}
	out.instructions.emplace_back(new reg_op(code::codetype::SWITCH_REG, 0));
	instrs = std::uniform_int_distribution<int>(0, 3)(random_engine);
	for (int i = 0; i < instrs; ++i) {
		out.instructions.push_back(std::move(generate_instr(random_engine, 1)));
	}
	out.instructions.emplace_back(new code(code::codetype::PUSH_RES));
	return out;
}

#endif
