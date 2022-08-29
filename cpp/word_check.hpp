#ifndef __WORD_CHECK_HPP__
#define __WORD_CHECK_HPP__

/* Copyright (c) 2022 bipentihexium

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
OTHER DEALINGS IN THE SOFTWARE. */

#include <array>
#include <deque>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

class trie_node {
public:
	inline trie_node() : is_terminal(false), children{nullptr} { }

	inline static trie_node load_file(const std::string &file_name, unsigned int word_min_limit) {
		std::ifstream f(file_name);
		if (f.good()) {
			trie_node trie;
			std::string buff;
			while (std::getline(f, buff)) {
				if (buff.size() > word_min_limit && buff[0] != '#')
					trie.add(buff);
			}
			return trie;
		} else {
			std::cerr << "unable to open " << file_name << std::endl;
			return trie_node();
		}
	}

	inline void add(std::string::const_iterator it, std::string::const_iterator end) {
		if (it == end) {
			is_terminal = true;
			return;
		} else if (children[*it - 'a'] == nullptr) {
			children[*it - 'a'] = std::unique_ptr<trie_node>(new trie_node());
		}
		children[*it - 'a']->add(++it, end);
	}
	inline void add(const std::string &str) { add(str.begin(), str.end()); }
	inline bool has(std::string::const_iterator it, std::string::const_iterator end) const {
		if (it == end) {
			return is_terminal;
		} else if (children[*it - 'a'] == nullptr) {
			return false;
		} else {
			return children[*it - 'a']->has(++it, end);
		}
	}
	inline bool has(const std::string &str) const { return has(str.begin(), str.end()); }
	inline bool has(char c) const { return children[c - 'a'] != nullptr; }
	inline bool terminal() const { return is_terminal; }
	inline const trie_node *at(char c) const { return children[c - 'a'].get(); }
	inline const trie_node *operator[](char c) const { return at(c); }
private:
	bool is_terminal;
	std::array<std::unique_ptr<trie_node>, 26> children;
};

struct word_check_data {
	std::string key;
	const trie_node *at_node;
	unsigned int off;

	inline word_check_data(const std::string &key, const trie_node *at_node, unsigned int off) : key(key), at_node(at_node), off(off) { }
};
template<typename F>
inline void check_start(std::string &data, std::string &keybuff, const trie_node *root, const trie_node *node, unsigned int skip,
	unsigned int off, unsigned int limit, F callback) {
	keybuff.push_back(static_cast<char>(skip + 64));
	if (limit == 0) {
		callback(keybuff);
	} else {
		char removed_char = data[off];
		data.erase(data.begin() + off);
		for (unsigned int skip = 1; skip <= 26; skip++) {
			unsigned int index = (off + skip) % data.size();
			char c = data[index];
			if (c >= 'a' && c <= 'z') {
				if (node != nullptr && node->has(c)) {
					check_start(data, keybuff, root, node->at(c), skip, index, limit - 1, callback);
				}
			} else if (c == ' ') {
				if (node == nullptr || node->terminal()) {
					check_start(data, keybuff, root, root, skip, index, limit - 1, callback);
				}
			} else if (c == ';') {
				if (node != nullptr && node->terminal()) {
					check_start(data, keybuff, root, nullptr, skip, index, limit - 1, callback);
				}
			}
		}
		data.insert(data.begin() + off, removed_char);
	}
	keybuff.pop_back();
}
template<typename F>
inline void check_start(const std::string &data, const trie_node &trie, unsigned int limit, F callback) {
	std::string datacpy(data);
	std::string keybuff;
	keybuff.reserve(limit);
	for (unsigned int skip = 1; skip <= 26; skip++) {
		unsigned int index = skip % datacpy.size();
		char c = data[index];
		if (c >= 'a' && c <= 'z') {
			if (trie.has(c)) {
				check_start(datacpy, keybuff, &trie, trie[c], skip, index, limit - 1, callback);
			}
		}
	}
}

#endif
