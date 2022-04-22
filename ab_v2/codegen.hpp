#ifndef __CODEGEN_HPP__
#define __CODEGEN_HPP__

#include <memory>
#include <random>
#include "cfg.hpp"
#include "code.hpp"

template<typename R_T>
code_block generate_code(R_T &random_engine) {
	code_block out(code::codetype::IF);
	generate_block(random_engine, out, 0);
	return out;
}

template<typename R_T>
void generate_block(R_T &random_engine, code_block &block, int depth) {
	int insts = std::uniform_int_distribution((9-depth)/3, 9-depth)(random_engine);
	block.instructions.reserve(insts);
	for (int i = 0; i < insts; ++i) {
		block.instructions.push_back(std::move(generate_instr(random_engine, depth-1)));
	}
}

template<typename R_T>
std::unique_ptr<code> generate_instr(R_T &random_engine, int depth) {
	code::codetype inst_type = static_cast<code::codetype>(std::uniform_int_distribution(0, code::codetype::LAST-1)(random_engine));
	switch (inst_type) {
	case code::codetype::SWITCH_REG_A:
	case code::codetype::SWITCH_REG_B:
	case code::codetype::SWITCH_REG_C:
	case code::codetype::SWITCH_REG_D:
	case code::codetype::MOV_A:
	case code::codetype::MOV_B:
	case code::codetype::MOV_C:
	case code::codetype::MOV_D: return std::unique_ptr<code>(new code(inst_type));
	case code::codetype::ADD:
	case code::codetype::SUB:
	case code::codetype::MUL:
	case code::codetype::DIV:
	case code::codetype::MOD: { bool rhs_reg; int rhs_val = generate_val(random_engine, rhs_reg); return std::unique_ptr<code>(new binary_op(inst_type, rhs_reg, rhs_val)); }
	case code::codetype::PUSH_RES:
	case code::codetype::REMOVE_DATA:
	case code::codetype::TEST_DATA: return std::unique_ptr<code>(new code(inst_type));
	case code::codetype::TEST_A_GT:
	case code::codetype::TEST_A_EQ:
	case code::codetype::TEST_B_GT:
	case code::codetype::TEST_B_EQ:
	case code::codetype::TEST_C_GT:
	case code::codetype::TEST_C_EQ:
	case code::codetype::TEST_D_GT:
	case code::codetype::TEST_D_EQ: { bool rhs_reg; int rhs_val = generate_val(random_engine, rhs_reg); return std::unique_ptr<code>(new binary_op(inst_type, rhs_reg, rhs_val)); }
	case code::codetype::IF:
	case code::codetype::WHILE:
	case code::codetype::IFNOT:
	case code::codetype::WHILENOT: auto block = std::unique_ptr<code>(new code_block(inst_type)); generate_block(random_engine, *(code_block *)block.get(), depth); return std::move(block);
	case code::codetype::LAST: return std::unique_ptr<code>(nullptr);
	}
}

template<typename R_T>
int generate_val(R_T &random_engine, bool &rhs_reg) {
	const static std::uniform_int_distribution reg_chance_dist = std::uniform_int_distribution(1, value_reg_chance);
	const static std::uniform_int_distribution reg_dist = std::uniform_int_distribution(0, 3);
	const static std::uniform_int_distribution value_dist = std::uniform_int_distribution(value_min, value_max);
	rhs_reg = reg_chance_dist(random_engine) == 1;
	if (rhs_reg) {
		return reg_dist(random_engine);
	} else {
		return value_dist(random_engine);
	}
}

#endif
