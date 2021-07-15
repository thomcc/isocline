<img align="right" width="500px" src="doc/completion-id.png"/>

# Repline> <br>a portable readline alternative.

Repline is a pure C library that can be used as readline alternative. 

- Small: less than 3k lines and can be compiled as a single C file without 
  any dependencies or configuration (e.g. `gcc -c src/repline.c`).
- Portable: works on Unix, Windows, and macOS, and relies on a minimal
  subset of ANSI escape sequences.
- Features: extensive multi-line editing mode, colors, history, completion, unicode, 
  graceful fallback, etc.
- License: MIT.

Enjoy,
  Daan

## Usage

Include the repline header in your C or C++ source:
```C
#include <include/repline.h>
```

and call `rl_readline` to get user input with rich editing abilities:
```C
rl_env_t* env = rl_init();
char* input;
while( (input = rl_readline(env,"prompt")) != NULL ) { // ctrl+d or errors return NULL
  // use the input
  free(input);  
}
```

See the [example](test/example.c) for a full example with completion, history, etc.

## Build

### CMake

Clone the repository and run cmake:
```
$ git clone https://github.com/daanx/repline
$ cd repline
$ mkdir -p out/release
$ cd out/release
$ cmake ../..
$ cmake --build .
```

and run the example program:
```
$ ./example
```

### As a single source

Copy the sources (in `include` and `src`) into your project, or add the library as a [submodule]:
```
$ git submodule add https://github.com/daanx/repline
```
and add `repline/src/repline.c` to your build rules -- no configuration is needed, for example:
```
$ gcc -c repline/src/repline.c
```

## Motivation

Repline was created for use in the [Koka] interative compiler. 
This required: pure C (no dependency on a C++ runtime or other libraries), 
portable (across Linux, macOS, and Windows), unicode support, 
a BSD-style license, and good functionality for completion and multi-line editing.

Some other libraries that we considered:
[GNU readline](https://tiswww.case.edu/php/chet/readline/rltop.html),
[editline](https://github.com/troglobit/editline),
[linenoise](https://github.com/antirez/linenoise),
[replxx](https://github.com/AmokHuginnsson/replxx).

[koka]: http://www.koka-lang.org
[submodule]: https://git-scm.com/book/en/v2/Git-Tools-Submodules

