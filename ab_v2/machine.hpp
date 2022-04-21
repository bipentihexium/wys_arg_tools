#ifndef __MACHINE_HPP__
#define __MACHINE_HPP__

#include <string.h>
#include "cfg.hpp"
#include "code.hpp"

class machine {
public:
	int *res;
	size_t reslen;

	inline machine() : res(nullptr), data(nullptr), key(nullptr) { }
	inline machine(size_t dlen, const int *k, size_t klen) {
		res = new int[0];
		data = new int[dlen];
		key = new int[klen];
		reset(dlen, k, klen);
	}
	inline ~machine() {
		if (res != nullptr) delete[] res;
		if (data != nullptr) delete[] data;
		if (key != nullptr) delete[] key;
	}
	inline void reset(size_t dlen, const int *k, size_t klen) {
		memcpy(key, k, klen * sizeof(int));
		datalen = dlen;
		for (int i = 0; i < datalen; ++i) { data[i] = i; }
		keylen = klen;
		delete[] res;
		res = new int[datalen];
		reslen = 0;
		activereg = reg;
		reg[0] = reg[1] = reg[2] = reg[3] = 0;
		flag = false;
		instrcount = 0;
	}
	inline void run(const code_block &block) {
		for (auto i = block.instructions.begin(); i != block.instructions.end() && instrcount < max_instrs; ++i) {
			run(i->get());
			++instrcount;
		}
		++instrcount;
	}
private:
	int reg[4];
	int *activereg;
	bool flag;
	int instrcount;

	int *data;
	int *key;
	size_t datalen;
	size_t keylen;

	inline void run(const code *c) {
		switch (c->type) {
			case code::codetype::SWITCH_REG_A: activereg = reg; break;
			case code::codetype::SWITCH_REG_B: activereg = reg+1; break;
			case code::codetype::SWITCH_REG_C: activereg = reg+2; break;
			case code::codetype::SWITCH_REG_D: activereg = reg+3; break;
			case code::codetype::MOV_A: *activereg = reg[0]; break;
			case code::codetype::MOV_B: *activereg = reg[1]; break;
			case code::codetype::MOV_C: *activereg = reg[2]; break;
			case code::codetype::MOV_D: *activereg = reg[3]; break;
#define RUN_BINARY(op) { binary_op *bop = (binary_op *)c; *activereg op ## = bop->is_rhs_reg ? reg[bop->rhs_value] : bop->rhs_value; }
			case code::codetype::ADD: RUN_BINARY(+) break;
			case code::codetype::SUB: RUN_BINARY(-) break;
			case code::codetype::MUL: RUN_BINARY(*) break;
#undef RUN_BINARY
#define RUN_DIV(op) { binary_op *bop = (binary_op *)c; int v = bop->is_rhs_reg ? reg[bop->rhs_value] : bop->rhs_value; if (v != 0) *activereg op ## = v; }
			case code::codetype::DIV: RUN_DIV(/) break;
			case code::codetype::MOD: RUN_DIV(%) break;
#undef RUN_DIV
			case code::codetype::PUSH_RES: { int i = reg[0] % datalen; res[reslen++] = data[i < 0 ? i + datalen : i]; } break;
			case code::codetype::REMOVE_DATA: { int i = reg[0] % datalen; if (i < 0) i += datalen; memcpy(data+i, data+i+1, datalen-i-1); } break;
			case code::codetype::TEST_DATA: { flag = datalen; } break;
#define RUN_BINARY_TEST(op, regid) { binary_op *bop = (binary_op *)c; flag = reg[regid] op (bop->is_rhs_reg ? reg[bop->rhs_value] : bop->rhs_value); }
			case code::codetype::TEST_A_GT: RUN_BINARY_TEST(>, 0) break;
			case code::codetype::TEST_A_EQ: RUN_BINARY_TEST(==, 0) break;
			case code::codetype::TEST_B_GT: RUN_BINARY_TEST(>, 1) break;
			case code::codetype::TEST_B_EQ: RUN_BINARY_TEST(==, 1) break;
			case code::codetype::TEST_C_GT: RUN_BINARY_TEST(>, 2) break;
			case code::codetype::TEST_C_EQ: RUN_BINARY_TEST(==, 2) break;
			case code::codetype::TEST_D_GT: RUN_BINARY_TEST(>, 3) break;
			case code::codetype::TEST_D_EQ: RUN_BINARY_TEST(==, 3) break;
#undef RUN_BINARY_TEST
			case code::codetype::IF: if (flag) { run(*((code_block *)c)); } break;
			case code::codetype::WHILE: while (flag) { run(*((code_block *)c)); } break;
			case code::codetype::IFNOT: if (!flag) { run(*((code_block *)c)); } break;
			case code::codetype::WHILENOT: while (!flag) { run(*((code_block *)c)); } break;
		}
	}
};

#endif
