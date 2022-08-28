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

from algo_cpp_gen_codegen import CodeGen
from algo_cpp_gen_parser import Lex, lexrules, Parser

lex = Lex(lexrules)
par = Parser()
codegen = CodeGen()

with open("./algos.abl", "r", encoding="utf-8") as f:
	asrc = f.read()

tokens = lex.lex(asrc)
tokens = ["\t" if x == "    " else x for x in tokens]
islineempty = True
i = 0
while i < len(tokens):
	t = tokens[i][0]
	if t == "\n":
		if islineempty:
			while i > -1 and tokens[i][0] != "\n":
				del tokens[i]
				i -= 1
			if tokens[i][0] == "\n":
				del tokens[i]
				i -= 1
		islineempty = True
	elif t == "\t":
		pass
	elif t.isspace() or t.startswith("#"):
		del tokens[i]
		i -= 1
	else:
		islineempty = False
	i += 1
algos = par.parse(tokens)
algosrcs = ""
for a in algos:
	algosrcs += codegen.gen_code(a)
res = codegen.gen_file(algosrcs)

with open("./algo_bruteforce_algos.hpp", "w") as f:
	f.write(res)
