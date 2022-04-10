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

class Lex:
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
					res.append((s, line, col, r))
					text = text[len(s):]
					if '\n' in s:
						line += s.count('\n')
						col = len(s)-s.rfind('\n')
					else:
						col += len(s)
					break
			else:
				print(f"Syntax error at {line}:{col} - unknown token")
				sys.exit(-1)
		return res
# lexer rules (regex patterns)
ident_pattern = r"[a-zA-Z_][a-zA-Z_0-9]*"
num_pattern, hexnum_pattern = r"\-?[0-9]+", r"\-?0x[0-9a-fA-F]+"
char_pattern, str_pattern = r"'([^\\']|\\.)'", r'"([^\\"]|\\.)+"'
lexspecial = [r"#.*"]
lexkeywords = [r"if\b", r"else\b", r"elif\b", r"while\b", r"for\b", r"algo\b",\
	r"break\b", r"continue\b", r"return\b", r"in\b", r"and\b", r"or\b", r"not\b", r"rand\b", r"randexpr\b", r"del\b"]
lexkeyvars = [r"index", r"keyindex", r"data", r"key"]
lexother_preop = [num_pattern, hexnum_pattern]
lexoperators = [r"<", r">", r"<=", r">=", r"==",\
	r"=", r"\+=", r"\-=", r"\*=", r"/=", r"%=",\
	r"\(", r"\)", r"\[", r"\]", r"\{", r"\}",\
	r":", r",", r"\.\.", r"\.",\
	r"\+", r"\-", r"\*", r"/", r"%", r","]
lexother = ["\n", "\t", "    ", ident_pattern, r"\s+", char_pattern, str_pattern]
lexrules = [*lexspecial, *lexkeywords, *lexkeyvars, *lexother_preop, *lexoperators, *lexother]

class Algo:
	def __init__(self, ident):
		self.ident = ident
		self.configs = {}
		self.statements = []
		self.iconstants = []
		self.econstants = []
class Parser:
	"""
	just a "simple" recursive descent parser
	"""
	def __init__(self):
		self.tokens = None
		self.indent = 0
		self.algo = None
	def parse(self, tokens):
		self.tokens = tokens
		self.indent = 0
		algo_list = []
		while self.tokens:
			a = self.parse_algo()
			if a:
				algo_list.append(a)
		return algo_list
	def parse_algo(self):
		while self.tokens[0] == '\n':
			del self.tokens[0]
			if not self.tokens:
				return None
		self.expect(self.tokens[0], "algo")
		self.expect_pattern(self.tokens[1], ident_pattern, "identifier")
		self.expect(self.tokens[2], ":")
		a = Algo(self.tokens[1][0])
		del self.tokens[:3]
		self.algo = a
		self.parse_algo_blocks(a)
		return a
	def parse_algo_blocks(self, a):
		self.indent += 1
		while True:
			self.expect(self.tokens[0], "\n", "\\n")
			del self.tokens[0]
			indent = 0
			while self.tokens and self.tokens[0][0] == "\t":
				del self.tokens[0]
				indent += 1
			if indent > self.indent:
				self.syntax_error(self.tokens[0], "unexpected indentation")
			elif indent < self.indent:
				break
			if self.tokens[0][0] == "algo":
				self.expect(self.tokens[1], ":")
				del self.tokens[:2]
				self.indent += 1
				self.parse_statement_block(a.statements)
				self.indent -= 1
			elif self.tokens[0][3] == ident_pattern:
				self.expect(self.tokens[1], ":")
				cfg = self.tokens[0][0]
				del self.tokens[:2]
				self.indent += 1
				a.configs[cfg] = self.parse_configuration()
				self.indent -= 1
			else:
				self.syntax_error(self.tokens[0], "unexpected token")
		self.indent -= 1
	def parse_configuration(self):
		if self.tokens[0][0] == "\n":
			values = []
			while True:
				self.expect(self.tokens[0], "\n", "\\n")
				tokenscpy = self.tokens[1:]
				indent = 0
				while tokenscpy[0][0] == "\t":
					del tokenscpy[0]
					indent += 1
				if indent > self.indent:
					self.syntax_error(tokenscpy[0], "unexpected indentation")
				elif indent < self.indent:
					break
				self.tokens = tokenscpy
				values.append(self.tokens[0][0])
				del self.tokens[0]
			return values
		else:
			v = self.tokens[0][0]
			del self.tokens[0]
			return [v]
	def parse_statement_block(self, block):
		if self.tokens[0][0] == "\n":
			while True:
				self.expect(self.tokens[0], "\n", "\\n")
				tokenscpy = self.tokens[1:]
				indent = 0
				while tokenscpy and tokenscpy[0][0] == "\t":
					del tokenscpy[0]
					indent += 1
				if indent > self.indent:
					self.syntax_error(tokenscpy[0], "unexpected indentation")
				elif indent < self.indent:
					break
				self.tokens = tokenscpy
				block.append(self.parse_statement())
		else:
			block.append(self.parse_statement())
	def parse_statement(self):
		statement = {}
		if self.tokens[0][0] == "if":
			statement["stype"] = "if"
			statement["stoken"] = self.tokens[0]
			del self.tokens[0]
			self.parse_if(statement)
		elif self.tokens[0][0] == "while":
			statement["stype"] = "while"
			statement["stoken"] = self.tokens[0]
			del self.tokens[0]
			self.parse_while(statement)
		elif self.tokens[0][0] == "for":
			statement["stype"] = "for"
			statement["stoken"] = self.tokens[0]
			del self.tokens[0]
			self.parse_for(statement)
		elif self.tokens[0][0] == "break":
			statement["stype"] = "break"
			statement["stoken"] = self.tokens[0]
			del self.tokens[0]
		elif self.tokens[0][0] == "continue":
			statement["stype"] = "continue"
			statement["stoken"] = self.tokens[0]
			del self.tokens[0]
		elif self.tokens[0][0] == "return":
			statement["stype"] = "return"
			statement["stoken"] = self.tokens[0]
			del self.tokens[0]
			statement["sexpr"] = self.parse_expr()
		elif self.tokens[0][0] == "del":
			statement["stype"] = "del"
			statement["stoken"] = self.tokens[0]
			if self.tokens[1][0] not in lexkeyvars:
				self.expect_pattern(self.tokens[1], ident_pattern, "expected identifier in del")
			statement["sident"] = self.tokens[1][0]
			del self.tokens[:2]
			if self.tokens and self.tokens[0][0] == "[":
				del self.tokens[0]
				statement["stype"] = "del[]"
				statement["sindex"] = self.parse_expr()
				self.expect(self.tokens[0], "]")
				del self.tokens[0]
		else:
			statement["stype"] = "expr"
			statement["stoken"] = self.tokens[0]
			statement["sexpr"] = self.parse_expr()
		return type('', (object,), statement)() # anonymous object from statement dict
	def parse_if(self, statement):
		statement["scondition"] = self.parse_expr()
		statement["sblock"] = []
		self.expect(self.tokens[0], ":")
		del self.tokens[0]
		self.indent += 1
		self.parse_statement_block(statement["sblock"])
		self.indent -= 1
		if self.tokens[0][0] == "\n":
			tokenscpy = self.tokens[1:]
			indent = 0
			while tokenscpy[0][0] == "\t":
				del tokenscpy[0]
				indent += 1
			if indent == self.indent:
				if tokenscpy[0][0] == "elif":
					self.tokens = tokenscpy
					elif_statement = {}
					elif_statement["stype"] = "elif"
					elif_statement["stoken"] = self.tokens[0]
					del self.tokens[0]
					self.parse_if(elif_statement)
					statement["selse"] = type('', (object,), elif_statement)()
				elif tokenscpy[0][0] == "else":
					self.tokens = tokenscpy
					else_statement = {}
					else_statement["stype"] = "else"
					else_statement["stoken"] = self.tokens[0]
					else_statement["sblock"] = []
					self.expect(self.tokens[1], ":")
					del self.tokens[:2]
					self.indent += 1
					self.parse_statement_block(else_statement["sblock"])
					self.indent -= 1
					statement["selse"] = type('', (object,), else_statement)()
	def parse_while(self, statement):
		statement["scondition"] = self.parse_expr()
		statement["sblock"] = []
		self.expect(self.tokens[0], ":")
		del self.tokens[0]
		self.indent += 1
		self.parse_statement_block(statement["sblock"])
		self.indent -= 1
		if self.tokens[0] == "\n":
			tokenscpy = self.tokens[1:]
			indent = 0
			while tokenscpy[0][0] == "\t":
				del tokenscpy[0]
				indent += 1
			if indent == self.indent and tokenscpy[0][0] == "else":
				self.tokens = tokenscpy
				else_statement = {}
				else_statement["stype"] = "else"
				else_statement["stoken"] = self.tokens[0]
				del self.tokens[0]
				else_statement["sblock"] = []
				self.expect(self.tokens[0], ":")
				del self.tokens[0]
				self.indent += 1
				self.parse_statement_block(statement["sblock"])
				self.indent -= 1
				statement["selse"] = type('', (object,), else_statement)()
	def parse_for(self, statement):
		if self.tokens[0][0] not in ["index", "keyindex"]:
			self.expect_pattern(self.tokens[0], ident_pattern, "ident")
		self.expect(self.tokens[1], "in")
		statement["svar"] = self.tokens[0]
		statement["sintoken"] = self.tokens[1]
		del self.tokens[:2]
		statement["sstart"] = self.parse_expr()
		self.expect(self.tokens[0], "..")
		statement["srangetoken"] = self.tokens[0]
		del self.tokens[0]
		statement["send"] = self.parse_expr()
		if self.tokens[0][0] == "..":
			statement["srangesteptoken"] = self.tokens[0]
			del self.tokens[0]
			statement["sstep"] = self.parse_expr()
		else:
			statement["srangesteptoken"] = None
			statement["sstep"] = type('', (object,), {"etype":"int", "evalue":1, "etoken":self.tokens[0]})()
		statement["sblock"] = []
		self.expect(self.tokens[0], ":")
		del self.tokens[0]
		self.indent += 1
		self.parse_statement_block(statement["sblock"])
		self.indent -= 1
		if self.tokens[0] == "\n":
			tokenscpy = self.tokens[1:]
			indent = 0
			while tokenscpy[0][0] == "\t":
				del tokenscpy[0]
				indent += 1
			if indent == self.indent and tokenscpy[0][0] == "else":
				self.tokens = tokenscpy
				else_statement = {}
				else_statement["stype"] = "else"
				else_statement["stoken"] = self.tokens[0]
				del self.tokens[0]
				else_statement["sblock"] = []
				self.expect(self.tokens[0], ":")
				del self.tokens[0]
				self.indent += 1
				self.parse_statement_block(statement["sblock"])
				self.indent -= 1
				statement["selse"] = type('', (object,), else_statement)()
	def parse_expr_left_general(self, operators, next, *args):
		op = next(*args)
		wrap = False
		while self.tokens[0][0] in operators:
			if wrap and self.tokens[0][0] == op["etype"]:
				op["etokens"].append(self.tokens[0])
				del self.tokens[0]
				op["eoperands"].append(next(*args))
			else:
				if wrap:
					op = type('', (object,), op)()
				op = {"etype":self.tokens[0][0], "etokens":[self.tokens[0]], "eoperands":[op]}
				del self.tokens[0]
				op["eoperands"].append(next(*args))
			wrap = True
		return type('', (object,), op)() if wrap else op
	def parse_expr(self):
		return self.parse_expr_left_general([","], self.parse_ternary_assign)
	def parse_ternary_assign(self):
		left = self.parse_or()
		op = {"etype":"", "etokens":[], "eoperands":[left]}
		if self.tokens[0][0] == 'if':
			op["etype"] = "if-else"
			op["etokens"].append(self.tokens[0])
			del self.tokens[0]
			op["eoperands"].append(self.parse_expr()) # condition
			self.expect(self.tokens[0], "else")
			op["etokens"].append(self.tokens[0])
			del self.tokens[0]
			op["eoperands"].append(self.parse_ternary_assign())
		elif self.tokens[0][0] == "=":
			op["etype"] = "="
			op["etokens"].append(self.tokens[0])
			del self.tokens[0]
			op["eoperands"].append(self.parse_ternary_assign())
		elif self.tokens[0][0].endswith("="):
			op["etype"] = self.tokens[0][0]
			op["etokens"].append(self.tokens[0])
			del self.tokens[0]
			op["eoperands"].append(self.parse_ternary_assign())
		return type('', (object,), op)() if op["etokens"] else left
	def parse_or(self):
		return self.parse_expr_left_general(\
			["or"], self.parse_expr_left_general,\
			["and"], self.parse_expr_left_general,\
			["==", "!="], self.parse_expr_left_general,\
			[">", "<", ">=", "<="], self.parse_expr_left_general,\
			["+", "-"], self.parse_expr_left_general,\
			["*", "/", "%"], self.parse_unary_pre)
	def parse_unary_pre(self):
		if self.tokens[0][0] in ["+", "-", "not"]:
			op = {"etype":"unary"+self.tokens[0][0], "etoken":self.tokens[0]}
			del self.tokens[0]
			op["eoperand"] = self.parse_unary_pre()
			return type('', (object,), op)()
		return self.parse_unary_post()
	def parse_unary_post(self):
		op = self.parse_dot()
		while self.tokens[0][0] in ["(", "["]:
			if self.tokens[0][0] == "(":
				op = {"etype":"call", "etoken":self.tokens[0], "etokens":[], "emacro":op, "eargs":[]}
				if self.tokens[1][0] == ")":
					del self.tokens[:2]
				else:
					while True:
						del self.tokens[0]
						op["eargs"].append(self.parse_ternary_assign())
						if self.tokens[0][0] != ",":
							break
						op["etokens"].append(self.tokens[0])
					self.expect(self.tokens[0], ")")
					del self.tokens[0]
				op = type('', (object,), op)()
			else: # '['
				op = {"etype":"[]", "etoken":self.tokens[0], "earray":op}
				del self.tokens[0]
				op["earg"] = self.parse_expr()
				self.expect(self.tokens[0], "]")
				del self.tokens[0]
				op = type('', (object,), op)()
		return op
	def parse_dot(self):
		op = self.parse_leaf()
		while self.tokens[0][0] == ".":
			op = {"etype":".", "etoken":self.tokens[0], "eparent":op}
			self.expect_pattern(self.tokens[1], ident_pattern, "ident")
			op["echild"] = self.tokens[1][0]
			del self.tokens[:2]
			op = type('', (object,), op)()
		return op
	def parse_leaf(self):
		if self.tokens[0][0] == "(":
			del self.tokens[0]
			e = self.parse_expr()
			self.expect(self.tokens[0], ")")
			del self.tokens[0]
			return e
		elif self.tokens[0][3] == num_pattern:
			leaf = type('', (object,), {"etype":"int", "etoken":self.tokens[0], "evalue":int(self.tokens[0][0])})()
			del self.tokens[0]
			return leaf
		elif self.tokens[0][3] == hexnum_pattern:
			if self.tokens[0][0][0] == '-':
				leaf = type('', (object,), {"etype":"int", "etoken":self.tokens[0], "evalue":-int(self.tokens[0][0][3:], 16)})()
			else:
				leaf = type('', (object,), {"etype":"int", "etoken":self.tokens[0], "evalue":int(self.tokens[0][0][2:], 16)})()
			del self.tokens[0]
			return leaf
		elif self.tokens[0][3] == char_pattern:
			leaf = type('', (object,), {"etype":"char", "etoken":self.tokens[0], "evalue":self.tokens[0][0][1:-1]})()
			del self.tokens[0]
			return leaf
		elif self.tokens[0][3] == str_pattern:
			leaf = type('', (object,), {"etype":"str", "etoken":self.tokens[0], "evalue":self.tokens[0][0][1:-1]})()
			del self.tokens[0]
			return leaf
		elif self.tokens[0][0] == "rand":
			leaf = type('', (object,), {"etype":"rand_int", "etoken":self.tokens[0], "erand_id":len(self.algo.iconstants)})()
			self.expect(self.tokens[1], "{")
			self.expect_pattern(self.tokens[2], num_pattern, "number")
			self.expect(self.tokens[3], "}")
			self.algo.iconstants.append(int(self.tokens[2][0]))
			del self.tokens[:4]
			return leaf
		elif self.tokens[0][0] == "randexpr":
			leaf = type('', (object,), {"etype":"rand_expr", "etoken":self.tokens[0], "erand_id":len(self.algo.econstants)})()
			self.expect(self.tokens[1], "{")
			self.expect(self.tokens[3], "}")
			if self.tokens[2][0] in ["..", "index", "keyindex", "key", "data"]:
				self.algo.econstants.append(self.tokens[2][0])
			else:
				self.syntax_error(self.tokens[2], "expected key variable (index, keyindex, data (which means data[index]), key (which means key[keyindex])) or '..' in randexpr")
			del self.tokens[:4]
			return leaf
		elif self.tokens[0][0] in lexkeyvars:
			leaf = type('', (object,), {"etype":"identifier", "etoken":self.tokens[0], "eidentifier":self.tokens[0][0]})()
			del self.tokens[0]
			return leaf
		elif self.tokens[0][3] == ident_pattern:
			leaf = type('', (object,), {"etype":"identifier", "etoken":self.tokens[0], "eidentifier":self.tokens[0][0]})()
			del self.tokens[0]
			return leaf
		self.syntax_error(self.tokens[0], "expected expression")
	def expect(self, token, expected, expected_name=None):
		if token[0] != expected:
			self.syntax_error(token, "expected '" + (expected if expected_name is None else expected_name) + "'")
	def expect_pattern(self, token, expected_pattern, expected_name):
		if token[3] != expected_pattern:
			self.syntax_error(token, "expected " + expected_name)
	def syntax_error(self, token, msg):
		print(f"Syntax error at '{token[0]}' - {token[1]}:{token[2]} - {msg}")
		sys.exit(0)
