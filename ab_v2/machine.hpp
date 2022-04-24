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
#include <map>
#include <numeric>
#include "cfg.hpp"
#include "code.hpp"
#include "util.hpp"

class machine {
public:
	int *res;
	size_t reslen;

	inline machine() : res(new int[0]), reslen(-1), data(nullptr), datalen(-1) {
		std::fill(keys.begin(), keys.end(), nullptr);
		std::fill(keylens.begin(), keylens.end(), -1);
	}
	inline machine(size_t dlen, const std::initializer_list<std::pair<const int *, size_t>> &ks) {
		res = new int[0];
		data = new int[dlen];
		currdatalen = datalen = dlen;
		reset(dlen, ks);
	}
	inline ~machine() {
		if (res != nullptr) delete[] res;
		if (data != nullptr) delete[] data;
		std::for_each(keys.begin(), keys.end(), [](int *const &k) { delete[] k; });
	}
	template<typename KEY_IT>
	inline void reset(size_t dlen, KEY_IT begin, KEY_IT end) {
		if (datalen != dlen) { if (datalen != static_cast<size_t>(-1)) delete[] data; data = new int[dlen]; }
		std::iota(data, data + dlen, 0);
		currdatalen = datalen = dlen;
		size_t i = 0;
		for (KEY_IT it = begin; it != end; ++it, ++i) {
			const auto &pair = *it;
			if (keylens[i] != pair.second) { if (keylens[i] != static_cast<size_t>(-1)) delete[] keys[i]; keys[i] = new int[pair.second]; }
			std::copy(pair.first, pair.first + pair.second, keys[i]);
			keylens[i] = pair.second;
		}
		delete[] res;
		res = new int[datalen];
		reslen = 0;
		activereg = reg;
		std::fill(std::begin(reg), std::end(reg), 0);
		flag = false;
		instrcount = 0;
	}
	inline void reset(size_t dlen, const std::initializer_list<std::pair<const int *, size_t>> &ks) {
		reset(dlen, ks.begin(), ks.end());
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

	int *data;
	size_t datalen;
	size_t currdatalen;
	std::array<int *, KEY_COUNT> keys;
	std::array<size_t, KEY_COUNT> keylens;

	inline void run(const code *c) {
		switch (c->type) {
		case code::codetype::SWITCH_REG: activereg = reg + ((reg_op *)c)->reg; break;
#define RUN_BINARY(op) *activereg op ## = get_binary_rhs_value((binary_op *)c);
		case code::codetype::ADD: RUN_BINARY(+) break;
		case code::codetype::SUB: RUN_BINARY(-) break;
		case code::codetype::MUL: RUN_BINARY(*) break;
#define RUN_DIV(op) { int v = get_binary_rhs_value((binary_op *)c); if (v != 0) *activereg op ## = v; }
		case code::codetype::DIV: RUN_DIV(/) break;
		case code::codetype::MOD: RUN_DIV(%) break;
#undef RUN_DIV
		case code::codetype::MOV: RUN_BINARY() break;
#undef RUN_BINARY
		case code::codetype::PUSH_RES: { // terminate when res is full
			int i = reg[0] % currdatalen;
			res[reslen++] = data[i < 0 ? i + currdatalen : i];
			if (reslen > datalen) {
				instrcount = max_instrs;
			}
			break;
		}
		case code::codetype::REMOVE_DATA:{
			int i = reg[0] % currdatalen;
			if (i < 0) i += currdatalen;
			for (size_t j = i+1; j < currdatalen; ++j) {
				data[j-1] = data[j];
			}
			--currdatalen;
			if (currdatalen < 1) { // terminate when data is empty
				instrcount = max_instrs;
			}
			break;
		}
		case code::codetype::TEST_DATA: { flag = currdatalen; } break;
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
			int regval = reg[c->rhs_value+1] % keylens[c->rhs_value];
			if (regval < 0)
				regval += c->rhs_value;
			return keys[c->rhs_value][regval];
		}
		case binary_op::value_type::DATALEN: return currdatalen;
		case binary_op::value_type::KEYLEN: return keylens[c->rhs_value];
		};
		return 0;
	}
};

#endif
