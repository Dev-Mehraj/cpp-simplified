# Cpp-Simplified

A single-header C++20 library that makes C++ syntax easier to **read and remember**, without using templates or advanced/high-level programming tricks.

This is aimed at developers who are comfortable writing "plain English" code and are struggling to get familiar with dense C++ syntax. It is **not** an attempt to turn C++ into JavaScript — it's a readability layer on top of standard C++.

> ⚠️ This is a learning/teaching-oriented library, not a drop-in replacement for idiomatic C++. Use it to get comfortable, then graduate to standard syntax as you go.

## Requirements

- **C++20** (uses abbreviated function templates via `auto` parameters)
- Minimum compiler versions:
    - GCC 10+ (GCC 11+ recommended)
    - Clang 12+ (Clang 14+ recommended)
    - MSVC 19.29+ (VS 2019 16.11+) or VS 2022

In your `CMakeLists.txt`:

```cmake
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
```

## Installation

Just drop `Cpp-Simplified.h` into your project and include it:

```cpp
#include "Cpp-Simplified.h"
using namespace gpp;
```

## Usage

```cpp
#include "Cpp-Simplified.h"
using namespace gpp;

int main() {
    let i = 19;
    let v = 19;

    if (i EQUAL_TO v) {
        repeat(3) {
            console.nlog("THIS CONFIRMS THAT EVERY FEATURE IS WORKING!");
        }
    }

    return 0;
}
```

## Features

### Readable keywords

| Cpp-Simplified       | Standard C++ |
|---------------|--------------|
| `let`         | `auto`       |
| `function`    | `auto` (as return type) |
| `null`        | `nullptr`    |
| `structure`   | `struct`     |

### Readable logic & operators

| Cpp-Simplified         | Standard C++ |
|-----------------|--------------|
| `OR`            | `\|\|`        |
| `AND`           | `&&`         |
| `NOT`           | `!`          |
| `EQUAL_TO`      | `==`         |
| `NOT_EQUAL_TO`  | `!=`         |
| `SUB`           | `-`          |
| `MUL`           | `*`          |
| `DIV`           | `/`          |

**Precedence warning:** these expand as plain text substitution, so normal C++ operator precedence still applies. `NOT a EQUAL_TO b` expands to `!a == b`, **not** `!(a == b)`. Use parentheses explicitly:

```cpp
if (NOT (a EQUAL_TO b)) { ... } // correct
```

### `repeat(n)` loop

Runs a block `n` times without writing a manual index loop:

```cpp
repeat(10) {
    console.log("hi");
}
```

Each `repeat(n)` uses its own internally scoped counter, so nested `repeat()` blocks are safe. The counter itself is not exposed to the loop body — `repeat` is for "do this N times," not indexed iteration.

### `console`

A small `cout`/`cerr` wrapper with JS-familiar method names:

```cpp
console.log("prints without a newline before it");
console.nlog("prints on a new line");
console.error("goes to stderr");
console.warn("prefixed with WARNING:");

let name = string("");
console.prompt(name, "What's your name?");
```

### `arrayReworked`

Simple array-copy helpers for common primitive types, since no templates are used:

```cpp
int source[5] = {1, 2, 3, 4, 5};
int dest[5];
arrayReworked.arrayCopierforINT(source, dest, 5);
```

Available for: `INT`, `STRING`, `CHAR`, `DOUBLE`, `SIZE_T`, `SHORT`, `LONG`, `LONG_LONG`, `BOOLEAN`.

## ⚠️ Reserved names

Because many features are implemented as preprocessor macros, the following identifiers are reserved once you include `Cpp-Simplified.h` — avoid using them as your own variable, function, or type names:

```
let, function, null, structure,
OR, AND, NOT, EQUAL_TO, NOT_EQUAL_TO, SUB, MUL, DIV,
repeat
```

Using any of these as your own identifier will silently expand as a macro instead of behaving as a normal name, which can produce confusing compiler errors.

## Design notes

- **No templates.** Repetition (e.g. `arrayCopierfor*` variants) is a deliberate tradeoff in favor of simplicity over abstraction.
- **`using namespace std;` is used inside the header.** If you're integrating this into a larger codebase, be aware this will bring the whole `std` namespace into any file that includes `Cpp-Simplified.h`.
- Everything library-specific lives under the `gpp` namespace (`gpp::console`, `gpp::arrayReworked`) — `using namespace gpp;` brings it into scope.

## License

MIT — see `LICENSE`.

## Author

Created by Dev-Mehraj, 2026.
