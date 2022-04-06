# Algo bruteforce

Probably the most interesting program here. It is written in C++ so you will need a C++ compiler to use it, but there is also a Python script so you'll need Python 3.6+ (I used f-strings).

## Notes

To customize parameters, check `algo_bruteforce_cfg.hpp`, to customize algorithm, check `algos.abalgo` and "Custom algorithms" below.

### What does this do?

It generates random algorithms (from the one you put `algos.abalgo` file and specified in `algo_bruteforce_cfg.hpp`). Then tests them if they are a valid message (by default, message is valid when it contains `DATA(`, but you can change it in `algo_bruteforce_cfg.hpp`.) When it is, it prints the algorithm.

If you can think of any way of improving this or making different algorithm generator, make a pull request or DM me on discord (I'm `__noop__#0077`).

### Custom algorithms

The `algos.abalgo` file has structure like this:

```
[<algo_name>]{
	[algorithm]{
		// code...; more on that later
	}
	[generator]{
		[leaf]{
			[var_chance]{<n>} // the chance of expression leaf being a variable is 1/n
			[num_range]{<min>, <max>} // the range of integer constants which are expression leafs between min (inclusive) and max (exclusive)
		}
		[expr]{
			[main_operations_max]{<n>} // every random expression will have random number from [0, n) operations applied to it
			[leaf_unop_chance]{<n>} // chance (1/n) for added leaf to have unary operator applied to it
			[leaf_binop_chance]{<n>} // chance (1/n) for added leaf to have binary operator with new random leaf applied to it
		}
	}
}
[<algo_name2>]{
	// same as in the first one
}
```

The code is the part you can have most fun with :). Its pretty reduced C-like language.

```c
[algorithm]{
	index = 0;
	keyindex = #{100}; // #{<n>} means random number from [0, n)
	keyindex %= ..key; // ..key means "length of key"
	str result; // declare string variable; only "int" and "str" variables supported; you can't assign during declaration :/
	while ($nonempty{data}) { // here is use of macro. more on that later :D
		index = #?{index}; // #?{<var>} means random expression based off/including <var>; you can use #? instead of var to make fully random expression
		$rot0{index, ..data};
		keyindex = #?{keyindex};
		$rot0{keyindex, ..data};
		$appendchar{result, data[index]};
		$removechar{data, index};
	}
	return result;
}
```

Note that there are no for loops.

Macros are there because it generates C++ code as well as Python code, which can be pretty different for some tasks. They have arguments in curly braces and separated by commas: `$macro{arg1, arg2}` There are currently these macros avaliable:

macro | what it does
--- | ---
\$nonempty{str} | checks if str is empty
\$rot0{n, limit} | puts k*limit+n to n so that 0 \<= n \< limit
\$appendchar{str, char} | appends char to str
\$removechar{str, index} | removes character from str at index
\$decl_filled_str{var, char, length} | declares a string variable filled with length*char

## Running this

### Linux (maybe Mac with g++)

On Linux you can use g++:

```shell
python3 algo_cpp_gen.py
g++ algo_bruteforce.cpp -o algo -O3 -std=c++11 -lpthread
./algo
```

I made a bash script which also builds and runs tests - `algo_bruteforce_run.sh`. You can add `-a` to skip generating c++ code from `algos.abalgo`, `-d` to compile with `-g` instead of `-O3`, `-i` to build and run without tests and `-g` to compile with `-g` instead of `-O3` but also lauch the program with `gdb`.

### Windows

on Windows it is a bit more complicated. You need to use Visual Studio or MinGW:

#### MinGW

 With MinGW it's basically same as on Linux, just replace `-lpthread` with `-lwinpthread`, note that you need the right MinGW version (posix thread model).
 If you have also GitBash you should be able to use the `algo_bruteforce_run.sh` if you replace `-lpthread` with `-lwinpthread` (on line 7). This is not tested though. Feel free to make a pull request with version written in batch!

#### Visual studio

I don't know how to use VS for C++, sorry :/. Just run the python script `algo_cpp_gen.py` and then somehow compilt `algo_bruteforce.cpp` with C++ standard `C++11` and `O3`. It uses C++ `<thread>` which might need to link some library, but I don't know...
