#ifndef __MACHINE_HPP__
#define __MACHINE_HPP__

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
#include <initializer_list>
#include <limits>
#include <numeric>
#include <vector>
#include "cfg.hpp"
#include "code.hpp"
#include "util.hpp"

class machine {
public:
	std::vector<int> res;

	inline machine() { }
	inline machine(size_t datalen, const std::initializer_list<std::vector<int>> &ks) {
		reset(datalen, ks);
	}
	template<typename KEY_IT>
	inline void reset(size_t datalen, KEY_IT begin, KEY_IT end) {
		data.resize(datalen, 0);
		std::iota(data.begin(), data.end(), 0);
		fulldatalen = datalen;
		size_t i = 0;
		for (KEY_IT it = begin; it != end; ++it, ++i) {
			keys[i].resize(it->size(), 0);
			std::copy(it->begin(), it->end(), keys[i].begin());
		}
		res.clear();
		res.reserve(fulldatalen);
		std::fill(std::begin(reg), std::end(reg), 0);
		activereg = reg;
		flag = false;
		instrcount = 0;
	}
	template<typename KEY_IT>
	inline void reset_key_ptrs(size_t datalen, KEY_IT begin, KEY_IT end) {
		data.resize(datalen, 0);
		std::iota(data.begin(), data.end(), 0);
		fulldatalen = datalen;
		size_t i = 0;
		for (KEY_IT it = begin; it != end; ++it, ++i) {
			const auto &j = *it;
			keys[i].resize(j->size(), 0);
			std::copy(j->begin(), j->end(), keys[i].begin());
		}
		res.clear();
		res.reserve(fulldatalen);
		std::fill(std::begin(reg), std::end(reg), 0);
		activereg = reg;
		flag = false;
		instrcount = 0;
	}
	inline void reset(size_t datalen, const std::initializer_list<std::vector<int>> &ks) {
		reset(datalen, ks.begin(), ks.end());
	}
	inline void run(const code_block &block) {
		for (auto i = block.instructions.begin(); i != block.instructions.end() && instrcount < max_instrs; ++i) {
			run(i->get());
			++instrcount;
		}
		++instrcount;
	}
private:
	int reg[register_count];
	int *activereg;
	bool flag;
	int instrcount;

	size_t fulldatalen;
	std::vector<int> data;
	std::array<std::vector<int>, KEY_COUNT> keys;

	inline void run(const code *c) {
		switch (c->type) {
		case code::codetype::SWITCH_REG: activereg = reg + ((reg_op *)c)->reg; break;
#define RUN_BINARY(op) *activereg op ## = get_binary_rhs_value((binary_op *)c);
		case code::codetype::ADD: RUN_BINARY(+) break;
		case code::codetype::SUB: RUN_BINARY(-) break;
		case code::codetype::MUL: RUN_BINARY(*) break;
#define RUN_DIV(op) { int v = get_binary_rhs_value((binary_op *)c); if (v != 0 && (v != -1 || *activereg != std::numeric_limits<int>::min())) *activereg op ## = v; }
		case code::codetype::DIV: RUN_DIV(/) break;
		case code::codetype::MOD: RUN_DIV(%) break;
#undef RUN_DIV
		case code::codetype::MOV: RUN_BINARY() break;
#undef RUN_BINARY
		case code::codetype::PUSH_RES: { // terminate when res is full
			int i = reg[0] % data.size();
			res.push_back(data[i < 0 ? i + data.size() : i]);
			if (res.size() > fulldatalen) {
				instrcount = max_instrs;
			}
			break;
		}
		case code::codetype::REMOVE_DATA:{
			int i = reg[0] % data.size();
			data.erase(data.begin() + (i < 0 ? i + data.size() : i));
			if (data.size() < 1) { // terminate when data is empty
				instrcount = max_instrs;
			}
			break;
		}
#define RUN_BINARY_TEST(op) flag = *activereg op get_binary_rhs_value((binary_op *)c);
		case code::codetype::TEST_GT: RUN_BINARY_TEST(>) break;
		case code::codetype::TEST_EQ: RUN_BINARY_TEST(==) break;
#undef RUN_BINARY_TEST
		case code::codetype::IF: if (flag) { run(*((code_block *)c)); } break;
		case code::codetype::WHILE: while (flag && instrcount < max_instrs) { run(*((code_block *)c)); } break;
		case code::codetype::IFNOT: if (!flag) { run(*((code_block *)c)); } break;
		case code::codetype::WHILENOT: while (!flag && instrcount < max_instrs) { run(*((code_block *)c)); } break;
		case code::codetype::LAST: break;
		}
	}
	inline int get_binary_rhs_value(binary_op *c) const {
		switch (c->rhs_type) {
		case binary_op::value_type::VALUE: return c->rhs_value;
		case binary_op::value_type::REG: return reg[c->rhs_value];
		case binary_op::value_type::KEY:{
			int regval = reg[c->rhs_value + 1] % keys[c->rhs_value].size();
			return keys[c->rhs_value][regval < 0 ? regval + keys[c->rhs_value].size() : regval];
		}
		case binary_op::value_type::DATALEN: return data.size();
		case binary_op::value_type::KEYLEN: return keys[c->rhs_value].size();
		};
		return 0;
	}
};

#endif
