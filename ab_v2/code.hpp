#ifndef __CODE_HPP__
#define __CODE_HPP__

#include <memory>
#include <vector>

class code {
public:
	enum class codetype {
		SWITCH_REG_A, SWITCH_REG_B, SWITCH_REG_C, SWITCH_REG_D,
		MOV_A, MOV_B, MOV_C, MOV_D,
		ADD, SUB, MUL, DIV, MOD,
		PUSH_RES, REMOVE_DATA, TEST_DATA,
		TEST_A_GT, TEST_A_EQ, TEST_B_GT, TEST_B_EQ,
		TEST_C_GT, TEST_C_EQ, TEST_D_GT, TEST_D_EQ,
		IF, WHILE, IFNOT, WHILENOT
	};
	codetype type;

	inline code(codetype type) : type(type) { }
	inline virtual ~code() { }
};

class binary_op : public code {
public:
	bool is_rhs_reg;
	int rhs_value;
	inline binary_op(codetype type, bool is_rhs_reg, int rhs_value) : code(type), is_rhs_reg(is_rhs_reg), rhs_value(rhs_value) { }
};

class code_block : public code {
public:
	std::vector<std::unique_ptr<code>> instructions;
	inline code_block(codetype type) : code(type) { }
};

#endif
