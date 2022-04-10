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

import re
import sys

file_start = """#ifndef __ALGOS_HPP__
#define __ALGOS_HPP__

#include "algo_bruteforce_expr.hpp"\n"""
file_end = "#endif\n"
generator_template = """
#define R(n) (std::uniform_int_distribution<int>(0, (n)-1)(random_engine))
template<typename RANDOM_T>
expr *randLeaf_%s(RANDOM_T &random_engine) {
	if (R(%d)) {
		return new expr(R(%d)+%d);
	} else {
		constexpr variable vars[] = { variable::INDEX, variable::KEYINDEX, variable::KEY };
		constexpr int varc = 3;
		return new expr(vars[R(varc)]);
	}
}
template<typename RANDOM_T>
expr *randExpr_%s(RANDOM_T &random_engine, expr *base) {
	int count = R(%d);
	constexpr operation binops[] = { operation::ADD, operation::MULT, operation::ADD }; // add is there for second time to increase the chance of selecting it
	constexpr operation unops[] = { operation::REV };
	constexpr int binoplen = 3;
	constexpr int unoplen = 1;
	constexpr int sumlen = binoplen + unoplen;
	for (int i = 0; i < count; ++i) {
		int op = R(sumlen);
		if (op < binoplen) {
			expr *leaf = randLeaf_%s(random_engine);
			if (!R(%d)) {
				leaf = new expr(leaf, unops[R(unoplen)]);
			}
			if (!R(%d)) {
				leaf = new expr(leaf, randLeaf_%s(random_engine), binops[R(binoplen)]);
			}
			base = new expr(base, leaf, binops[op]);
		} else {
			base = new expr(base, unops[op-binoplen]);
		}
	}
	return base;
}

template<typename RANDOM_T>
algo_%s randAlgo_%s(RANDOM_T &random_engine) {
	return algo_%s(%s);
}
#undef R
"""
algo_class_template = """
class algo_%s {
public:
	%s;
	%s;

	algo_%s(%s) : %s {
#ifdef EXPR_OPTI
		%s
#endif
	}
	~algo_%s() {
		%s
	}
	/**
	 * @brief runs the algorithm on data with key
	 * @returns resulting message
	 */
	std::string run(const char *data, const char *key) const {
		auto reserving_string_constr = [](std::size_t reserve_size){
			std::string str;
			str.reserve(reserve_size);
			return str;
		};

		algo_context ctx;
		ctx.d = data;
		ctx.k = key;
		%s
	}
};
/**
 * @brief oputputs algorithm as a python function
 */
std::ostream &operator<<(std::ostream &o, const algo_%s &a) {
	o << %s;
	return o;
}
"""
def generator_from_template(algoname, leaf_varchance, leaf_num_min, leaf_num_max, expr_binop_count_max, expr_unop_chance, expr_binop_chance, rand_params):
	rand_iparams = ", ".join(["R("+str(i)+")" for i in rand_params[0]])
	rand_eparams = ", ".join(["randExpr_"+algoname+"(random_engine, "+e+")" for e in rand_params[1]])
	return generator_template % (algoname, leaf_varchance, leaf_num_max-leaf_num_min, leaf_num_min,\
		algoname, expr_binop_count_max, algoname, expr_unop_chance, expr_binop_chance, algoname,\
		algoname, algoname, algoname, ", ".join([x for x in [rand_iparams, rand_eparams] if x]))
def algo_class_from_template(algoname, algo_code, algo_out, algo_constants):
	inames = ["_ic"+str(i) for i in range(algo_constants[0])]
	enames = ["_ec"+str(i) for i in range(algo_constants[1])]
	decls_ic = "int " + ", ".join(inames) if inames else "" # int _ic0, _ic1, _ic2...
	decls_ec = "expr *" + ", *".join(enames) if enames else "" # expr *_ec0, *_ec1, *_ec2...
	ctor_iparams = ", ".join(["int " + n for n in inames]) # int _ic0, int _ic1, int _ic2...
	ctor_eparams = ", ".join(["expr *" + n for n in enames]) # expr *_ec0, expr *_ec1, expr *_ec2...
	ctor_params = ", ".join([x for x in [ctor_iparams, ctor_eparams] if x]) # int _ic0, int _ic1..., expr *_ec0, expr *_ec1...
	ctor_initializers = ", ".join([x+"("+x+")" for x in [*inames, *enames]]) # _ic0(_ic0), _ic1(_ic1)..., _ec0(_ec0), _ec1(_ec1)...
	expr_optimize = "\n\t\t".join([n + "->optimize();" for n in enames])
	expr_destruct = "\n\t\t".join(["delete " + n + ";" for n in enames])
	algo_code = algo_code.replace("\n", "\n\t\t").strip()
	algo_out = "\n".join(["\t\t\""+line+"\\n\"" for line in algo_out.split('\n')]).strip()
	return algo_class_template % (algoname, decls_ic, decls_ec,\
		algoname, ctor_params, ctor_initializers, expr_optimize,\
		algoname, expr_destruct,\
		algo_code,
		algoname, algo_out)

class CodeGenerator:
	def __init__(self):
		self.vars = {"index":type('', (object,), {"ident":"index", "type":"i"})(),\
			"keyindex":type('', (object,), {"ident":"keyindex", "type":"i"})(),\
			"data":type('', (object,), {"ident":"data", "type":"s"})(),\
			"key":type('', (object,), {"ident":"key", "type":"s"})}
		self.types = ["int", "chr", "str"]
		self.macros = {"extern":{}, "int":{}, "chr":{}, "str":{}}
		self.macros["extern"]["unary+ i i"] = "($0)"
		self.macros["extern"]["unary- i i"] = "(-$0)"
		self.macros["extern"]["unarynot i i"] = None
		self.macros["extern"]["* ii i"] = "($0*$1)"
		self.macros["extern"]["/ ii i"] = "($0/$1)"
		self.macros["extern"]["% ii i"] = "($0%$1)"
		self.macros["extern"]["+ ii i"] = "($0+$1)"
		self.macros["extern"]["+ ci c"] = "($0+$1)"
		self.macros["extern"]["+ ss s"] = "($0+$1)"
		self.macros["extern"]["- ii i"] = "($0-$1)"
		self.macros["extern"]["- ci c"] = "($0-$1)"
		self.macros["extern"]["> ii i"] = "($0>$1)"
		self.macros["extern"]["< ii i"] = "($0<$1)"
		self.macros["extern"]["> cc i"] = "($0>$1)"
		self.macros["extern"]["< cc i"] = "($0<$1)"
		self.macros["extern"][">= ii i"] = "($0>=$1)"
		self.macros["extern"]["<= ii i"] = "($0<=$1)"
		self.macros["extern"][">= cc i"] = "($0>=$1)"
		self.macros["extern"]["<= cc i"] = "($0<=$1)"
		self.macros["extern"]["== ii i"] = "($0==$1)"
		self.macros["extern"]["!= ii i"] = "($0!=$1)"
		self.macros["extern"]["== cc i"] = "($0==$1)"
		self.macros["extern"]["!= cc i"] = "($0!=$1)"
		self.macros["extern"]["== ss i"] = "($0==$1)"
		self.macros["extern"]["!= ss i"] = "($0!=$1)"
		self.macros["extern"]["and ii i"] = "($0&&$1)"
		self.macros["extern"]["or ii i"] = "($0||$1)"
		self.macros["extern"][", ii i"] = "($0,$1)"
		self.macros["extern"][", cc c"] = "($0,$1)"
		self.macros["extern"][", ss s"] = "($0,$1)"
		self.macros["extern"]["len s i"] = None
		self.macros["extern"]["rot0 ii v"] = None
		self.macros["str"]["ctor i s"] = None
		self.macros["str"]["ctor ic s"] = None
		self.macros["str"]["[] i c"] = "($0[$1])"
		self.macros["str"]["del[] i v"] = None
		self.macros["str"]["empty  i"] = None
		self.macros["str"]["append c v"] = None
		self.macros["str"]["append s v"] = None
		self.lit_formats = {"int":"${evalue}","char":"'${evalue}'","str":"\"${evalue}\"",\
			"rand_int":None,"rand_expr":None}
		self.ternary_format = None
		self.assign_formats = {"=":"$0=$1","*=":"$0*=$1","/=":"$0/=$1","%=":"$0%=$1","+=":"$0+=$1","-=":"$0-=$1"}
		self.statement_formats = {"if":[None, None, None], "elif":[None, None], "else":[None, None],\
			"while":[None, None, None], "while-else":[None, None], "for":[None, None, None], "for-else":[None, None],\
			"break":None, "continue":None, "return":None,"expr":None}
		self.decl_formats = {"i":None, "c":None, "s":None}
		self.lit2type = {"int":"i", "char":"c", "str":"s", "rand_int":"i", "rand_expr":"i", "identifier":None}
		self.type2fulltype = {"i":"int", "c":"char", "s":"str"}
		self.whileloops = 0
		self.forloops = 0
		self.loopid = ""
	def perform_macro(self, macrosrc, *args):
		for i, a in enumerate(args):
			macrosrc = macrosrc.replace("$"+str(i), a)
		return macrosrc
	def findmacro(self, macros, name, types):
		x = name + " " + types + " "
		for m in macros:
			if m.startswith(x):
				return m
	def get_expr_type(self, expr):
		try: # I'm to lazy to do this the smart way, sorry...
			if expr.etype == "identifier":
				i = expr.eidentifier
				if i in self.vars:
					return self.vars[i].type
			elif expr.etype in self.lit2type:
				return self.lit2type[expr.etype]
			elif expr.etype == "call":
				argtypes = ""
				for a in expr.eargs:
					argtypes += self.get_expr_type(a)
				if expr.emacro.etype == "identifier":
					if expr.emacro.eidentifier in self.types:
						return {"int":"i","char":"c","str":"s"}[expr.emacro.eidentifier]
					return self.findmacro(self.macros["extern"], expr.emacro.eidentifier, argtypes)[-1]
				elif expr.emacro.etype == ".":
					pt = self.get_expr_type(expr.emacro.eparent)
					return self.findmacro(self.macros[self.type2fulltype[pt]], expr.emacro.echild, argtypes)[-1]
			elif expr.etype == "[]":
				arr = expr.earray.eidentifier
				if arr in self.vars:
					arrt = self.vars[arr].type
				argtype = self.get_expr_type(expr.earg)
				return self.findmacro(self.macros[self.type2fulltype[arrt]], "[]", argtype)[-1]
			elif expr.etype in ["unary+", "unary-", "unarynot"]:
				return self.findmacro(self.macros["extern"], expr.etype, self.get_expr_type(expr.eoperand))[-1]
			elif expr.etype in ["*", "/", "%", "+", "-", ">", "<", ">=", "<=", "==", "!=", "or", "and", ","]:
				t = self.get_expr_type(expr.eoperands[0])
				for t2 in expr.eoperands[1:]:
					t2 = self.get_expr_type(t2)
					t = self.findmacro(self.macros["extern"], expr.etype, t+t2)[-1]
				return t
			elif expr.etype in ["=", "*=", "/=", "%=", "+=", "-="]:
				return self.get_expr_type(expr.eoperands[-1])
			elif expr.etype == "if-else":
				return self.get_expr_type(expr.eoperands[-1])
		except Exception as e:
			import traceback
			print(traceback.format_exc())
			print(e)
			return None
		return None
	def gen_expr(self, expr):
		if expr.etype == "identifier":
			i = expr.eidentifier
			if i in self.vars:
				return self.vars[i].ident
			self.err(expr.etoken, i+" is not defined")
		elif expr.etype in self.lit_formats:
			f = self.lit_formats[expr.etype]
			while (m := re.search(r"\$\{([a-zA-Z0-9_]+)\}", f)):
				f = f[:m.span()[0]] + str(getattr(expr, m.group(1))) + f[m.span()[1]:]
			return f
		elif expr.etype == ".":
			self.err(expr.etoken, "'.' operator must be in macro call")
		elif expr.etype == "call":
			argtypes = ""
			args = []
			for a in expr.eargs:
				t = self.get_expr_type(a)
				if not t: self.err(a.etoken, "unable to resolve type of argument")
				argtypes += t
				args.append(self.gen_expr(a))
			if expr.emacro.etype == "identifier":
				if expr.emacro.eidentifier in self.types:
					am = self.macros[expr.emacro.eidentifier]
					macro = self.findmacro(am, "ctor", argtypes)
				else:
					am = self.macros["extern"]
					macro = self.findmacro(am, expr.emacro.eidentifier, argtypes)
				if not macro:
					self.err(expr.etoken, "call of undefined macro")
				return self.perform_macro(am[macro], *args)
			elif expr.emacro.etype == ".":
				parent = expr.emacro.eparent
				pt = self.get_expr_type(parent)
				macro = self.findmacro(self.macros[self.type2fulltype[pt]], expr.emacro.echild, argtypes)
				if not macro:
					self.err(expr.etoken, "call of undefined macro")
				parent = self.gen_expr(parent)
				return self.perform_macro(self.macros[self.type2fulltype[pt]][macro], parent, *args)
		elif expr.etype == "[]":
			if expr.earray.etype != "identifier":
				self.err(expr.earray.etoken, "first operand of [] operator must be identifier")
			arr = expr.earray.eidentifier
			if arr not in self.vars:
				self.err(expr.earray.etoken, "undefined identifier")
			arr = self.vars[arr]
			arrt = arr.type
			argtype = self.get_expr_type(expr.earg)
			if not argtype:
				self.err(expr.earg, "unable to resolve type")
			macro = self.findmacro(self.macros[self.type2fulltype[arrt]], "[]", argtype)
			if not macro:
				self.err(expr.etoken, "operator [] is undefined for types " + arrt + " and " + self.type2fulltype[argtype])
			return self.perform_macro(self.macros[self.type2fulltype[arrt]][macro], arr.ident, self.gen_expr(expr.earg))
		elif expr.etype in ["unary+", "unary-", "unarynot"]:
			optype = self.get_expr_type(expr.eoperand)
			if not optype:
				self.err(expr.eoperand.etoken, "unable to resolve type")
			macro = self.findmacro(self.macros["extern"], expr.etype, optype)
			if not macro:
				self.err(expr.etoken, "operator " + expr.etype + " is undefined for type " + optype)
			return self.perform_macro(self.macros["extern"][macro], self.gen_expr(expr.eoperand))
		elif expr.etype in ["*", "/", "%", "+", "-", ">", "<", ">=", "<=", "==", "!=", "or", "and", ","]:
			t = self.get_expr_type(expr.eoperands[0])
			res = self.gen_expr(expr.eoperands[0])
			if not t:
				self.err(expr.eoperands[0].etoken, "unable to resolve type")
			for i, op in enumerate(expr.eoperands[1:]):
				t2 = self.get_expr_type(op)
				o2 = self.gen_expr(op)
				if not t2:
					self.err(op.etoken, "unable to resolve type")
				macro = self.findmacro(self.macros["extern"], expr.etype, t+t2)
				if not macro:
					self.err(expr.etokens[i], "operator " + expr.etype + " is undefined for types " + t + " and " + t2)
				res = self.perform_macro(self.macros["extern"][macro], res, o2)
			return res
		elif expr.etype in ["=", "*=", "/=", "%=", "+=", "-="]:
			decl = False
			o2 = self.gen_expr(expr.eoperands[1])
			t2 = self.get_expr_type(expr.eoperands[1])
			if not t2:
				self.err(expr.eoperands[1].etoken, "unable to resolve type")
			if expr.eoperands[0].etype == "identifier":
				name = expr.eoperands[0].eidentifier
				if name not in self.vars:
					self.vars[name] = type('', (object,), {"ident":name, "type":t2})()
					decl = True
			o = self.gen_expr(expr.eoperands[0])
			t = self.get_expr_type(expr.eoperands[0])
			if not t:
				self.err(expr.eoperands[0].etoken, "unable to resolve type")
			if decl:
				res = self.decl_formats[t2].replace("$0", o).replace("$1", o2)
			else:
				res = self.assign_formats[expr.etype].replace("$0", o).replace("$1", o2)
			return res
		elif expr.etype == "if-else":
			o3 = self.gen_expr(expr.eoperands[2])
			t3 = self.get_expr_type(expr.eoperands[2])
			if not t3: self.err(expr.eoperands[2].etoken, "unable to resolve type")
			o2 = self.gen_expr(expr.eoperands[1])
			t2 = self.get_expr_type(expr.eoperands[1])
			if not t2: self.err(expr.eoperands[1].etoken, "unable to resolve type")
			o1 = self.gen_expr(expr.eoperands[0])
			t1 = self.get_expr_type(expr.eoperands[0])
			if not t1: self.err(expr.eoperands[0].etoken, "unable to resolve type")
			macro = self.findmacro(self.macros["extern"], expr.etype, t1+t2+t3)
			if not macro:
				self.err(expr.etoken, "operator " + expr.etype + " is undefined for types " + t1 + ", " + t2 + " and " + t3)
			return self.perform_macro(self.macros["extern"][macro], o1, o2, o3)
	def gen_statement(self, statement):
		if statement.stype == "if":
			formats = self.statement_formats["if"]
			res = formats[0].replace("$0", self.gen_expr(statement.scondition))
			for s in statement.sblock:
				s = self.gen_statement(s)
				res += "".join(["\n\t" + x for x in s.split("\n")])
			res += formats[1]
			while hasattr(statement, "selse"):
				statement = statement.selse
				if statement.stype == "elif":
					res += self.statement_formats["elif"][0].replace("$0", self.gen_expr(statement.scondition))
					for s in statement.sblock:
						s = self.gen_statement(s)
						res += "".join(["\n\t" + x for x in s.split("\n")])
					res += self.statement_formats["elif"][1]
				else: # else
					res += self.statement_formats["else"][0]
					for s in statement.sblock:
						s = self.gen_statement(s)
						res += "".join(["\n\t" + x for x in s.split("\n")])
					res += self.statement_formats["else"][1]
			res += formats[2]
			return res
		elif statement.stype == "while":
			wid = "while_" + str(self.whileloops)
			self.whileloops += 1
			formats = self.statement_formats["while"]
			res = formats[0].replace("$0", self.gen_expr(statement.scondition))
			for s in statement.sblock:
				self.loopid = wid
				s = self.gen_statement(s)
				res += "".join(["\n\t" + x for x in s.split("\n")])
			res += formats[1]
			if hasattr(statement, "selse"):
				res += self.statement_formats["while-else"][0]
				for s in statement.selse.sblock:
					s = self.gen_statement(s)
					res += "".join(["\n\t" + x for x in s.split("\n")])
				res += self.statement_formats["while-else"][1]
			res += formats[2].replace("$0", wid)
			return res
		elif statement.stype == "for":
			fid = "for_" + str(self.forloops)
			self.forloops += 1
			if statement.svar[0] not in self.vars:
				self.vars[statement.svar[0]] = type('', (object,), {"ident":statement.svar[0], "type":"i"})()
				formats = self.statement_formats["for-undef"]
			else:
				formats = self.statement_formats["for-def"]
			res = formats[0].replace("$0", self.vars[statement.svar[0]].ident).\
				replace("$1", self.gen_expr(statement.sstart)).\
				replace("$2", self.gen_expr(statement.send)).\
				replace("$3", self.gen_expr(statement.sstep))
			for s in statement.sblock:
				self.loopid = fid
				s = self.gen_statement(s)
				res += "".join(["\n\t" + x for x in s.split("\n")])
			res += formats[1]
			if hasattr(statement, "selse"):
				res += self.statement_formats["for-else"][0]
				for s in statement.selse.sblock:
					s = self.gen_statement(s)
					res += "".join(["\n\t" + x for x in s.split("\n")])
				res += self.statement_formats["for-else"][1]
			res += formats[2].replace("$0", fid)
			if statement.svar[0] not in ["index", "keyindex"]:
				del self.vars[statement.svar[0]]
			return res
		elif statement.stype == "continue":
			return self.statement_formats[statement.stype]
		elif statement.stype == "break":
			return self.statement_formats[statement.stype].replace("$0", self.loopid)
		elif statement.stype in ["return", "expr"]:
			return self.statement_formats[statement.stype].replace("$0", self.gen_expr(statement.sexpr))
		elif statement.stype == "del":
			if statement.sident not in self.vars:
				self.err(statement.stoken, "undeclared identifier")
			del self.vars[statement.sident]
			return ""
		elif statement.stype == "del[]":
			if statement.sident not in self.vars:
				self.err(statement.stoken, "undeclared identifier")
			o = self.vars[statement.sident].ident
			t = self.vars[statement.sident].type
			o2 = self.gen_expr(statement.sindex)
			t2 = self.get_expr_type(statement.sindex)
			macro = self.findmacro(self.macros[self.type2fulltype[t]], "del[]", t2)
			if not macro:
				self.err(statement.stoken, "operator del[] is undefined for types " + self.type2fulltype[t] + " and " + t2)
			return self.statement_formats["expr"].replace("$0", self.perform_macro(self.macros[self.type2fulltype[t]][macro], o, o2))
	def gen_algo(self, algo):
		res = ""
		for s in algo.statements:
			res += self.gen_statement(s) + "\n"
		return res.strip()
	def err(self, token, msg):
		print(f"codegen error at {token[0]} - {token[1]}:{token[2]} - {msg}")
		sys.exit(-1)

class CppCodeGenerator(CodeGenerator):
	def __init__(self):
		super().__init__()
		self.vars = {"index":type('', (object,), {"ident":"ctx.index", "type":"i"})(),\
			"keyindex":type('', (object,), {"ident":"ctx.keyindex", "type":"i"})(),\
			"data":type('', (object,), {"ident":"ctx.d", "type":"s"})(),\
			"key":type('', (object,), {"ident":"ctx.k", "type":"s"})}
		self.macros["extern"]["unarynot i i"] = "(!$0)"
		self.macros["extern"]["len s i"] = "($0.size())"
		self.macros["extern"]["rot0 ii v"] = "$0 %= $1; if ($0 < 0) $0 += $1"
		self.macros["str"]["ctor i s"] = "reserving_string_constr($0)"
		self.macros["str"]["ctor ic s"] = "std::string($0, $1)"
		self.macros["str"]["[] i c"] = "($0[$1])"
		self.macros["str"]["del[] i v"] = "$0.erase($1, 1)"
		self.macros["str"]["empty  i"] = "($0.empty())"
		self.macros["str"]["append c v"] = "$0.push_back($1)"
		self.macros["str"]["append s v"] = "$0.apprnd($1)"
		self.lit_formats = {"int":"${evalue}","char":"'${evalue}'","str":"\"${evalue}\"",\
			"rand_int":"_ic${erand_id}","rand_expr":"_ec${erand_id}->get(ctx)"}
		self.ternary_format = "($1 ? $0 : $2)"
		self.statement_formats = {"if":["if ($0) {", "\n}", ""], "elif":["else if ($0) {", "\n}"], "else":["else {", "\n}"],\
			"while":["while ($0) {", "\n}", "\nlab_$0:;"], "while-else":["\n", ""],\
			"for-undef":["for (int $0 = $1; $0 != $2; $0 += $3) {", "\n}", "\nlab_$0:;"],\
				"for-def":["for ($0 = $1; $0 != $2; $0 += $3) {", "\n}", "\nlab_$0:;"], "for-else":["\n", ""],\
			"break":"goto lab_$0;", "continue":"continue;", "return":"return $0;","expr":"$0;"}
		self.decl_formats = {"i":"int $0($1)", "c":"char $0($1)", "s":"std::string $0($1)"}
class PyCodeGenerator(CodeGenerator):
	def __init__(self):
		super().__init__()
		self.macros["extern"]["unary+ i i"] = "($0)"
		self.macros["extern"]["unary- i i"] = "(-$0)"
		self.macros["extern"]["unarynot i i"] = "(not $0)"
		self.macros["extern"]["/ ii i"] = "($0//$1)"
		self.macros["extern"]["and ii i"] = "($0 and $1)"
		self.macros["extern"]["or ii i"] = "($0 or $1)"
		self.macros["extern"][", ii i"] = "($0,$1)[-1]"
		self.macros["extern"][", cc c"] = "($0,$1)[-1]"
		self.macros["extern"][", ss s"] = "($0,$1)[-1]"
		self.macros["extern"]["len s i"] = "len($0)"
		self.macros["extern"]["rot0 ii v"] = "$0 %= $1; if $0 < 0: $0 += $1"
		self.macros["str"]["ctor i s"] = "\\\"\\\""
		self.macros["str"]["ctor ic s"] = "$1 * $0"
		self.macros["str"]["del[] i v"] = "$0 = $0[:$1] + $0[$1+1:]"
		self.macros["str"]["empty  i"] = "(not $0)"
		self.macros["str"]["append c v"] = "$0 += $1"
		self.macros["str"]["append s v"] = "$0 += $1"
		self.lit_formats = {"int":"${evalue}","char":"'${evalue}'","str":"\"${evalue}\"",\
			"rand_int":"\" << a._ic${erand_id} << \"","rand_expr":"\" << *a._ec${erand_id} << \""}
		self.ternary_format = "($0 if $1 else $2)"
		self.assign_formats["/="] = "$0//=$1"
		self.statement_formats = {"if":["if $0:", "", ""], "elif":["elif $0:", ""], "else":["else:", ""],\
			"while":["while $0:", "", ""], "while-else":["else:", ""],\
			"for-undef":["for $0 in range($1, $2):", "", ""], "for-def":["for $0 in range($1, $2):", "", ""], "for-else":["else:", ""],\
			"break":"break", "continue":"continue", "return":"return $0","expr":"$0"}
		self.decl_formats = {"i":"$0 = $1", "c":"$0 = $1", "s":"$0 = $1"}

class CodeGen:
	def gen_file(self, srcs):
		return file_start + srcs + file_end
	def gen_code(self, a):
		leaf_var_chance = int(a.configs["__generator_leaf_var_chance__"][0])
		leaf_num_min = int(a.configs["__generator_leaf_num_range__"][0])
		leaf_num_max = int(a.configs["__generator_leaf_num_range__"][1])
		expr_op_max = int(a.configs["__generator_expr_operations_max__"][0])
		expr_leaf_unop = int(a.configs["__generator_expr_leaf_unop_chance__"][0])
		expr_leaf_binop = int(a.configs["__generator_expr_leaf_binop_chance__"][0])
		erand_params = []
		for e in a.econstants:
			if e == "..":
				erand_params.append("randLeaf_"+a.ident+"(random_engine)")
			elif e == "index":
				erand_params.append("new expr(variable::INDEX)")
			elif e == "keyindex":
				erand_params.append("new expr(variable::KEYINDEX)")
			elif e == "data":
				erand_params.append("new expr(variable::DATA)")
			elif e == "key":
				erand_params.append("new expr(variable::KEY)")
		rand_params = [a.iconstants, erand_params]
		generator = generator_from_template(a.ident, leaf_var_chance, leaf_num_min, leaf_num_max,\
			expr_op_max, expr_leaf_unop, expr_leaf_binop, rand_params)
		algo_class = algo_class_from_template(a.ident, self.algo_code(a), self.algo_out(a), [len(a.iconstants), len(a.econstants)])
		return algo_class + generator
	def algo_code(self, a):
		cppgen = CppCodeGenerator()
		return cppgen.gen_algo(a)
	def algo_out(self, a):
		pygen = PyCodeGenerator()
		return pygen.gen_algo(a)
