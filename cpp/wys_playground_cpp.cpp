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

// command for g++:
// g++ -o playground wys_playground_cpp.cpp -Wall -Wextra -Wpedantic -O3 -march=native -std=c++11
// ./playground

#include <iostream>
#include "wys_lib_cpp.hpp"

int main() {
	std::cout << dontbother17_decrypt(data1) << std::endl;
	std::cout << dontbother17_encrypt(text2) << std::endl;
	std::cout << humanscantsolvethis_decrypt(data2) << std::endl;
	std::cout << humanscantsolvethis_encrypt(text3) << std::endl;
	std::cout << sheismymother_decrypt(data3) << std::endl;
	std::cout << sheismymother_encrypt(text4) << std::endl;
	std::cout << processingpowercheck_decrypt(data4) << std::endl;
	std::cout << processingpowercheck_encrypt(text5) << std::endl;
	return 0;
}
