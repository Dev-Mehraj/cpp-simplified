# `cpp_simplified.hpp` — Single-Header C++ Utility Library

`cpp_simplified.hpp` is a lightweight, zero-dependency, single-header C++17/C++20 library that brings Python- and JavaScript-style ergonomics to standard C++. Every function and template is documented with structured Doxygen `@` tags (`@brief`, `@tparam`, `@param`, `@return`, `@note`, and `@code`) so your IDE displays rich hover tooltips and inline usage examples as you type.

## Key Highlights

* **Single-Header & Zero External Dependencies**: Drop `cpp_simplified.hpp` into your project and `#include` it—only the C++17 standard library is required.
* **Rich IDE Hover Tooltips**: Every function includes Doxygen `@` annotations with parameter descriptions, return types, and copy-pasteable code snippets for VS Code, CLion, Visual Studio, and `clangd`.
* **Python-Style Console I/O**: Print primitives, strings, `std::vector`, `std::map`, `std::set`, and `std::pair` directly via `easy::println(...)`, and read validated user input in one line with `easy::input(...)` and `easy::input_val<T>(...)`.
* **Zero Iterator Boilerplate**: Sort, filter, map, slice, sum, average, and search containers without writing `.begin()` and `.end()`.
* **Exception-Safe Parsing & One-Line File I/O**: Read or write files in a single function call and convert strings to numbers with fallback defaults instead of unhandled `std::invalid_argument` exceptions.

## Requirements & Installation

1. Copy `cpp_simplified.hpp` into your project's `include/` directory (or alongside your `.cpp` source files).
2. Include the header in your source file:

```cpp
#include "cpp_simplified.hpp"
```

3. Compile with any C++17 or newer compiler (`g++`, `clang++`, or `MSVC`):

```bash
g++ -std=c++20 -O2 main.cpp -o app
```

## Quick Start Example

```cpp
#include "cpp_simplified.hpp"

int main() {
    using namespace easy;

    // 1. Python-style printing (including vectors, maps, pairs, and sets)
    auto nums = range(1, 10); // [1, 2, 3, 4, 5, 6, 7, 8, 9]
    println("Generated numbers:", nums);

    // 2. Functional vector helpers without .begin() / .end()
    auto evens = filter(nums, [](int n) { return is_even(n); });
    auto squares = map_vec(evens, [](int n) { return n * n; });
    println("Even squares:", squares, "| Sum:", sum(squares), "| Avg:", average(squares));

    // 3. String manipulation
    auto words = split(trim("   C++ made simple and memorable   "), " ");
    println("Joined slug:", to_lower(join(words, "-")));

    // 4. Random utilities without engine boilerplate
    println("Random roll (1-6):", rand_int(1, 6), "| Random pick:", choice(words));

    // 5. Benchmarking in one line
    double elapsed = measure_ms([&]() {
        sleep_ms(50);
    });
    println("Task finished in", round_to(elapsed, 2), "ms");

    return 0;
}
```

## API Reference

All functions live inside the `easy` namespace (`easy::function_name` or via `using namespace easy;`).

### 1. Console I/O & Stream Operators

`cpp_simplified.hpp` overloads `operator<<` inside `namespace easy` for `std::pair`, `std::vector`, `std::set`, and `std::map`, allowing them to be streamed directly or passed to `print` and `println`.

| Function / Operator | Signature | Description | Example |
| :--- | :--- | :--- | :--- |
| `print` | `void print(const Args&... args)` | Prints any number of space-separated arguments without a trailing newline. | `easy::print("HP:", 100);` |
| `println` | `void println(const Args&... args)` | Prints any number of space-separated arguments followed by `\n`. | `easy::println("Items:", vec);` |
| `print_line` | `void print_line(char ch = '-', size_t length = 50)` | Prints a horizontal divider line of repeated characters. | `easy::print_line('=', 40);` |
| `input` | `std::string input(std::string_view prompt = "")` | Displays an optional prompt and reads a full line from `std::cin`. | `auto name = easy::input("Name: ");` |
| `input_val<T>` | `T input_val<T>(prompt, error_msg)` | Prompts and parses a value of type `T`, retrying automatically on invalid input. | `int age = easy::input_val<int>("Age: ");` |
| `confirm` | `bool confirm(std::string_view prompt, bool default_yes = true)` | Prompts the user with `[Y/n]` or `[y/N]` and returns `true` or `false`. | `if (easy::confirm("Save?")) { ... }` |

### 2. String Utilities

| Function | Signature | Description | Example |
| :--- | :--- | :--- | :--- |
| `to_lower` | `std::string to_lower(std::string_view s)` | Converts all characters to lowercase. | `to_lower("HeLLo") // "hello"` |
| `to_upper` | `std::string to_upper(std::string_view s)` | Converts all characters to uppercase. | `to_upper("HeLLo") // "HELLO"` |
| `capitalize` | `std::string capitalize(std::string_view s)` | Uppercases the first character and lowercases the rest. | `capitalize("cPP") // "Cpp"` |
| `ltrim` | `std::string ltrim(std::string_view s)` | Strips leading whitespace characters. | `ltrim("  hi ") // "hi "` |
| `rtrim` | `std::string rtrim(std::string_view s)` | Strips trailing whitespace characters. | `rtrim("  hi ") // "  hi"` |
| `trim` | `std::string trim(std::string_view s)` | Strips both leading and trailing whitespace. | `trim("  hi \n") // "hi"` |
| `split` | `std::vector<std::string> split(s, delim = " ", skip_empty = false)` | Splits a string by a delimiter into a vector of substrings. | `split("a,b,c", ",")` |
| `join` | `std::string join(const Container& items, sep = ", ")` | Joins any iterable container into a string with a separator. | `join(vec, " - ")` |
| `replace_all` | `std::string replace_all(s, from, to)` | Replaces every occurrence of `from` with `to`. | `replace_all("a-b-a", "a", "x")` |
| `starts_with` | `bool starts_with(s, prefix)` | Returns `true` if `s` begins with `prefix`. | `starts_with("main.cpp", "main")` |
| `ends_with` | `bool ends_with(s, suffix)` | Returns `true` if `s` ends with `suffix`. | `ends_with("main.cpp", ".cpp")` |
| `str_contains` | `bool str_contains(s, sub)` | Returns `true` if `sub` appears inside `s`. | `str_contains("hello", "ell")` |
| `repeat_str` | `std::string repeat_str(s, size_t count)` | Repeats string `s` `count` times. | `repeat_str("ab", 3) // "ababab"` |
| `reverse_str` | `std::string reverse_str(std::string_view s)` | Returns a reversed copy of `s`. | `reverse_str("abc") // "cba"` |
| `pad_left` | `std::string pad_left(s, total_width, pad_char = ' ')` | Left-pads `s` up to `total_width`. | `pad_left("7", 3, '0') // "007"` |
| `pad_right` | `std::string pad_right(s, total_width, pad_char = ' ')` | Right-pads `s` up to `total_width`. | `pad_right("7", 3, '0') // "700"` |
| `count_substr` | `size_t count_substr(s, sub)` | Counts non-overlapping occurrences of `sub` in `s`. | `count_substr("banana", "an") // 2` |
| `is_digits` | `bool is_digits(std::string_view s)` | Returns `true` if `s` is non-empty and contains only digits `0-9`. | `is_digits("12345") // true` |
| `is_alpha` | `bool is_alpha(std::string_view s)` | Returns `true` if `s` is non-empty and contains only letters. | `is_alpha("Hello") // true` |

### 3. Vector & Container Shortcuts

| Function | Signature | Description | Example |
| :--- | :--- | :--- | :--- |
| `range` | `std::vector<T> range(start, stop, step = 1)` | Generates `[start, stop)` with `step` (or `range(stop)` for `[0, stop)`). | `range(0, 10, 2) // [0, 2, 4, 6, 8]` |
| `linspace` | `std::vector<double> linspace(start, end, count)` | Generates `count` evenly spaced doubles across `[start, end]`. | `linspace(0.0, 1.0, 5)` |
| `contains` | `bool contains(const Container& c, const T& value)` | Checks if `value` exists in container `c`. | `contains(vec, 42)` |
| `index_of` | `ptrdiff_t index_of(const std::vector<T>& vec, const T& value)` | Returns zero-based index of `value`, or `-1` if not found. | `index_of(names, "Ali")` |
| `sort_asc` | `std::vector<T>& sort_asc(std::vector<T>& vec)` | Sorts `vec` in ascending order in-place and returns it. | `sort_asc(nums);` |
| `sort_desc` | `std::vector<T>& sort_desc(std::vector<T>& vec)` | Sorts `vec` in descending order in-place and returns it. | `sort_desc(nums);` |
| `reverse_vec` | `std::vector<T>& reverse_vec(std::vector<T>& vec)` | Reverses `vec` in-place and returns it. | `reverse_vec(nums);` |
| `unique_vec` | `std::vector<T> unique_vec(std::vector<T> vec)` | Returns a sorted copy of `vec` with duplicate elements removed. | `unique_vec(std::vector{3, 1, 3})` |
| `remove_val` | `size_t remove_val(std::vector<T>& vec, const T& value)` | Erases all occurrences of `value` in-place and returns count removed. | `remove_val(vec, 0);` |
| `remove_at` | `bool remove_at(std::vector<T>& vec, size_t index)` | Safely removes element at `index` if within bounds. | `remove_at(vec, 2);` |
| `slice` | `std::vector<T> slice(const std::vector<T>& vec, start, end)` | Returns sub-vector `[start, end)` clamped safely to bounds. | `slice(vec, 1, 4)` |
| `sum` | `auto sum(const Container& c)` | Returns the sum of all elements in a numeric container. | `sum(vec)` |
| `average` | `double average(const Container& c)` | Returns the arithmetic mean of a numeric container (`0.0` if empty). | `average(scores)` |
| `min_val` | `auto min_val(const Container& c)` | Returns the smallest element in a non-empty container. | `min_val(scores)` |
| `max_val` | `auto max_val(const Container& c)` | Returns the largest element in a non-empty container. | `max_val(scores)` |
| `filter` | `std::vector<T> filter(const std::vector<T>& vec, Pred pred)` | Returns a new vector with elements satisfying `pred`. | `filter(v, [](int x){ return x > 0; })` |
| `map_vec` | `auto map_vec(const std::vector<T>& vec, Func fn)` | Applies `fn` to each element and returns the transformed vector. | `map_vec(v, [](int x){ return x * 2; })` |
| `zip` | `std::vector<std::pair<T1, T2>> zip(const vec1&, const vec2&)` | Pairs elements from two vectors up to the shorter length. | `zip(keys_vec, vals_vec)` |

### 4. Map & Set Helpers

| Function | Signature | Description | Example |
| :--- | :--- | :--- | :--- |
| `has_key` | `bool has_key(const MapType& m, const KeyType& key)` | Checks whether `key` exists in a `std::map` or `std::unordered_map`. | `has_key(config, "port")` |
| `get_or` | `mapped_type get_or(const MapType& m, key, default_val)` | Returns `m[key]` if present, or `default_val` without mutating `m`. | `get_or(scores, "Alice", 0)` |
| `keys` | `std::vector<key_type> keys(const MapType& m)` | Extracts all keys from a map into a `std::vector`. | `auto k = keys(user_map);` |
| `values` | `std::vector<mapped_type> values(const MapType& m)` | Extracts all values from a map into a `std::vector`. | `auto v = values(user_map);` |

### 5. Math, Number & Random Utilities

Uses a thread-local `std::mt19937` engine seeded automatically via `std::random_device`.

| Function | Signature | Description | Example |
| :--- | :--- | :--- | :--- |
| `rand_int` | `IntType rand_int(IntType min_val, IntType max_val)` | Returns a random integer in the inclusive range `[min_val, max_val]`. | `rand_int(1, 100)` |
| `rand_float` | `RealType rand_float(min_val = 0.0, max_val = 1.0)` | Returns a random floating-point value in `[min_val, max_val)`. | `rand_float(0.0, 10.0)` |
| `rand_bool` | `bool rand_bool(double probability_true = 0.5)` | Returns `true` with probability `probability_true`. | `rand_bool(0.75)` |
| `choice` | `T choice(const std::vector<T>& vec)` | Picks and returns a random element from a non-empty vector. | `choice(cards)` |
| `shuffle_vec` | `std::vector<T>& shuffle_vec(std::vector<T>& vec)` | Randomly shuffles `vec` in-place and returns it. | `shuffle_vec(deck);` |
| `clamp_val` | `constexpr T clamp_val(T val, T low, T high)` | Clamps `val` to stay within `[low, high]`. | `clamp_val(speed, 0, 120)` |
| `lerp` | `constexpr double lerp(double a, double b, double t)` | Linearly interpolates between `a` and `b` by factor `t`. | `lerp(0.0, 100.0, 0.25) // 25.0` |
| `remap` | `constexpr double remap(val, in_min, in_max, out_min, out_max)` | Maps `val` from `[in_min, in_max]` to `[out_min, out_max]`. | `remap(512, 0, 1023, 0, 100)` |
| `is_even` | `constexpr bool is_even(IntType n)` | Returns `true` if `n` is divisible by 2. | `is_even(42) // true` |
| `is_odd` | `constexpr bool is_odd(IntType n)` | Returns `true` if `n` is not divisible by 2. | `is_odd(7) // true` |
| `is_prime` | `constexpr bool is_prime(long long n)` | Primality test in $O(\sqrt{n})$ time. | `is_prime(97) // true` |
| `factorial` | `constexpr unsigned long long factorial(unsigned int n)` | Computes $n!$ for $0 \le n \le 20$. | `factorial(5) // 120` |
| `gcd` | `constexpr long long gcd(long long a, long long b)` | Computes the greatest common divisor of `a` and `b`. | `gcd(12, 18) // 6` |
| `lcm` | `constexpr long long lcm(long long a, long long b)` | Computes the least common multiple of `a` and `b`. | `lcm(4, 6) // 12` |
| `round_to` | `double round_to(double val, int decimals = 2)` | Rounds a floating-point number to `decimals` decimal places. | `round_to(3.14159, 2) // 3.14` |
| `approx_equal` | `bool approx_equal(double a, double b, double eps = 1e-9)` | Checks whether `|a - b| <= eps`. | `approx_equal(0.1 + 0.2, 0.3)` |

### 6. File I/O, Timing & Safe Conversions

| Function | Signature | Description | Example |
| :--- | :--- | :--- | :--- |
| `read_file` | `std::string read_file(const std::string& path)` | Reads an entire file into a `std::string` (`""` on failure). | `auto txt = read_file("notes.txt");` |
| `read_lines` | `std::vector<std::string> read_lines(const std::string& path)` | Reads all lines of a text file into a vector of strings. | `auto lines = read_lines("log.txt");` |
| `write_file` | `bool write_file(const std::string& path, std::string_view content)` | Overwrites a file with `content` and returns `true` on success. | `write_file("out.txt", "Hello");` |
| `append_file` | `bool append_file(const std::string& path, std::string_view content)` | Appends `content` to the end of a file. | `append_file("out.txt", "\nMore");` |
| `file_exists` | `bool file_exists(const std::string& path)` | Returns `true` if a file or folder exists at `path`. | `if (file_exists("cfg.ini")) { ... }` |
| `sleep_ms` | `void sleep_ms(long long ms)` | Sleeps the current thread for `ms` milliseconds. | `sleep_ms(250);` |
| `sleep_sec` | `void sleep_sec(double seconds)` | Sleeps the current thread for `seconds` (supports fractional seconds). | `sleep_sec(1.5);` |
| `now_ms` | `int64_t now_ms()` | Returns current Unix epoch timestamp in milliseconds. | `auto t0 = now_ms();` |
| `measure_ms` | `double measure_ms(Func&& fn)` | Executes `fn()` and returns elapsed wall-clock time in milliseconds. | `double ms = measure_ms([&]{ run(); });` |
| `to_str` | `std::string to_str(const T& val)` | Converts any streamable value into a `std::string`. | `to_str(42) // "42"` |
| `to_int` | `int to_int(std::string_view s, int default_val = 0)` | Exception-safe string-to-`int` parser with fallback default. | `to_int("bad", -1) // -1` |
| `to_double` | `double to_double(std::string_view s, double default_val = 0.0)` | Exception-safe string-to-`double` parser with fallback default. | `to_double("3.5", 0.0) // 3.5` |

## IDE Hover Documentation (`@` Tags)

Every function in `cpp_simplified.hpp` is annotated with standard Doxygen tags:

* `@brief` — Concise one-sentence summary shown at the top of the hover popup.
* `@tparam` & `@param` — Type and parameter explanations.
* `@return` — Description of the returned value and edge-case behavior.
* `@code ... @endcode` — Syntax-highlighted usage example rendered directly inside the IDE tooltip.
