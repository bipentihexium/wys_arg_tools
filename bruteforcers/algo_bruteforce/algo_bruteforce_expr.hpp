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

#ifndef __EXPR_HPP__
#define __EXPR_HPP__

enum class operation {
	CONSTANT, VAR, REV, ADD, MULT, COUNT
};
enum class variable {
	INDEX, KEYINDEX, KEY, KEYLEN, KEYINDEX2, KEY2, KEYLEN2, DATA, DATALEN, COUNT
};
struct algo_context {
	int index;
	int keyindex;
	int keyindex2;
	std::string d;
	std::string k;
	std::string k2;
};
class expr;
std::ostream &operator<<(std::ostream &o, const expr &e);
bool valid(const expr &e);
void printExprDetail(const expr &e);
class expr {
public:
	expr *a;
	expr *b;
	int constant;
	variable var;
	operation op;

	/**
	 * @brief constructs empty expression
	 */
	expr() : a(nullptr), b(nullptr), constant(0), var(variable::INDEX), op(operation::CONSTANT) { }
	/**
	 * @brief constructs variable expression
	 */
	expr(variable v) : a(nullptr), b(nullptr), constant(0), var(v), op(operation::VAR) { }
	/**
	 * @brief constructs constant expression
	 */
	expr(int c) : a(nullptr), b(nullptr), constant(c), var(variable::INDEX), op(operation::CONSTANT) { }
	/**
	 * @brief constructs unary expression (from reference)
	 */
	expr(const expr &f, operation o) : b(nullptr), constant(0), var(variable::INDEX), op(o) {
		a = new expr(f);
	}
	/**
	 * @brief constructs binary expression (from references)
	 */
	expr(const expr &f, const expr &f2, operation o) : constant(0), var(variable::INDEX), op(o) {
		a = new expr(f);
		b = new expr(f2);
	}
	/**
	 * @brief constructs unary expression (from pointer, consumes it)
	 */
	expr(expr *f, operation o) : a(f), b(nullptr), constant(0), var(variable::INDEX), op(o) { }
	/**
	 * @brief constructs binary expression (from pointers, consumes them)
	 */
	expr(expr *f, expr *f2, operation o) : a(f), b(f2), constant(0), var(variable::INDEX), op(o) { }
	/**
	 * @brief copy constructor
	 */
	expr(const expr &f) : constant(f.constant), var(f.var), op(f.op) {
		a = f.a == nullptr ? nullptr : new expr(*f.a);
		b = f.b == nullptr ? nullptr : new expr(*f.b);
	}
	~expr() {
		if (a != nullptr) { delete a; }
		if (b != nullptr) { delete b; }
	}
	/**
	 * @brief gets value of expression in given context
	 */
	int get(const algo_context &c) const {
		switch (op) {
		case operation::CONSTANT: return constant;
		case operation::VAR:
			switch (var) {
			case variable::DATA: return c.d[c.index];
			case variable::DATALEN: return c.d.size();
			case variable::INDEX: return c.index;
			case variable::KEY: return c.k[c.keyindex]-'@';
			case variable::KEYINDEX: return c.keyindex;
			case variable::KEYLEN: return c.k.size();
			case variable::KEY2: return c.k2[c.keyindex2]-'@';
			case variable::KEYINDEX2: return c.keyindex2;
			case variable::KEYLEN2: return c.k2.size();
			default: return 0;
			}
		case operation::REV: return -a->get(c);
		case operation::ADD: return a->get(c) + b->get(c);
		case operation::MULT: return a->get(c) * b->get(c);
		default: return 0;
		};
	}
	/**
	 * @brief attempts to optimize the expression
	 */
	void optimize() {
		switch (op) {
		case operation::REV:
			a->optimize();
			if (a->op == operation::CONSTANT) { // -const => const
				op = operation::CONSTANT;
				constant = -a->constant;
				delete a;
				a = nullptr;
			} else if (a->op == operation::REV) { // --x => x
				expr *inside = a->a;
				op = inside->op;
				constant = inside->constant;
				var = inside->var;
				expr *temp_a = inside->a == nullptr ? nullptr : new expr(*inside->a);
				b = inside->b == nullptr ? nullptr : new expr(*inside->b);
				delete a;
				a = temp_a;
			}
			break;
		case operation::ADD:
			a->optimize();
			b->optimize();
			if (a->op == operation::CONSTANT) {
				if (b->op == operation::CONSTANT) { // const + const => const
					op = operation::CONSTANT;
					constant = a->constant+b->constant;
					delete a;
					delete b;
					a = b = nullptr;
				} else if (b->op == operation::ADD) {
					if (b->a->op == operation::CONSTANT) { // const + (const + x) => const + x
						a->constant += b->a->constant;
						expr *temp_b = new expr(*b->b);
						delete b;
						b = temp_b;
					} else if (b->b->op == operation::CONSTANT) { // const + (x + const) => const + x
						a->constant += b->b->constant;
						expr *temp_b = new expr(*b->a);
						delete b;
						b = temp_b;
					}
				}
			} else if (b->op == operation::CONSTANT) {
				if (a->op == operation::ADD) {
					if (a->a->op == operation::CONSTANT) { // (const + x) + const => x + const
						b->constant += a->a->constant;
						expr *temp_a = new expr(*a->b);
						delete a;
						a = temp_a;
					} else if (a->b->op == operation::CONSTANT) { // (x + const) + const => x + const
						b->constant += a->b->constant;
						expr *temp_a = new expr(*a->a);
						delete a;
						a = temp_a;
					}
				}
			}
			break;
		case operation::MULT:
			a->optimize();
			b->optimize();
			if (a->op == operation::CONSTANT) {
				if (b->op == operation::CONSTANT) { // const * const => const
					op = operation::CONSTANT;
					constant = a->constant*b->constant;
					delete a;
					delete b;
					a = b = nullptr;
				} else if (b->op == operation::MULT) {
					if (b->a->op == operation::CONSTANT) { // const * (const * x) => const * x
						a->constant *= b->a->constant;
						expr *temp_b = new expr(*b->b);
						delete b;
						b = temp_b;
					} else if (b->b->op == operation::CONSTANT) { // const * (x * const) => const * x
						a->constant *= b->b->constant;
						expr *temp_b = new expr(*b->a);
						delete b;
						b = temp_b;
					}
				}
			} else if (b->op == operation::CONSTANT) {
				if (a->op == operation::MULT) {
					if (a->a->op == operation::CONSTANT) { // (const * x) * const => x * const
						b->constant *= a->a->constant;
						expr *temp_a = new expr(*a->b);
						delete a;
						a = temp_a;
					} else if (a->b->op == operation::CONSTANT) { // (x * const) * const => x * const
						b->constant *= a->b->constant;
						expr *temp_a = new expr(*a->a);
						delete a;
						a = temp_a;
					}
				}
			}
			break;
		default: break;
		};
	}
};
/**
 * @brief oputputs expression
 */
std::ostream &operator<<(std::ostream &o, const expr &e) {
	switch (e.op) {
	case operation::CONSTANT: o << e.constant; break;
	case operation::VAR:
		switch (e.var) {
		case variable::DATA: o << "data[index]"; break;
		case variable::DATALEN: o << "len(data)"; break;
		case variable::INDEX: o << "index"; break;
		case variable::KEY: o << "key[keyindex]"; break;
		case variable::KEYINDEX: o << "keyindex"; break;
		case variable::KEYLEN: o << "len(key)"; break;
		case variable::KEY2: o << "key2[keyindex2]"; break;
		case variable::KEYINDEX2: o << "keyindex2"; break;
		case variable::KEYLEN2: o << "len(key2)"; break;
		default: break;
		}
		break;
	case operation::REV: o << "-" << *e.a; break;
	case operation::ADD: o << "(" << *e.a << "+" << *e.b << ")"; break;
	case operation::MULT: o << "(" << *e.a << "*" << *e.b << ")"; break;
	default: break;
	};
	return o;
}

#endif
