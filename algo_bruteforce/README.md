# Algo bruteforce

Probably the most interesting program here. It is written in C++ so you will need a C++ compiler to use it, but there is also a Python script so you'll need Python 3.6+ (I used f-strings).

## Notes

To customize parameters, check `algo_bruteforce_cfg.hpp`, to customize algorithm, check `algos.abl` and "Custom algorithms" below.

### What does this do?

It generates random algorithms (from the one you put `algos.abl` file and specified in `algo_bruteforce_cfg.hpp`). Then tests them if they are a valid message (by default, message is valid when it contains `DATA(`, but you can change it in `algo_bruteforce_cfg.hpp`.) When it is, it prints the algorithm. And appends it to the `ab_out.txt` file.

If you can think of any way of improving this or making better algorithm generator, make a pull request or DM me on discord (I'm `__noop__#0077`).

### Custom algorithms

The `algos.abl` file has structure like this:

```
algo <name>:
	__generator_leaf_var_chance__: <n> # the chance of expression leaf being a variable is 1/n
	__generator_leaf_num_range__:
		<min>
		<max> # the range of integer constants which are expression leafs between min (inclusive) and max (exclusive)
	__generator_expr_operations_max__: <n> # every random expression will have random number from [0, n) operations applied to it
	__generator_expr_leaf_unop_chance__: <n> # chance (1/n) for added leaf to have unary operator applied to it
	__generator_expr_leaf_binop_chance__: <n> # chance (1/n) for added leaf to have binary operator with new random leaf applied to it
	algo:
		<source_code>
algo <name2>:
	...
```

The code is the part you can have most fun with :). Its python-like language. There are only 3 types: `int`. `char` and `str`. There are operators for basic math with `int`s, `+` and `-` is also defined for `char` and `int`. `str` can be subscripted with int, which gives you char, and it is possible to delete character at index using `del strvar[index]`.

There are some predefined macros:

macro | effect
--- | ---
`len(s : str)` | *returns* length of `s`
`rot0(n : int, limit : int)` | folds `n` into [0, `limit`) - it puts k*`limit`+`n` into `n` so that `n` is greater than 0 and smaller than `limit`
`str(n : int)` (string constructor) | *returns* new string with reserved space of length `n` (for optimization)
`str(n : int, c : char)` (string constructor) | *returns* new string filled with `n` `c`s
`str.empty()` | *returns* True/1 if `str` is empty, else False/0
`str.append(c : char)` | appends `c` to `str`
`str.append(s : str)` | appends `s` to `str`

You can use `rand{n}` to make a random constant (from interval [0, n)) which is generated when generating the algorithm. Then there is `randexpr{base}` which is a random expression based off `base`, or completly random when used `randexpr{..}`.

```python
index = rand{2} * (len(data) - 1)
keyindex = rand{2} * (len(key) - 1)
keyindex %= len(key)
result = str(len(data))
while not data.empty():
	index = randexpr{index}
	rot0(index, len(data))
	keyindex = randexpr{keyindex}
	rot0(keyindex, len(key))
	result.append(data[index])
	del data[index]
return result
```

There is also `for` cycle:

```python
for i in min..max(..step): # ..step is optional
```

## Running this

### Linux (maybe Mac with g++)

On Linux you can use g++:

```shell
python3 algo_cpp_gen.py
g++ algo_bruteforce.cpp -o algo -O3 -std=c++11 -lpthread
./algo
```

I made a bash script which also builds and runs tests - `algo_bruteforce_run.sh`. You can add `-a` to skip generating c++ code from `algos.abl`, `-d` to compile with `-g` instead of `-O3`, `-i` to build and run without tests and `-g` to compile with `-g` instead of `-O3` but also lauch the program with `gdb`.

### Windows

on Windows it is a bit more complicated. You need to use Visual Studio or MinGWs, or something I don't know about :P :

#### MinGW

 With MinGW it's basically same as on Linux, just replace `-lpthread` with `-lwinpthread`, note that you need the right MinGW version (posix thread model).
 If you have also GitBash you should be able to use the `algo_bruteforce_run.sh` if you replace `-lpthread` with `-lwinpthread` (on line 7). This is not tested though. Feel free to make a pull request with version written in batch!

#### Visual studio

I don't know how to use VS for C++, sorry :/. Just run the python script `algo_cpp_gen.py` and then somehow compilt `algo_bruteforce.cpp` with C++ standard `C++11` and `O3`. It uses C++ `<thread>` which might need to link some library, but I don't know...
