/*
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
*/

#include <algorithm>
#include <array>
#include <initializer_list>
#include <iostream>
#include <vector>
#include "../cfg.hpp"
#undef KEY_COUNT
#define KEY_COUNT 1
#include "../code.hpp"
#include "../machine.hpp"

bool test_machine(machine &m, const code_block &block, const std::initializer_list<std::vector<int>> &keys,
	const std::vector<int> &expected, const std::string &msg) {
	m.reset(expected.size(), keys);
	m.run(block);
	bool fail = m.res.size() != expected.size() || !std::equal(m.res.begin(), m.res.end(), expected.begin());
	if (fail) {
		std::cout << "[TEST-MACHINE-1-KEY::FAIL]: " << msg << "\n\tcode:\n" << block.to_str() << "\n\tresult:\n\t\t";
		for (const auto &i : m.res) { std::cout << i << " "; }
		std::cout << "\n\texpected:\n\t\t";
		for (const auto &i : expected) { std::cout << i << " "; }
		std::cout << std::endl;
	}
	return fail;
}

int main() {
	bool fail = false;
	machine m;
	fail |= test_machine(m,
		code_block(code::codetype::LAST, {
			new code_block(code::codetype::WHILENOT, {
				new binary_op(code::codetype::ADD, binary_op::value_type::KEY, 0),
				new binary_op(code::codetype::MOD, binary_op::value_type::DATALEN, 0),
				new reg_op(code::codetype::SWITCH_REG, 1),
				new binary_op(code::codetype::ADD, binary_op::value_type::VALUE, 1),
				new reg_op(code::codetype::SWITCH_REG, 0),
				new code(code::codetype::PUSH_RES),
				new code(code::codetype::REMOVE_DATA),
			})
		}),
		{ { 1, 2, 3 } },
		{ 1, 4, 8, 10, 13, 2, 5, 9, 15, 3, 11, 6, 12, 7, 0, 14 },
		"~{ +B %. b +1 a < # } - humanscantsolvethissobetterstophere - simpler");
	fail |= test_machine(m,
		code_block(code::codetype::LAST, {
			new code_block(code::codetype::WHILENOT, {
				new binary_op(code::codetype::ADD, binary_op::value_type::KEY, 0),
				new binary_op(code::codetype::MOD, binary_op::value_type::DATALEN, 0),
				new reg_op(code::codetype::SWITCH_REG, 1),
				new binary_op(code::codetype::ADD, binary_op::value_type::VALUE, 1),
				new reg_op(code::codetype::SWITCH_REG, 0),
				new code(code::codetype::PUSH_RES),
				new code(code::codetype::REMOVE_DATA),
			})
		}),
		{ { 8, 21, 13, 1, 14, 19, 3, 1, 14, 20, 19, 15, 12, 22, 5, 20, 8, 9, 19, 19, 15, 2, 5, 20, 20, 5, 18, 19, 20, 15, 16, 8, 5, 18, 5 } },
		{ 8, 30, 44, 46, 61, 81, 85, 87, 102, 123, 143, 159, 172, 195, 201, 222, 231, 241, 261, 281, 297, 300,
		306, 327, 348, 354, 373, 393, 414, 430, 447, 456, 462, 481, 487, 496, 518, 532, 534, 549, 569, 573, 575, 590, 12,
		33, 51, 65, 91, 97, 119, 129, 139, 161, 182, 199, 203, 209, 232, 254, 260, 280, 303, 325, 342, 361, 370, 377, 397,
		403, 412, 436, 451, 453, 470, 492, 497, 499, 514, 538, 559, 578, 592, 17, 23, 48, 58, 70, 94, 116, 135, 138, 146,
		169, 192, 200, 223, 246, 270, 288, 309, 318, 324, 346, 353, 364, 389, 406, 408, 425, 448, 454, 457, 474, 501, 523,
		542, 556, 584, 591, 15, 26, 38, 64, 89, 109, 112, 120, 148, 173, 179, 205, 228, 253, 273, 293, 305, 313, 336, 343,
		356, 383, 400, 402, 422, 445, 452, 458, 476, 504, 527, 547, 563, 594, 0, 27, 39, 53, 78, 106, 128, 132, 141, 167,
		194, 206, 229, 255, 282, 302, 328, 338, 347, 374, 381, 392, 424, 441, 443, 469, 495, 503, 506, 524, 552, 579, 1,
		18, 52, 60, 90, 103, 117, 150, 176, 197, 204, 213, 240, 268, 276, 304, 333, 366, 388, 416, 428, 435, 468, 478,
		489, 522, 543, 545, 566, 596, 2, 4, 25, 59, 88, 114, 136, 170, 180, 215, 226, 242, 269, 298, 323, 330, 339, 372,
		407, 417, 446, 483, 516, 540, 567, 581, 588, 21, 32, 45, 80, 105, 108, 134, 165, 174, 177, 202, 237, 266, 291,
		315, 357, 365, 399, 418, 433, 472, 508, 531, 536, 548, 582, 19, 31, 67, 99, 142, 164, 196, 217, 225, 257, 265,
		283, 320, 349, 351, 379, 415, 423, 427, 460, 494, 530, 561, 585, 29, 41, 77, 96, 118, 155, 190, 227, 234, 244,
		279, 319, 332, 371, 410, 461, 488, 520, 539, 553, 587, 599, 14, 66, 92, 95, 127, 166, 178, 183, 214, 256, 294,
		329, 359, 404, 420, 467, 485, 509, 551, 593, 28, 36, 49, 93, 145, 154, 198, 247, 287, 321, 363, 384, 394, 440,
		459, 479, 526, 560, 564, 598, 50, 57, 63, 100, 151, 193, 238, 264, 314, 334, 385, 405, 434, 486, 533, 572, 577,
		597, 55, 111, 125, 171, 224, 275, 311, 360, 382, 396, 455, 473, 498, 554, 589, 3, 40, 98, 110, 115, 156, 216, 263,
		301, 341, 411, 431, 493, 515, 544, 9, 72, 124, 131, 149, 211, 267, 284, 337, 395, 471, 517, 570, 6, 20, 79, 104,
		140, 210, 249, 251, 295, 362, 375, 378, 437, 507, 568, 34, 74, 162, 185, 250, 278, 310, 386, 464, 513, 525, 546,
		24, 113, 137, 208, 274, 350, 419, 482, 512, 537, 13, 43, 75, 175, 230, 235, 289, 367, 380, 390, 450, 550, 37, 107,
		163, 259, 286, 369, 426, 466, 558, 56, 133, 152, 181, 262, 352, 391, 490, 580, 83, 186, 252, 299, 322, 438, 465,
		510, 16, 86, 121, 191, 296, 316, 326, 421, 535, 54, 157, 221, 355, 401, 528, 576, 42, 184, 290, 409, 432, 475,
		595, 147, 188, 307, 463, 5, 122, 239, 292, 340, 502, 541, 7, 187, 272, 285, 439, 583, 22, 47, 160, 344, 521, 73,
		212, 413, 480, 71, 158, 245, 477, 69, 236, 258, 331, 562, 218, 271, 505, 130, 398, 586, 220, 345, 442, 76, 153,
		308, 10, 233, 248, 511, 219, 317, 358, 571, 429, 144, 519, 126, 62, 189, 68, 335, 555, 491, 449, 312, 387, 565,
		82, 243, 500, 35, 376, 168, 484, 207, 101, 574, 444, 368, 84, 529, 11, 557, 277 },
		"~{ +B %. b +1 a < # } - humanscantsolvethissobetterstophere");
	return fail;
}
