# Algorithm Bruteforcer v2

- [Algorithm Bruteforcer v2](#algorithm-bruteforcer-v2)
	- [Why I made this?](#why-i-made-this)
	- [How to use?](#how-to-use)
	- [Example output](#example-output)
	- [How to read the output code](#how-to-read-the-output-code)
		- [Internal machine](#internal-machine)
		- [The code in the example](#the-code-in-the-example)
	- [How this works?](#how-this-works)

This is second version of the algorithm bruteforcer :)

## Why I made this?

The first version had just random expressions, which is useful, but not when you are completely stuck... So there are random instructions this time.

## How to use?

As with the first bruteforcer - use `cmake`/`build_linux_gcc.sh`/`build_win_mingw.bat` and configure it with changing `cfg.hpp`. Now it has even CTest tests :). It builds the executable you can use afterwards :).
Type `exit` (and enter) to stop the search.

## Example output

the keys in `cfg.hpp` are:
```cpp
constexpr const char *keys[] = {
	"ELLIE",
}
```
output:
```
[Welcome to algortihm bruteforcer v2]
threads: 3
algorithm key count: 1
register count: 5
instructions before termination: 5000
data: AtniotoMK;hHLt hOT(NSCCiMs  aEeMifpCesul)t: su|'yhlRtsW ;tFpb7t actt lbA  L|c  Ar:SlihA7Eof kh rK;LSPrfdswdrBrHekblUytasxKsnc 7uAROslOyELt SSUC;G Amu snOaACtrutyreebN;TPx thNIteelset;seis;  drs  nDdEpdltueUc And o c dyS7tdTlwFcA TItiePoA:(slpr(ltefKaIeeR  EdN;AvtetEE psottTCTEaCoAa IyYfsnouotsbUti sAkSetL;iui hNpnedped nIhcetx ;ttAeN lsytTnhKtD EeiaexRELityHU'Uux )e UMVr NVhtYiHc  rj Blu;Oe rN e pdsYNHIDo6NeS: D OOAlnn aC TC f So RPoGMsntsan EI LtE anoOiEeP    wDThxdt;CLp)eoEHo arS;wrwgiABeRzwAsue evirjOotiimo;L L( NEwros|oIpNiWeisoin;AiOAit2EQnyUlzsR TWRn rfCAeBEO ks PTW in|sngscthezHt eD)
[Good luck!]
	{searched: 1.0m; time: 24.728s; average search speed: 2.4265m/min}
	{searched: 2.0m; time: 49.801s; average search speed: 2.4097m/min}
	{searched: 3.0m; time: 74.567s; average search speed: 2.4140m/min}
	{searched: 4.0m; time: 99.940s; average search speed: 2.4015m/min}
	{searched: 5.0m; time: 129.847s; average search speed: 2.3105m/min}
	{searched: 6.0m; time: 154.513s; average search speed: 2.3300m/min}
	{searched: 7.0m; time: 180.447s; average search speed: 2.3276m/min}
------------------------ FOUND ---------------------------
inverted: 0	code:
???
	REG_SWITCH REG{2}
	DIV KEY{0}
	REG_SWITCH REG{3}
	TEST_GT KEY{0}
	MOD KEYLEN{0}
	REG_SWITCH REG{4}
	MOV VAL{8}
	WHILE_NOT
		ADD DATALEN{0}
		IF_NOT
			MUL KEYLEN{0}
			TEST_GT KEY{0}
	WHILE
		MOD VAL{5}
		TEST_GT REG{0}
		MUL VAL{-9}
	REG_SWITCH REG{1}
	ADD VAL{4}
	IF
		MOV DATALEN{0}
		MOD REG{0}
	SUB REG{3}
	REG_SWITCH REG{0}
	ADD KEY{0}
	MOD DATALEN{0}
	PUSH_RES
	message:
		that's correct; third test passed; next up: SGIPCESRON|WOREP|HKCEC|7|SEPURECAP; DATA(IvTuitn tat  eHenoEi pgvi IATf nAOiM pLl ssyGnelnu l(Eeo seIthHNc;YARsL oeeoEilnBst( elth dyl
	keys:
		ELLIE 
	permutation:
		5 15 28 41 47 53 63 76 89 95 101 111 124 137 143 149 159 172 185 191 197 207 220 233 239 245 255 268 281 287 293 303 316 329 335 341 351 364 377 383 389 399 412 425 431 437 447 460 473 479 485 495 508 521 527 533 543 556 569 575 581 591 8 22 29 35 46 61 75 82 88 100 115 129 135 142 154 168 182 189 196 208 222 236 243 250 261 275 290 297 304 314 328 344 350 357 368 382 397 404 410 421 436 451 457 464 475 490 504 511 517 529 544 558 564 571 583 0 16 23 31 43 59 74 83 91 104 119 134 144 151 163 178 195 203 211 223 238 256 263 270 282 299 315 322 330 342 359 374 381 390 402 418 434 442 449 462 478 494 501 509 522 538 553 561 568 582 1 18 26 36 50 67 85 94 103 116 132 
	{searched: 8.0m; time: 204.879s; average search speed: 2.3429m/min}
	{searched: 9.0m; time: 229.605s; average search speed: 2.3520m/min}
	{searched: 10.0m; time: 254.092s; average search speed: 2.3614m/min}
	{searched: 11.0m; time: 279.669s; average search speed: 2.3600m/min}
	{searched: 12.0m; time: 305.138s; average search speed: 2.3597m/min}
```

## How to read the output code

As you can see in the example above, the output can get very messy. The message is correct, but it ends in the middle. In order to understand what it does, you need to know how the internal machine works.

### Internal machine

The machine has 5 registers (this can be changed in `cfg.hpp`), you can see that at the beginning of the example - `register count: 5`. The registers are simply `int`s. They are initialized to `0` and I'll refer to them as `R0`, `R1`.... One of them is active (`R0` at the start; I'll refer to it as `Ra`), which means all operations are performed on it. There is `REG_SWITCH REG{n}` instruction, which makes the `Rn` active. Then there are instructions to do basic math:

```
REG_SWITCH REG{1}       - switches to R1
ADD REG{2}              - adds value of R2 to R1
SUB VAL{4}              - substracts 4 from R1 (VAL{n} means just constant n)
MUL DATALEN{0}          - the 0 doesn't mean anything here; it multiplies value in R1 by length of data
DIV VAL{4}              - divides value of R1 by 4; does nothing on division by 0
MOD REG{0}              - sets R1 to R1 mod R0; does nothing on division by 0
```

There's also a `PUSH_RES` instruction. It adds `data[R0]` to the output, then removes `data[R0]`. Because the value in `R0` is going to be outside of bounds, the actual value is `r0 === n (mod datalen)` where `0 <= n < datalen` :) (`(r0%datalen+datalen)%datalen`).

The L2 algorithm used a key. Here's key support too. There can be any amount of keys, but it takes exponentionaly more time to try more keys - `key_count^algo_key_count` where `key_count` is count of keys in the `keys` variable in `cfg.hpp`. Every key is indexed in the same way as data, but with different register - `KEY{0}` (`K0`) is indexed by `R1`, `K1` by `R2` and so on (`Kn` by `R(n+1)`). The algorithm can use `KEYLEN{n}` too - it's just length of `Kn`.

The machine contains one more value - `flag`, which is just a flag for conditions. It can be set with `TEST_...` instructions:

```
TEST_GT VAL{0}       - set flag to true if active register is greater than 0 (to false otherwise)
TEST_EQ REG{0}       - flag = Ra == R0
TEST_LT KEY{0}       - flaf = Ra < key[0][R1]
```

The `flag` can be used with `IF`, `WHILE` instructions, which also have reversed versions - `IF_NOT` and `WHILE_NOT`:

```
SWITCH_REG{0}
TEST_GT VAL{4}
IF
	SUB VAL{8}
SWITCH_REG{1}
WHILE
	MUL KEY{0}
	TEST_EQ REG{4}
```
would translate to this pseudocode:
```python
flag = R0 > 4
if flag:
	R0 -= 8
while flag:
	R1 *= key[0][R1]
	flag = R1 > R4
```

When the code finishes, it's started again from the beginning.

### The code in the example

So let's take a look at what the code does. It's messy, so let's start by optimizing it:
```
REG_SWITCH REG{2}
DIV KEY{0}
REG_SWITCH REG{3}
TEST_GT KEY{0}
MOD KEYLEN{0}
REG_SWITCH REG{4}
MOV VAL{8}
WHILE_NOT
	ADD DATALEN{0}
	IF_NOT
		MUL KEYLEN{0}
		TEST_GT KEY{0}
WHILE
	MOD VAL{5}
	TEST_GT REG{0}
	MUL VAL{-9}
REG_SWITCH REG{1}
ADD VAL{4}
IF
	MOV DATALEN{0}
	MOD REG{0}
SUB REG{3}
REG_SWITCH REG{0}
ADD KEY{0}
MOD DATALEN{0}
PUSH_RES
```
In this section:
```
MOV VAL{8}
WHILE_NOT
	ADD DATALEN{0}
	IF_NOT
		MUL KEYLEN{0}
		TEST_GT KEY{0}
```
The `flag` is always `false` because it's inside `while not flag:` loop and there's no `TEST` between the `WHILE_NOT` and `IF_NOT`, so the `IF_NOT` can be removed (as if it was `if true:`):
```
MOV VAL{8}
WHILE_NOT
	ADD DATALEN{0}
	MUL KEYLEN{0}
	TEST_GT KEY{0}
```
`R2` is never used, so every part that modifies it can be removed.
```
	REG_SWITCH REG{2}
	DIV KEY{0}
	REG_SWITCH REG{3}
	...
to
	REG_SWITCH REG{3}
	...
```

There is no test between the `WHILE` and `IF`, so the `IF` will never run (in order to exit the `WHILE`, the `flag` must be `false`) and can be removed.

Then `R3` is never modified, so It's always `0` - the `SUB REG{3}` can be removed. This gives us this:

```
REG_SWITCH REG{3}
TEST_GT KEY{0}
MOD KEYLEN{0}
REG_SWITCH REG{4}
MOV VAL{8}
WHILE_NOT
	ADD DATALEN{0}
	MUL KEYLEN{0}
	TEST_GT KEY{0}
WHILE
	MOD VAL{5}
	TEST_GT REG{0}
	MUL VAL{-9}
REG_SWITCH REG{1}
ADD VAL{4}
REG_SWITCH REG{0}
ADD KEY{0}
MOD DATALEN{0}
PUSH_RES
```

Now the biggest optimization here is that only register affecting the `PUSH_RES` is `R0`, which is only affected by `R1` (in the `ADD KEY{0}`). The stuff that happens before changing `R1` - in other registers - is not needed, as long as it finishes running, which it does at leas for some time, as we can see in the output. So the optimized code looks like this.

```
REG_SWITCH REG{1}
ADD VAL{4}
REG_SWITCH REG{0}
ADD KEY{0}
MOD DATALEN{0}
PUSH_RES
```
which could translate into this python code:
```python
r0, r1 = 0, 0
while True:
	r1 += 4 # traversing the key in backwards
	r0 += key[r1 % keylen]
	out += data[r0 % datalen]
	data = data[:r0 % datalen] + data[r0 % datalen + 1:]
```

## How this works?

Most of internal working can be found in the [How to read the output code](#how-to-read-the-output-code) section, but there is a bit more stuff going on. The permutation every algorithm generated is inverted to check even the inverse versions of the algorithms. It checks for a valid message by checking if it contains `; DATA(`, but this can be changed in `cfg.hpp` here:

```cpp
constexpr const char *message_identifier = "; DATA(";
```

The code gets terminated after specified amount of instructions, so it doesn't get stuck forever. The amount can be found in `cfg.hpp` here:

```cpp
constexpr int max_instrs = 5000;
```

The code generation currently generates these hardcoded instructions, but it adds `0-3` random instructions in between.

```
REG_SWITCH REG{2}
REG_SWITCH REG{3}
REG_SWITCH REG{4}
REG_SWITCH REG{1}
REG_SWITCH REG{0}
PUSH_RES
```

When any block gets generated (`IF`,`WHILE`...), it has random amount of instructions depending on the depth it's at:

```cpp
static const int instr_count_mins[] = { 3, 1, 1, 1, 1 };
static const int instr_count_maxs[] = { 9, 4, 3, 2, 1 };
```
