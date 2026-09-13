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

| Cpp-Simplified | Standard C++             |
|-----------------|--------------------------|
| `let`           | `auto`                   |
| `function`      | `auto` (as return type)  |
| `null`          | `nullptr`                |
| `structure`     | `struct`                 |
| `finish`        | `return 0;`              |
| `newL`          | `endl`                   |

> ⚠️ `finish` expands to `return 0;` verbatim. It only makes sense at the end of a function that returns `int` (typically `main`). Using it elsewhere, or following it with a stray `;`, will produce confusing code (`return 0;;`) or a type error.

### Readable logic & operators

| Cpp-Simplified   | Standard C++ |
|-------------------|--------------|
| `OR`               | `\|\|`        |
| `AND`              | `&&`         |
| `NOT`              | `!`          |
| `EQUAL_TO`         | `==`         |
| `NOT_EQUAL_TO`     | `!=`         |
| `SUB`              | `-`          |
| `MUL`              | `*`          |
| `DIV`              | `/`          |

**Precedence warning:** these expand as plain text substitution, so normal C++ operator precedence still applies. `NOT a EQUAL_TO b` expands to `!a == b`, **not** `!(a == b)`. Use parentheses explicitly:

```cpp
if (NOT (a EQUAL_TO b)) { ... } // correct
```

**Naming collision warning:** `SUB`, `MUL`, `DIV`, and the other macros below are defined globally via `#define`. If your own code (or another library) uses these as identifiers, they will be silently substituted. See [Reserved names](#reserved-names).

### `repeat(n)` loop

Runs a block `n` times without writing a manual index loop:

```cpp
repeat(10) {
    console.log("hi");
}
```

Each `repeat(n)` uses its own internally scoped counter, so nested `repeat()` blocks are safe. The counter itself is not exposed to the loop body — `repeat` is for "do this N times," not indexed iteration.

### Color macros

Raw ANSI escape codes, usable directly in any `cout`/`cerr` stream or string:

| Macro       | Effect            |
|-------------|-------------------|
| `RED`       | Red text          |
| `GREEN`     | Green text        |
| `YELLOW`    | Yellow text       |
| `BLUE`      | Blue text         |
| `MAGENTA`   | Magenta text      |
| `CYAN`      | Cyan text         |
| `RESET`     | Reset to default  |

```cpp
cout << RED << "This is red" << RESET << newL;
```

These are also used internally by `console.error`, `console.warn`, and `console.success` (see below).

### `console`

A small `cout`/`cerr` wrapper with JS-familiar method names:

```cpp
console.log("prints without a newline before it");
console.nlog("prints on a new line");
console.error("goes to stderr, shown in red");
console.warn("shown in yellow, prefixed with WARNING:");
console.success("shown in green, prefixed with Success:");

let name = string("");
console.prompt(name, "What's your name?");
```

`log`, `nlog`, `error`, `warn`, and `success` all accept any number of arguments of any type (via variadic `auto...`), so you can pass multiple values in one call:

```cpp
console.log("x =", 5, "y =", 10);
```

#### `console.log_table(rowArray, columnArray, rowLabel = "ROW", columnLabel = "COLUMN")`

Prints two arrays side-by-side as a simple two-column table:

```cpp
IntArray ids = {1, 2, 3};
StringArray names = {"Alice", "Bob", "Charlie"};
console.log_table(ids, names, "ID", "Name");
```

If the two arrays are different lengths, the shorter column is padded with `-`.

### `arrayReworked`

Simple array-copy helpers for common primitive types, since no templates are used at this layer:

```cpp
int source[5] = {1, 2, 3, 4, 5};
int dest[5];
arrayReworked.arrayCopierforINT(source, dest, 5);
```

Available for: `INT`, `STRING`, `CHAR`, `DOUBLE`, `SIZE_T`, `SHORT`, `LONG`, `LONG_LONG`, `BOOLEAN`.

Each copier has the signature `arrayCopierfor<TYPE>(sourceArray, destinationArray, size)` and copies `size` elements from source to destination.

### `List<T>` — dynamic typed array

A thin, readable wrapper around `std::vector<T>` for developers not yet comfortable with templates directly:

```cpp
List<int> scores;
scores.push(10);
scores.push(20);
scores.push(30);

console.log("Size:", scores.size());          // 3
console.log("Has 20:", scores.includes(20));   // true
console.log("Index of 20:", scores.indexOf(20)); // 1

scores.remove(20);
scores.print(); // [10, 30]

int first = scores[0]; // operator[] access
scores.clear();
```

You can also construct a `List` directly from a brace-enclosed initializer list:

```cpp
List<string> names = {"Alice", "Bob", "Charlie"};
```

| Method                | Description                                      |
|-----------------------|---------------------------------------------------|
| `push(value)`         | Appends `value` to the end                         |
| `pop()`               | Removes the last element (no-op if empty)          |
| `size()`              | Returns the number of elements                     |
| `includes(value)`     | Returns `true` if `value` exists in the list       |
| `indexOf(value)`      | Returns the index of `value`, or `-1` if not found |
| `remove(value)`       | Removes the first matching element                 |
| `clear()`             | Empties the list                                   |
| `print()`             | Prints the list as `[a, b, c]`                     |
| `operator[](i)`       | Access/modify the element at index `i`             |

#### Prebuilt type aliases

To avoid writing out `List<T>` for common types, the following aliases are provided:

```cpp
IntArray, StringArray, CharArray, DoubleArray, SizeTArray,
ShortArray, LongArray, LongLongArray, BooleanArray, Size_tArray
```

> Note: `SizeTArray` and `Size_tArray` are both aliases for `List<size_t>` and are functionally identical — this is a naming duplication, not two different types. Prefer `SizeTArray` for consistency with the other alias names.

### `FileReader`

Simple wrapper over `std::ifstream` for reading files:

```cpp
FileReader reader("data.txt");

if (reader.exists()) {
    string content = reader.readAll();
    console.log(content);
}

reader.close();
```

| Method          | Description                                              |
|-----------------|------------------------------------------------------------|
| `FileReader(path)` | Constructor — opens the file at `path` immediately       |
| `exists()`      | Returns `true` if the file was successfully opened          |
| `readAll()`     | Reads the entire file into a single `string` (lines joined with `\n`) |
| `readLines()`   | Reads the file into a `StringArray`, one entry per line      |
| `close()`       | Closes the underlying file stream                            |

> ⚠️ Always check `exists()` before calling `readAll()` or `readLines()` — if the file failed to open, these will silently return empty results rather than throwing an error.

### `FileWriter`

Simple wrapper over `std::ofstream` for writing files:

```cpp
FileWriter writer("output.txt");         // overwrites the file
FileWriter logFile("log.txt", true);     // append mode

writer.write("no newline after this");
writer.writeLine("this line ends with a newline");

writer.close();
```

| Method                       | Description                                                        |
|------------------------------|----------------------------------------------------------------------|
| `FileWriter(path, append=false)` | Constructor — opens `path` for writing; pass `true` to append instead of overwrite |
| `exists()`                   | Returns `true` if the file was successfully opened                    |
| `write(value)`               | Writes `value` to the file with no trailing newline                   |
| `writeLine(value)`           | Writes `value` to the file followed by a newline                      |
| `close()`                    | Closes the underlying file stream                                     |

> ⚠️ As with `FileReader`, writes will silently no-op if the file failed to open — check `exists()` first.

### `strings` (STRING helpers)

A small set of common string operations:

```cpp
string word = "level";

console.log(strings.reverseString(word));         // "level"
console.log(strings.isPalindrome(word));           // true
console.log(strings.palindromeMessage(word));      // "The word/statement 'level', is a palindrome!"

CharArray chars = strings.convertStringToCharArray(word);
chars.print(); // [l, e, v, e, l]
```

| Method                          | Description                                                |
|----------------------------------|--------------------------------------------------------------|
| `reverseString(input)`           | Returns a reversed copy of `input`                            |
| `isPalindrome(input)`            | Returns `true` if `input` reads the same forwards and backwards |
| `palindromeMessage(input)`       | Returns a human-readable sentence stating whether `input` is a palindrome |
| `convertStringToCharArray(input)`| Returns a `CharArray` containing each character of `input`   |

## Reserved names

Because many features are implemented as preprocessor macros, the following identifiers are reserved once you include `Cpp-Simplified.h` — avoid using them as your own variable, function, or type names:

```
let, function, null, structure, finish, newL,
OR, AND, NOT, EQUAL_TO, NOT_EQUAL_TO, SUB, MUL, DIV,
repeat,
RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, RESET
```

Using any of these as your own identifier will silently expand as a macro instead of behaving as a normal name, which can produce confusing compiler errors.

## Design notes

- **No templates at the macro/keyword layer.** Repetition (e.g. `arrayCopierfor*` variants) is a deliberate tradeoff in favor of simplicity over abstraction. `List<T>` is the one templated class in the library, provided as a more ergonomic alternative to the untemplated `arrayReworked` copiers.
- **`using namespace std;` is used inside the header.** If you're integrating this into a larger codebase, be aware this will bring the whole `std` namespace into any file that includes `Cpp-Simplified.h`.
- Everything library-specific lives under the `gpp` namespace (`gpp::console`, `gpp::arrayReworked`, `gpp::strings`, `gpp::List`, `gpp::FileReader`, `gpp::FileWriter`) — `using namespace gpp;` brings it into scope.

## License

MIT — see `LICENSE`.

## Author

Created by Dev-Mehraj, 2026.
