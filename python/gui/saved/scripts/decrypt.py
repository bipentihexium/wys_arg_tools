global decrypt

def decrypt(data, key):
	res = ""
	index = 0
	keyindex = 0
	while data:
		index = (index + ord(key[keyindex]) - 64) % len(data)
		keyindex = (keyindex + 1) % len(key)
		res += data[index]
		data = data[:index] + data[index+1:]
	return res
print(decrypt(data, key))
