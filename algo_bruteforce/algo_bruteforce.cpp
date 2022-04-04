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

#include <array>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>
#include "algo_bruteforce_cfg.hpp"
#include "algo_bruteforce_expr.hpp"

template<int N>
constexpr int const_strlength(char const (&)[N]) { return N-1; }
template<typename T, int N>
constexpr int const_arrlength(T const (&)[N]) { return N; }
constexpr int datalen = const_strlength(data);
constexpr int keycount = const_arrlength(keys);

bool ismsg(const std::string &msg) {
#ifdef CHECK_CLOSING_PAREN
	if (msg.back() != ')')
		return false;
#endif
	size_t pos = msg.find(message_string, 0);
	return pos != std::string::npos;
	//if (pos == std::string::npos)
	//	return false;
	//;
}

class algo {
public:
	int start_index;
	int start_keyindex;
	expr *index_expr;
	expr *keyindex_expr;

	algo(int si, int ski, expr *i, expr *ki) : start_index(si), start_keyindex(ski), index_expr(i), keyindex_expr(ki) {
#ifdef EXPR_OPTI
		index_expr->optimize();
		keyindex_expr->optimize();
#endif
	}
	~algo() {
		delete index_expr;
		delete keyindex_expr;
	}
	/**
	 * @brief runs the algorithm on data with key
	 * @returns resulting message
	 */
	std::string run(const char *data, const char *key) const {
		algo_context ctx;
		ctx.d = data;
		ctx.index = start_index;
		ctx.k = key;
		ctx.keyindex = start_keyindex % ctx.k.size();
#ifdef INV_ALGO
		std::string res(ctx.d.size(), '-');
		const char *c;
		for (c = data; *c; ++c) {
			int step = index_expr->get(ctx);
			step %= res.size()-(c-data);
			if (step > 0) {
				while (step) {
					ctx.index = (ctx.index + 1) % res.size();
					if (res[ctx.index] == '-') {
						step--;
					}
				}
			} else if (step < 0) {
				while (step) {
					ctx.index = (ctx.index - 1 + res.size()) % res.size();
					if (res[ctx.index] == '-') {
						step++;
					}
				}
			} else {
				return res;
			}
			ctx.keyindex = keyindex_expr->get(ctx);
			ctx.keyindex %= ctx.k.size();
			if (ctx.keyindex < 0) { ctx.keyindex += ctx.k.size(); }
			res[ctx.index] = *c;
		}
		return res;
#else
		std::string res;
		res.reserve(ctx.d.size());
		while (!ctx.d.empty()) {
			ctx.index = index_expr->get(ctx);
			ctx.index %= ctx.d.size();
			if (ctx.index < 0) { ctx.index += ctx.d.size(); }
			ctx.keyindex = keyindex_expr->get(ctx);
			ctx.keyindex %= ctx.k.size();
			if (ctx.keyindex < 0) { ctx.keyindex += ctx.k.size(); }
			res.push_back(ctx.d[ctx.index]);
			ctx.d.erase(ctx.index, 1);
		}
		return res;
#endif
	}
};
/**
 * @brief oputputs algorithm as a python function
 */
std::ostream &operator<<(std::ostream &o, const algo &a) {
#ifdef INV_ALGO
	o << "def algo(data, key):\n"
		"	key=[ord(c)-64 for c in key]\n"
		"	index=" << a.start_index << "\n"
		"	keyindex=" << a.start_keyindex << "\n"
		"	res='-'*len(data)\n"
		"	for char in data:\n"
		"		skip=" << *a.index_expr << "\n"
		"		if skip > 0:\n"
		"			while skip > 0\n"
		"				index=(index+1)%len(data)\n"
		"				if res[index] == '-':\n"
		"					skip -= 1\n"
		"		elif skip < 0:\n"
		"			while skip < 0\n"
		"				index=(index-1+len(data))%len(data)\n"
		"				if res[index] == '-':\n"
		"					skip += 1\n"
		"		else:\n"
		"			return res\n"
		"		index%=len(data)\n"
		"		keyindex=" << *a.keyindex_expr << "\n"
		"		while keyindex < 0: keyindex+=len(key)\n"
		"		keyindex%=len(key)\n"
		"		res[index]=char\n"
		"	return res";
#else
	o << "def algo(data, key):\n"
		"	key=[ord(c)-64 for c in key]\n"
		"	index=" << a.start_index << "\n"
		"	keyindex=" << a.start_keyindex << "\n"
		"	res=''\n"
		"	while data:\n"
		"		index=" << *a.index_expr << "\n"
		"		while index < 0: index+=len(data)\n"
		"		index%=len(data)\n"
		"		keyindex=" << *a.keyindex_expr << "\n"
		"		while keyindex < 0: keyindex+=len(key)\n"
		"		keyindex%=len(key)\n"
		"		res+=data[index]\n"
		"		data=data[:index]+data[index+1:]\n"
		"	return res";
#endif
	return o;
}
/**
 * @brief tests if function is valid message; valid message:
 *  - contains "DATA("
 *  - that is actually already enough to filter the messages :), no more complicated test needed
 */
#define R(n) (std::uniform_int_distribution<int>(0, (n)-1)(random_engine))
/**
 * @brief creates random expression leaf:
 *  - 90% chance to return random number between -30 ad 30
 *  - 10% chance to return ranodm variable
 */
template<typename RANDOM_T>
expr *randLeaf(RANDOM_T &random_engine) {
	if (R(10)) {
		return new expr(R(61)-30);
	} else {
		constexpr variable vars[] = { variable::INDEX, variable::KEYINDEX, variable::KEY };
		constexpr int varc = 3;
		return new expr(vars[R(varc)]);
	}
}
/**
 * @brief creates random expression from base:
 *  - it adds 0-3 operations to base
 *  - binary operations have second operand as random leaf (see randomLeaf()), but:
 *    > it has 25% chance to have some unary operator (currently only -a)
 *    > it has 1/7 chance to be in a binary expression with another random leaf
 */
template<typename RANDOM_T>
expr *randExpr(RANDOM_T &random_engine, expr *base) {
	int count = R(5);
	constexpr operation binops[] = { operation::ADD, operation::MULT, operation::ADD }; // add is there for second time to increase the chance of selecting it
	constexpr operation unops[] = { operation::REV };
	constexpr int binoplen = 3;
	constexpr int unoplen = 1;
	constexpr int sumlen = binoplen + unoplen;
	for (int i = 0; i < count; ++i) {
		int op = R(sumlen);
		if (op < binoplen) {
			expr *leaf = randLeaf(random_engine);
			if (!R(4)) {
				leaf = new expr(leaf, unops[R(unoplen)]);
			}
			if (!R(7)) {
				leaf = new expr(leaf, randLeaf(random_engine), binops[R(binoplen)]);
			}
			base = new expr(base, leaf, binops[op]);
		} else {
			base = new expr(base, unops[op-binoplen]);
		}
	}
	return base;
}
/**
 * @brief creates algorithm:
 *  - starts at random position (50% to start at 0, 50% to start at random position)
 *  - key iterator starts at random position (50% to start at 0, 50% to start at random position)
 *  - and then loops through data, changing index using random expression (which contains index, but it can be nullified (like index-index or index*0))
 *  - keyindex has also its own random expression
 */
template<typename RANDOM_T>
algo randAlgo(RANDOM_T &random_engine) {
#ifdef INV_ALGO
	return algo(R(2) * R(datalen), R(2) * R(datalen), randExpr(random_engine, randLeaf(random_engine)), randExpr(random_engine, new expr(variable::KEYINDEX)));
#else
	return algo(R(2) * R(datalen), R(2) * R(datalen), randExpr(random_engine, new expr(variable::INDEX)), randExpr(random_engine, new expr(variable::KEYINDEX)));
#endif
}
#undef R

unsigned long int searched = 0;
std::chrono::high_resolution_clock::time_point search_start;
bool do_search = true;

void runtests() {
	uint_fast32_t seed = std::hash<std::thread::id>{}(std::this_thread::get_id());
	seed ^= std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 random_engine(seed);
	while (do_search) {
		algo a = randAlgo(random_engine);
		for (const char * const &key : keys) {
			std::string res = a.run(data, key);
			if (ismsg(res)) {
				std::cout << "============================== FOUND <KEY: " << key << "> ===============================" << std::endl <<
					a << std::endl << "-------------- out ------------------" << std::endl << res << std::endl;
			}
		}
		if ((++searched)%searchprint == 0) {
			std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds millis = std::chrono::duration_cast<std::chrono::milliseconds>(now - search_start);
			std::cout << std::fixed << std::setprecision(searched_count_precision) << (searched/1000000.f) << "m algos searched; "
				"time: " << std::setprecision(search_time_precision) << (millis.count()/1000.f) << "s; "
				"avg search speed" << std::setprecision(search_speed_precision) << (searched/millis.count()/1000.f) << "m/s" << std::endl;
		}
	}
}

int main() {
	//algo a1(0, 0, new expr(new expr(variable::INDEX), new expr(17), operation::ADD), new expr(0)); // lvl1 algorithm
	//algo a2(0, 0, new expr(new expr(variable::INDEX), new expr(variable::KEY), operation::ADD),
	//	new expr(new expr(variable::KEYINDEX), new expr(1), operation::ADD)); // lvl2 algorithm
	search_start = std::chrono::high_resolution_clock::now();
	std::array<std::unique_ptr<std::thread>, no_threads> thrs;
	do_search = true;
	for (auto &thr : thrs) {
		thr = std::unique_ptr<std::thread>(new std::thread(runtests));
	}
	std::string cmd;
	while (true) {
		std::getline(std::cin, cmd);
		if (cmd == "exit") {
			break;
		}
	}
	do_search = false;
	for (auto &thr : thrs) {
		thr->join();
	}
	return 0;
}
