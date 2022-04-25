#ifndef __CODE_HPP__
#define __CODE_HPP__

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

#include <initializer_list>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class code {
public:
	enum class codetype {
		SWITCH_REG,
		ADD, SUB, MUL, DIV, MOD, MOV,
		PUSH_RES, REMOVE_DATA,
		TEST_EQ, TEST_GT,
		IF, WHILE, IFNOT, WHILENOT,
		LAST
	};
	static std::string to_str(const codetype &type) {
		switch (type) {
		case codetype::SWITCH_REG: return "REG_SWITCH";
		case codetype::ADD: return "ADD";
		case codetype::SUB: return "SUB";
		case codetype::MUL: return "MUL";
		case codetype::DIV: return "DIV";
		case codetype::MOD: return "MOD";
		case codetype::MOV: return "MOV";
		case codetype::PUSH_RES: return "PUSH_RES";
		case codetype::REMOVE_DATA: return "REMOVE_DATA";
		case codetype::TEST_EQ: return "TEST_EQ";
		case codetype::TEST_GT: return "TEST_GT";
		case codetype::IF: return "IF";
		case codetype::WHILE: return "WHILE";
		case codetype::IFNOT: return "IF_NOT";
		case codetype::WHILENOT: return "WHILE_NOT";
		case codetype::LAST: return "???";
		}
		return "??????";
	}
	codetype type;

	inline code(codetype type) : type(type) { }
	inline virtual ~code() { }
	inline virtual std::string to_str() const { return code::to_str(type) + "\n"; }
};

class binary_op : public code {
public:
	enum class value_type { VALUE, REG, DATALEN, KEY, KEYLEN }; // TODO: Don't forget to disable generating KEY and KEYLEN when KEY_COUNT is 0
	static std::string to_str(const value_type &type) {
		switch (type) {
		case value_type::VALUE: return "VAL";
		case value_type::REG: return "REG";
		case value_type::KEY: return "KEY";
		case value_type::DATALEN: return "DATALEN";
		case value_type::KEYLEN: return "KEYLEN";
		}
		return "???";
	}
	int rhs_value;
	value_type rhs_type;
	inline binary_op(codetype type, value_type rhs_type, int rhs_value) : code(type), rhs_value(rhs_value), rhs_type(rhs_type) { }
	inline std::string to_str() const override {
		return code::to_str(type) + " " + binary_op::to_str(rhs_type) + "{" + std::to_string(rhs_value) + "}\n";
	}
};

class reg_op : public code {
public:
	int reg;
	inline reg_op(codetype type, int reg) : code(type), reg(reg) { }
	inline std::string to_str() const override {
		return code::to_str(type) + " REG" + "{" + std::to_string(reg) + "}\n";
	}
};

class code_block : public code {
public:
	std::vector<std::unique_ptr<code>> instructions;
	inline code_block(codetype type) : code(type) { }
	inline code_block(codetype type, const std::initializer_list<code *> &instrs) : code(type) {
		instructions.reserve(instrs.size());
		for (const auto &i : instrs) {
			instructions.push_back(std::unique_ptr<code>(i));
		}
	}
	inline std::string to_str() const override {
		std::stringstream res;
		res << code::to_str(type) + "\n";
		for (const auto &instr : instructions) {
			std::string i_str(instr->to_str());
			auto it = i_str.find('\n');
			if (it != std::string::npos) {
				while (true) {
					auto next = i_str.find('\n', it + 1);
					if (next == std::string::npos)
						break;
					i_str.insert(it+1, 1, '\t');
					it = next+1;
				}
			}
			res << "\t" << i_str;
		}
		return res.str();
	}
};

#endif
