# Algo bruteforce

## THIS IS FOR AN OLDER VERSION - WILL MAKE README SOON

Probably the most interesting program here. It is written in C++ so you will need a C++ compiler to use it.

## Notes

To customize parameters, check `algo_bruteforce_cfg.hpp` :).

### What does this do?

It generates random algorithms like this:

```python
def humanscantsolvethis_decrypt(data, key):
    key = [ord(c)-64 for c in key]
    index = <random number>
    keyindex = <random number>
    result = ""
    while data:
        index = <random expression with index>
        while index < 0: index += len(data)
        index %= len(data)
        keyindex = <random expression with keyindex>
        while keyindex < 0: keyindex += len(key)
        keyindex %= len(key)
        result += data[index]
        data = data[:index] + data[index+1:]
    return result
```

and then tries them on \_DATA and \_KEY. If the result contains `DATA(`

If you can think of any way of improving this or making different algorithm generator, make a pull request or DM me on discord (I'm `__noop__#0077`).

## Linux (maybe Mac with g++)

On Linux you can use g++:

```shell
g++ algo_bruteforce.cpp -o algo -O3 -std=c++11 -lpthread
./algo
```

I made a bash script which also builds and runs tests - `algo_bruteforce_run.sh`. You can add `-d` to compile with `-g` instead of `-O3`, `-i` to build and run without tests and `-g` to compile with `-g` instead of `-O3` but also lauch the program with `gdb`.

## Windows

on Windows it is a bit more complicated. You need to use Visual Studio or MinGW (with MinGW it's basically same as on Linux, just replace `-lpthread` with `-lwinpthread`, note that you need the right MinGW version (posix thread model); I don't know how to use VS for C++).

If you have MinGW and GitBash you should be able to use the `algo_bruteforce_run.sh` if you replace `-lpthread` with `-lwinpthread` (on line 7). This is not tested though. Feel free to make a pull request with version written in batch!
