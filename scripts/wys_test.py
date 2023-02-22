import os
from ..wys_lib import data5, humanscantsolvethis_decrypt, humanscantsolvethis_encrypt

data = data5

print_all = False

pass_mod = lambda x: x
reverse_mod = lambda x: x[::-1]

test_methods = [humanscantsolvethis_decrypt, humanscantsolvethis_encrypt]
autotest_keys = []
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

