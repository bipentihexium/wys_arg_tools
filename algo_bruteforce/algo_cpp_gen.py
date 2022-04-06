"""
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
"""

# warning: this is an ugly script
# I apologize to those who wanted to read the code

import sys
import time
import re

class Lex: # just a lexer
	def __init__(self, rules):
		self.rules = rules
	def lex(self, text):
		line = 1
		col = 1
		res = []
		while text:
			for r in self.rules:
				m = re.match(r, text)
				if m:
					s = m.group(0)
					res.append((s, line, col))
					text = text[len(s):]
					if '\n' in s:
						line += s.count('\n')
						col = len(s)-s.rfind('\n')
					else:
						col += len(s)
					break
			else:
				print(f"Syntax error at {line}:{col}")
				break
		return res
# lexer rules (regex patterns)
special = [r"\[[a-z_]+\]", r"\{", r"\}", r"//.*", r"#\?", r"#", r"\$[a-z_0-9A-Z]+", "\".*\"", r"'.'"]
keywords = ["if", "else", "elif", "while", "int"]
keyvars = [r"index", r"keyindex", r"\.\.data", r"\.\.key", r"data", r"key"]
operators = [r"\+", r"\-", r"\*", r"/", r"%", r",", r"=", r"\+=", r"\-=", r"\*=", r"/=", r"%=", r"\(", r"\)", r"\[", r"\]", r"<", r">", r"<=", r">=", r"=="]
other = [r":", r"[a-zA-Z_][a-zA-Z_0-9]*", r"[0-9]+", r"0x[0-9a-fA-F]+", r"\s+", r";"]
rules = [*special, *keywords, *keyvars, *operators, *other]
lex = Lex(rules)

# algorithm generator
class algo:
	def __init__(self, toks):
		self.data = self.parsedata(toks)
		self.iconstants, self.econstants = self.get_constants()
		self.fadd = "_" + self.data["[name]"][1:-1]
	@classmethod
	def parsedata(cls, toks, gen=False):
		"""
		parses trees like this:
		[<name>]{
			[<name>]{
				<data>
			}
			[<name>]{
				<data>
			}
			[<name>]{
				[<name>]{
					<data>
				}
			}
		}
		"""
		dat = {}
		if not re.match(r"\[[a-z_]+\]", toks[0][0]):
			cls.syntax_err(toks[0], "[<name>]{<data>} expected")
		dat["[name]"] = toks[0][0]
		if toks[1][0] != "{":
			cls.syntax_err(toks[1], "{ expected after " + toks[0][0])
		del toks[:2]
		if re.match(r"\[[a-z_]+\]", toks[0][0]):
			while toks[0][0] != "}":
				n = toks[0][0]
				dat[n] = cls.parsedata(toks, gen or dat["[name]"] == "[generator]")
			del toks[0]
			return dat
		else:
			skip = 0
			i = 0
			tl = "" if gen else []
			while skip >= 0:
				if i >= len(toks):
					print(toks)
					time.sleep(1)
					cls.syntax_err(toks[i-1], "unclosed { in " + dat["[name]"])
				if toks[i][0] == "{":
					skip += 1
				elif toks[i][0] == "}":
					skip -= 1
				if gen:
					tl += toks[i][0]
				else:
					tl.append(toks[i])
				i += 1
			del toks[:i]
			return tl[:-1].split(",") if gen else tl[:-1]
	@classmethod
	def syntax_err(cls, tok, msg=""):
		print(f"Syntax error at {tok[0]} - {tok[1] if len(tok)>1 else '?'}:{tok[2] if len(tok)>2 else '?'}: " + msg)
		sys.exit(-1)
	def make_generator(self):
		"""
		returns string with generated c++ code for algo generator
		"""
		g = self.data["[generator]"]
		leaf = g["[leaf]"]
		expr = g["[expr]"]
		vars = {"..data":"datalen"}
		evars = {"index":"new expr(variable::INDEX)", "keyindex":"new expr(variable::KEYINDEX)","#?":f"randLeaf{self.fadd}()"}
		randparams = ", ".join([*["R("+(vars[x] if x in vars else str(x))+")" for x in self.iconstants],\
			*["randExpr"+self.fadd+"(random_engine, "+evars[x]+")" for x in self.econstants]])
		return f"""
#define R(n) (std::uniform_int_distribution<int>(0, (n)-1)(random_engine))
template<typename RANDOM_T>
expr *randLeaf{self.fadd}(RANDOM_T &random_engine) {{
	if (R({leaf["[var_chance]"][0]})) {{
		return new expr(R({int(leaf["[num_range]"][1])-int(leaf["[num_range]"][0])})+{leaf["[num_range]"][0]});
	}} else {{
		constexpr variable vars[] = {{ variable::INDEX, variable::KEYINDEX, variable::KEY }};
		constexpr int varc = 3;
		return new expr(vars[R(varc)]);
	}}
}}
template<typename RANDOM_T>
expr *randExpr{self.fadd}(RANDOM_T &random_engine, expr *base) {{
	int count = R({expr["[main_operations_max]"][0]});
	constexpr operation binops[] = {{ operation::ADD, operation::MULT, operation::ADD }}; // add is there for second time to increase the chance of selecting it
	constexpr operation unops[] = {{ operation::REV }};
	constexpr int binoplen = 3;
	constexpr int unoplen = 1;
	constexpr int sumlen = binoplen + unoplen;
	for (int i = 0; i < count; ++i) {{
		int op = R(sumlen);
		if (op < binoplen) {{
			expr *leaf = randLeaf{self.fadd}(random_engine);
			if (!R({expr["[leaf_unop_chance]"][0]})) {{
				leaf = new expr(leaf, unops[R(unoplen)]);
			}}
			if (!R({expr["[leaf_binop_chance]"][0]})) {{
				leaf = new expr(leaf, randLeaf{self.fadd}(random_engine), binops[R(binoplen)]);
			}}
			base = new expr(base, leaf, binops[op]);
		}} else {{
			base = new expr(base, unops[op-binoplen]);
		}}
	}}
	return base;
}}

template<typename RANDOM_T>
algo{self.fadd} randAlgo{self.fadd}(RANDOM_T &random_engine) {{
	return algo{self.fadd}({randparams});
}}
#undef R
"""
	def get_constants(self):
		"""
		finds randomized constants in [algorithm]
		"""
		int_consts = []
		expr_consts = []
		a = self.data["[algorithm]"]
		i = 0
		while i < len(a):
			if a[i][0] == "#":
				if a[i+1][0] == "{":
					if a[i+3][0] == "}":
						j = len(int_consts)
						if re.match(r"\-?[0-9]+", a[i+2][0]):
							int_consts.append(int(a[i+2][0]))
						else:
							int_consts.append(a[i+2][0])
						del a[i+1:i+4]
						a[i] = (f"#{j}", *a[i][1:])
					else:
						self.syntax_err(a[i+3], "expected } in rand")
				else:
					self.syntax_err(a[i+1], "exprected { in rand")
			elif a[i][0] == "#?":
				if a[i+1][0] == "{":
					if a[i+3][0] == "}":
						j = len(expr_consts)
						expr_consts.append(a[i+2][0])
						del a[i+1:i+4]
						a[i] = (f"#?{j}", *a[i][1:])
					else:
						self.syntax_err(a[i+3], "expected } in expr rand")
				else:
					self.syntax_err(a[i+1], "expected } in expr rand")
			i += 1
		return int_consts, expr_consts
	def gen_algo(self):
		"""
		returns string with generated c++ code for algo
		"""
		ici = ["_ic"+str(x) for x in range(len(self.iconstants))]
		eci = ["_ec"+str(x) for x in range(len(self.econstants))]
		icd = "int " + ", ".join(ici) + ";" if self.iconstants else ""
		ecd = "expr *" + ", *".join(eci) + ";" if self.econstants else ""
		icp = ", ".join(["int "+x for x in ici]) if self.iconstants else ""
		ecp = ", ".join(["expr *"+x for x in eci]) if self.econstants else ""
		ctor_params = ", ".join([x for x in [icp, ecp] if x])
		ctor_initializers = ", ".join([x+"("+x+")" for x in [*ici, *eci]])
		expr_const_opti = "\n\t\t".join([x+"->optimize();" for x in eci])
		expr_const_dest = "\n\t\t".join(["delete "+x+";" for x in eci])
		py_code = "\n\t\t".join(['"'+l+'\\n"' for l in self.gen_pycode(ici, eci).split('\n')])
		return f"""
class algo{self.fadd} {{
public:
	{icd}
	{ecd}

	algo{self.fadd}({ctor_params}) : {ctor_initializers} {{
#ifdef EXPR_OPTI
		{expr_const_opti}
#endif
	}}
	~algo{self.fadd}() {{
		{expr_const_dest}
	}}
	/**
	 * @brief runs the algorithm on data with key
	 * @returns resulting message
	 */
	std::string run(const char *data, const char *key) const {{
		algo_context ctx;
		ctx.d = data;
		ctx.k = key;
		{self.gen_code(ici, eci)}
	}}
}};
/**
 * @brief oputputs algorithm as a python function
 */
std::ostream &operator<<(std::ostream &o, const algo{self.fadd} &a) {{
	o << {py_code};
	return o;
}}
"""
	def gen_code(self, int_const_idents, expr_const_idents):
		"""
		returns string with generated c++ code which performs the algorithm
		"""
		res = ""
		ident = 2
		i = 0
		a = self.data["[algorithm]"]
		def vars_res(s):
			s = re.sub(r"\bindex\b", "ctx.index", s)
			s = re.sub(r"\bkeyindex\b", "ctx.keyindex", s)
			s = re.sub(r"\.\.data\b", "ctx.d.size()", s)
			s = re.sub(r"\.\.key\b", "ctx.k.size()", s)
			s = re.sub(r"\bdata\b", "ctx.d", s)
			s = re.sub(r"\bkey\b", "ctx.k", s)
			return s
		def macro_res(s):
			macros = {\
				"nonempty":"!$0.empty()",\
				"rot0":"$0 %= $1; if ($0 < 0) { $0 += $1; }",\
				"appendchar":"$0.push_back($1)",\
				"removechar":"$0.erase($1,1)",\
				"decl_filled_str":"std::string $0($2, $1)",\
				}
			name = s[1:].split("{", 1)[0]
			s = s[2+len(name):]
			args = [""]
			skip = 0
			for c in s[:-1]:
				if c == "{":
					skip += 1
				elif c == "}":
					skip -= 1
				if c == "," and skip == 0:
					args.append("")
				else:
					args[-1] += c
			r = macros[name]
			for i, x in enumerate(args):
				r = r.replace("$" + str(i), x)
			return r
		def macro():
			nonlocal i
			nonlocal a
			if a[i+1][0] != "{":
				self.syntax_err(a[i+1], "expected { in macro")
			s = a[i][0] + a[i+1][0]
			i += 2
			# parse arguments
			skip = 0
			while skip >= 0:
				if a[i][0] == "{":
					skip += 1
				elif a[i][0] == "}":
					skip -= 1
				s += a[i][0]
				i += 1
			return macro_res(s)
		while i < len(a):
			t = a[i]
			if t[0].startswith("#?"):
				res += expr_const_idents[int(t[0][2:])] + "->get(ctx)"
			elif t[0].startswith("#"):
				res += int_const_idents[int(t[0][1:])]
			elif t[0].startswith("$"):
				res += vars_res(macro())
				i -= 1
			elif t[0] == "str":
				res += "std::string"
			elif t[0] == "elif":
				res += "else if"
			elif t[0] == "{":
				ident += 1
				res += "{\n" + "\t" * ident
			elif t[0] == "}":
				ident -= 1
				if res.endswith("\t"):
					res = res[:-1]
				res += "}\n" + "\t" * ident
			elif t[0] == ";":
				res += ";\n" + "\t" * ident
			else:
				res += vars_res(t[0])
			if res[-1].isalnum():
				res += " "
			i += 1
		return res
	def gen_pycode(self, int_const_idents, expr_const_idents):
		"""
		returns string with generated python code for output
		"""
		res = ""
		ident = 0
		i = 0
		a = self.data["[algorithm]"]
		def vars_res(s):
			s = re.sub(r"\bindex\b", "index", s)
			s = re.sub(r"\bkeyindex\b", "keyindex", s)
			s = re.sub(r"\.\.data\b", "len(data)", s)
			s = re.sub(r"\.\.key\b", "len(key)", s)
			s = re.sub(r"\bdata\b", "data", s)
			s = re.sub(r"\bkey\b", "key", s)
			return s
		def macro_res(s):
			macros = {\
				"nonempty":"$0",\
				"rot0":"$0 %= $1; if $0 < 0: $0 += $1",\
				"appendchar":"$0 += $1",\
				"removechar":"del $0[$1]",\
				"decl_filled_str":"$0 = $2*$1",\
				}
			name = s[1:].split("{", 1)[0]
			s = s[2+len(name):]
			args = [""]
			skip = 0
			for c in s[:-1]:
				if c == "{":
					skip += 1
				elif c == "}":
					skip -= 1
				if c == "," and skip == 0:
					args.append("")
				else:
					args[-1] += c
			r = macros[name]
			for i, x in enumerate(args):
				r = r.replace("$" + str(i), x)
			return r
		def macro():
			nonlocal i
			nonlocal a
			if a[i+1][0] != "{":
				self.syntax_err(a[i+1], "expected { in macro")
			s = a[i][0] + a[i+1][0]
			i += 2
			# parse arguments
			skip = 0
			while skip >= 0:
				if a[i][0] == "{":
					skip += 1
				elif a[i][0] == "}":
					skip -= 1
				s += a[i][0]
				i += 1
			return macro_res(s)
		while i < len(a):
			t = a[i]
			if t[0].startswith("#?"):
				res += "\" << *a." + expr_const_idents[int(t[0][2:])] + " << \""
			elif t[0].startswith("#"):
				res += "\" << a." + int_const_idents[int(t[0][1:])] + " << \""
			elif t[0].startswith("$"):
				res += vars_res(macro())
				i -= 1
			elif t[0] == "str":
				i += 1
				res += t[0] + " = \"\""
			elif t[0] == "int":
				i += 1
				res += t[0] + " = 0"
			elif t[0] == "{":
				ident += 1
				res += ":\n" + "\t" * ident
			elif t[0] == "}":
				ident -= 1
			elif t[0] == ";":
				res += "\n" + "\t" * ident
			else:
				res += vars_res(t[0])
			if res[-1].isalnum():
				res += " "
			i += 1
		return res

with open("./algos.abalgo", "r", encoding="utf-8") as f:
	asrc = f.read()

tokens = lex.lex(asrc)
tokens = [x for x in tokens if not x[0].startswith("//") and not x[0].isspace()]
algosrcs = ""
while tokens:
	a = algo(tokens)
	algosrcs += a.gen_algo() + a.make_generator()
res = """
#ifndef __ALGOS_HPP__
#define __ALGOS_HPP__
#include "algo_bruteforce_expr.hpp"
""" + algosrcs + "\n#endif"

with open("./algo_bruteforce_algos.hpp", "w") as f:
	f.write(res)
