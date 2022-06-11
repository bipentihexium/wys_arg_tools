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

import os
from wys_lib import data3, key3, data4, humanscantsolvethis_decrypt, humanscantsolvethis_encrypt

data = data4#data3

print_all = False

pass_mod = lambda x: x
reverse_mod = lambda x: x[::-1]

test_methods = [humanscantsolvethis_decrypt, humanscantsolvethis_encrypt]
autotest_keys = []#key3]
test_modifications = [pass_mod, reverse_mod]

def is_message(msg):
	return print_all or "passed; " in msg # "DATA(" in msg

def test_key(key):
	found = False
	for method in test_methods:
		for key_mod in test_modifications:
			for data_mod in test_modifications:
				unmodified_res = method(data_mod(data), key_mod(key))
				for result_mod in test_modifications:
					res = result_mod(unmodified_res)
					if is_message(res):
						print("--------------------- MESSAGE ------------------------")
						print(res)
						print("key: " + key_mod(key))
						print("data: " + data_mod(data))
						print("method: " + method.__name__)
						found = True
	if not found:
		print("Didn't find anything with key " + key)

for key in autotest_keys:
	test_key(key)
while True:
	key = input("another key (auto-capitalized)>")
	os.system("cls | clear")
	print("another key (auto-capitalized)> " + key)
	key = key.upper()
	if key == "EXIT":
		break
	elif key == "PRINTALL":
		print_all = not print_all
		continue
	test_key(key)

