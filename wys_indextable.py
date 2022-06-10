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

import sys
from wys_lib import data4

def printIndices(data, string, key=lambda n:n, genkeys=False):
	keys = [("", i) for i in range(200 if genkeys else 0)]
	indices = []
	for char in string:
		# find all occurences of char in data
		indices.append([i for i, c in enumerate(data) if c == char])
	for i in range(len(string)):
		ii = indices[i]
		for j, k in reversed(list(enumerate(keys))):
			opts = [x for x in ii if x - k[1] > 1 and x - k[1] < 28]
			keys.pop(j)
			for o in opts:
				nk = k[0]+chr(63+o-k[1])
				if len(nk) > 2 and nk[-3] == nk[-2] and nk[-2] == nk[-1]:
					continue
				#if len(nk) > 6:
				#	for vowel in "AEIOUY":
				#		if vowel in nk[-6:]:
				#			break
				#	else:
				#		continue
				keys.append((nk, o))
	# pad " " lists inside indices to make the 2d array rectangular
	ilen = max([len(x) for x in indices])
	for i in indices:
		while len(i) < ilen:
			i.append(" ")
	# transpose indices table
	indices = list(map(list, zip(*indices)))
	
	max_index_width = len(str(len(data)))
	# print table header
	print(" ".join([char.ljust(max_index_width) for char in string]))
	# print table
	for row in indices:
		for index in row:
			if type(index) == int:
				print(str(key(index)).ljust(max_index_width), end=" ")
			else:
				print(" " * max_index_width, end=" ")
		print()
	print(" ------------------------------------------------ ")
	for i in keys:
		print(i[0], end="; ")
def findWord(data, string, key):
	indices = []
	for char in string:
		indices.append([i for i, c in enumerate(data) if c == char])
	def dfs(indices, key, previ=0, path=[]):
		for i in indices:
			if key[0] in (abs(previ-indices), abs(previ-indices-len(data)), abs(previ-indices+len(data))):
				if len(key) < 2:
					print(path)
				else:
					dfs(indices, key, i, [*path, i])
	dfs(indices, key)

if __name__ == "__main__":
	data = data4
	datainput = input("Data (default lvl4 data)>")
	if datainput:
		data = datainput
	string = input("String you want to find >")
	genkeys = True
	if len(sys.argv) > 1:
		if sys.argv[1] == "usekey":
			key = input("Key function >")
			printIndices(data, string, eval(key), genkeys)
			sys.exit(0)
		elif sys.argv[1] == "index1": # indices start at 1 instead of 0
			printIndices(data, string, lambda n: n+1, genkeys)
			sys.exit(0)
	printIndices(data, string, lambda n:n, genkeys)
