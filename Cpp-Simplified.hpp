/**
 * @filecpp_simplified.hpp
 * @brief Single-header C++ utility library designed to make C++ easier, shorter, and more memorable.
 * @details Provides intuitive one-liner functions for Console I/O, Strings, Vectors/Containers,
 *          Maps/Sets, Math & Random, File I/O, Timing, and Type Conversions, all documented
 *          with Doxygen @ tags for rich IDE hover tooltips.
 * @version 2.0.0
 * @date 2026-10-22
 */

#pragma once

#ifndef CPP_SIMPLIFIED_HPP
#define CPP_SIMPLIFIED_HPP

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <optional>
#include <random>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace easy {

// ============================================================================
// 1. STREAM & CONTAINER PRINTING HELPERS (INTERNAL & PUBLIC)
// ============================================================================

/**
 * @brief Outputs a std::pair to an output stream in `(first, second)` format.
 * @tparam T1 Type of the first element.
 * @tparam T2 Type of the second element.
 * @param os Target output stream.
 * @param p The pair to print.
 * @return Reference to the output stream.
 */
template <typename T1, typename T2>
inline std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}

/**
 * @brief Outputs a std::vector to an output stream in `[e1, e2, ...]` format.
 * @tparam T Element type of the vector.
 * @param os Target output stream.
 * @param vec The vector to print.
 * @return Reference to the output stream.
 */
template <typename T>
inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[";
    for (std::size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i + 1 < vec.size()) os << ", ";
    }
    return os << "]";
}

/**
 * @brief Outputs a std::set to an output stream in `{e1, e2, ...}` format.
 * @tparam T Element type of the set.
 * @param os Target output stream.
 * @param s The set to print.
 * @return Reference to the output stream.
 */
template <typename T>
inline std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
    os << "{";
    std::size_t i = 0;
    for (const auto& elem : s) {
        os << elem;
        if (++i < s.size()) os << ", ";
    }
    return os << "}";
}

/**
 * @brief Outputs a std::map to an output stream in `{k1: v1, k2: v2, ...}` format.
 * @tparam K Key type of the map.
 * @tparam V Value type of the map.
 * @param os Target output stream.
 * @param m The map to print.
 * @return Reference to the output stream.
 */
template <typename K, typename V>
inline std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{";
    std::size_t i = 0;
    for (const auto& [k, v] : m) {
        os << k << ": " << v;
        if (++i < m.size()) os << ", ";
    }
    return os << "}";
}

// ============================================================================
// 2. CONSOLE I/O (PYTHON-STYLE PRINT & INPUT)
// ============================================================================

/**
 * @brief Prints any number of arguments separated by spaces without a trailing newline.
 * @tparam Args Variadic argument types (supports primitives, strings, vectors, maps, sets, pairs).
 * @param args Values to print to standard output.
 * @note Use `println(...)` if you want an automatic newline at the end.
 * @code
 * easy::print("Score:", 100, "Items:", std::vector<int>{1, 2, 3});
 * @endcode
 */
template <typename... Args>
inline void print(const Args&... args) {
    std::size_t idx = 0;
    ((std::cout << (idx++ > 0 ? " " : "") << args), ...);
}

/**
 * @brief Prints any number of arguments separated by spaces, followed by a newline.
 * @tparam Args Variadic argument types (supports primitives, strings, vectors, maps, sets, pairs).
 * @param args Values to print to standard output.
 * @code
 * easy::println("Hello", "World!", 42);
 * @endcode
 */
template <typename... Args>
inline void println(const Args&... args) {
    print(args...);
    std::cout << '\n';
}

/**
 * @brief Prints a divider line to the console for visual separation.
 * @param ch Character to repeat (default: `'-'`).
 * @param length Number of characters in the line (default: `50`).
 * @code
 * easy::print_line('=', 40);
 * @endcode
 */
inline void print_line(char ch = '-', std::size_t length = 50) {
    std::cout << std::string(length, ch) << '\n';
}

/**
 * @brief Prompts the user and reads a full line of text from standard input.
 * @param prompt Optional message displayed before reading input (default: `""`).
 * @return The full line entered by the user as a `std::string`.
 * @code
 * std::string name = easy::input("Enter your name: ");
 * @endcode
 */
inline std::string input(std::string_view prompt = "") {
    if (!prompt.empty()) {
        std::cout << prompt << std::flush;
    }
    std::string line;
    std::getline(std::cin, line);
    return line;
}

/**
 * @brief Prompts the user and safely reads a value of type `T`, retrying on invalid input.
 * @tparam T Target type to parse (e.g., `int`, `double`, `long`).
 * @param prompt Message displayed before reading input.
 * @param error_msg Message displayed when parsing fails (default: `"Invalid input, try again: "`).
 * @return The parsed value of type `T`.
 * @code
 * int age = easy::input_val<int>("Enter your age: ");
 * @endcode
 */
template <typename T>
inline T input_val(std::string_view prompt = "", std::string_view error_msg = "Invalid input, try again: ") {
    if (!prompt.empty()) {
        std::cout << prompt << std::flush;
    }
    T value{};
    while (true) {
        std::string line;
        if (!std::getline(std::cin, line)) {
            return value;
        }
        std::istringstream iss(line);
        if ((iss >> value) && (iss >> std::ws).eof()) {
            return value;
        }
        std::cout << error_msg << std::flush;
    }
}

/**
 * @brief Prompts the user for a Yes/No confirmation and returns a boolean.
 * @param prompt Question prompt shown to the user.
 * @param default_yes Returned if the user presses Enter without typing (default: `true`).
 * @return `true` if the user enters y/yes/1/true, `false` otherwise.
 * @code
 * if (easy::confirm("Save changes?")) { ... }
 * @endcode
 */
inline bool confirm(std::string_view prompt, bool default_yes = true) {
    std::cout << prompt << (default_yes ? " [Y/n]: " : " [y/N]: ") << std::flush;
    std::string resp;
    if (!std::getline(std::cin, resp) || resp.empty()) {
        return default_yes;
    }
    char first = static_cast<char>(std::tolower(static_cast<unsigned char>(resp[0])));
    if (first == 'y' || first == '1') return true;
    if (first == 'n' || first == '0') return false;
    return default_yes;
}

// ============================================================================
// 3. STRING UTILITIES (MEMORABLE PYTHON/JS-STYLE HELPERS)
// ============================================================================

/**
 * @brief Converts all characters in a string to lowercase.
 * @param s Input string view.
 * @return A new lowercase `std::string`.
 * @code
 * auto lower = easy::to_lower("HeLLo"); // "hello"
 * @endcode
 */
inline std::string to_lower(std::string_view s) {
    std::string out(s);
    std::transform(out.begin(), out.end(), out.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return out;
}

/**
 * @brief Converts all characters in a string to uppercase.
 * @param s Input string view.
 * @return A new uppercase `std::string`.
 * @code
 * auto upper = easy::to_upper("HeLLo"); // "HELLO"
 * @endcode
 */
inline std::string to_upper(std::string_view s) {
    std::string out(s);
    std::transform(out.begin(), out.end(), out.begin(),
                   [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
    return out;
}

/**
 * @brief Capitalizes the first character of a string and lowercases the rest.
 * @param s Input string view.
 * @return Capitalized `std::string`.
 * @code
 * auto cap = easy::capitalize("cPP iS fUN"); // "Cpp is fun"
 * @endcode
 */
inline std::string capitalize(std::string_view s) {
    if (s.empty()) return "";
    std::string out = to_lower(s);
    out[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(out[0])));
    return out;
}

/**
 * @brief Removes leading whitespace from a string.
 * @param s Input string view.
 * @return Left-trimmed `std::string`.
 */
inline std::string ltrim(std::string_view s) {
    std::size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) {
        ++start;
    }
    return std::string(s.substr(start));
}

/**
 * @brief Removes trailing whitespace from a string.
 * @param s Input string view.
 * @return Right-trimmed `std::string`.
 */
inline std::string rtrim(std::string_view s) {
    std::size_t end = s.size();
    while (end > 0 && std::isspace(static_cast<unsigned char>(s[end - 1]))) {
        --end;
    }
    return std::string(s.substr(0, end));
}

/**
 * @brief Removes both leading and trailing whitespace from a string.
 * @param s Input string view.
 * @return Trimmed `std::string`.
 * @code
 * auto clean = easy::trim("   hello world \n\t "); // "hello world"
 * @endcode
 */
inline std::string trim(std::string_view s) {
    return rtrim(ltrim(s));
}

/**
 * @brief Splits a string by a delimiter string into a vector of substrings.
 * @param s Input string view to split.
 * @param delim Delimiter string (default: `" "`).
 * @param skip_empty Whether to omit empty tokens (default: `false`).
 * @return `std::vector<std::string>` containing the split parts.
 * @code
 * auto parts = easy::split("a,b,c", ","); // ["a", "b", "c"]
 * @endcode
 */
inline std::vector<std::string> split(std::string_view s, std::string_view delim = " ", bool skip_empty = false) {
    std::vector<std::string> tokens;
    if (delim.empty()) {
        tokens.emplace_back(s);
        return tokens;
    }
    std::size_t pos = 0;
    while (true) {
        std::size_t next = s.find(delim, pos);
        std::string_view token = (next == std::string_view::npos)
                                     ? s.substr(pos)
                                     : s.substr(pos, next - pos);
        if (!skip_empty || !token.empty()) {
            tokens.emplace_back(token);
        }
        if (next == std::string_view::npos) break;
        pos = next + delim.size();
    }
    return tokens;
}

/**
 * @brief Joins elements of any container into a single string with a separator.
 * @tparam Container Any iterable container (e.g., `std::vector<std::string>`, `std::vector<int>`).
 * @param items Container of elements to join.
 * @param sep Separator string inserted between elements (default: `", "`).
 * @return Joined `std::string`.
 * @code
 * std::string csv = easy::join(std::vector<int>{10, 20, 30}, "-"); // "10-20-30"
 * @endcode
 */
template <typename Container>
inline std::string join(const Container& items, std::string_view sep = ", ") {
    std::ostringstream oss;
    auto it = std::begin(items);
    auto end = std::end(items);
    bool first = true;
    for (; it != end; ++it) {
        if (!first) oss << sep;
        oss << *it;
        first = false;
    }
    return oss.str();
}

/**
 * @brief Replaces all occurrences of `from` with `to` in a string.
 * @param s Input string view.
 * @param from Substring to search for.
 * @param to Replacement string.
 * @return New `std::string` with all occurrences replaced.
 * @code
 * auto res = easy::replace_all("foo bar foo", "foo", "baz"); // "baz bar baz"
 * @endcode
 */
inline std::string replace_all(std::string_view s, std::string_view from, std::string_view to) {
    if (from.empty()) return std::string(s);
    std::string out;
    out.reserve(s.size());
    std::size_t pos = 0;
    while (true) {
        std::size_t next = s.find(from, pos);
        if (next == std::string_view::npos) {
            out.append(s.substr(pos));
            break;
        }
        out.append(s.substr(pos, next - pos));
        out.append(to);
        pos = next + from.size();
    }
    return out;
}

/**
 * @brief Checks if a string starts with the given prefix.
 * @param s Input string view.
 * @param prefix Prefix to check.
 * @return `true` if `s` starts with `prefix`, `false` otherwise.
 */
inline bool starts_with(std::string_view s, std::string_view prefix) {
    return s.size() >= prefix.size() && s.compare(0, prefix.size(), prefix) == 0;
}

/**
 * @brief Checks if a string ends with the given suffix.
 * @param s Input string view.
 * @param suffix Suffix to check.
 * @return `true` if `s` ends with `suffix`, `false` otherwise.
 */
inline bool ends_with(std::string_view s, std::string_view suffix) {
    return s.size() >= suffix.size() &&
           s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0;
}

/**
 * @brief Checks if a string contains a substring.
 * @param s Input string view to search in.
 * @param sub Substring to look for.
 * @return `true` if `sub` is found within `s`, `false` otherwise.
 */
inline bool str_contains(std::string_view s, std::string_view sub) {
    return s.find(sub) != std::string_view::npos;
}

/**
 * @brief Repeats a string `count` times.
 * @param s String view to repeat.
 * @param count Number of repetitions.
 * @return Repeated `std::string`.
 * @code
 * auto stars = easy::repeat_str("*", 5); // "*****"
 * @endcode
 */
inline std::string repeat_str(std::string_view s, std::size_t count) {
    std::string out;
    out.reserve(s.size() * count);
    for (std::size_t i = 0; i < count; ++i) {
        out.append(s);
    }
    return out;
}

/**
 * @brief Reverses a string and returns the reversed copy.
 * @param s Input string view.
 * @return Reversed `std::string`.
 */
inline std::string reverse_str(std::string_view s) {
    return std::string(s.rbegin(), s.rend());
}

/**
 * @brief Pads a string on the left until it reaches `total_width`.
 * @param s Input string view.
 * @param total_width Desired minimum character length.
 * @param pad_char Padding character (default: `' '`).
 * @return Left-padded `std::string`.
 * @code
 * auto id = easy::pad_left("42", 5, '0'); // "00042"
 * @endcode
 */
inline std::string pad_left(std::string_view s, std::size_t total_width, char pad_char = ' ') {
    if (s.size() >= total_width) return std::string(s);
    return std::string(total_width - s.size(), pad_char) + std::string(s);
}

/**
 * @brief Pads a string on the right until it reaches `total_width`.
 * @param s Input string view.
 * @param total_width Desired minimum character length.
 * @param pad_char Padding character (default: `' '`).
 * @return Right-padded `std::string`.
 */
inline std::string pad_right(std::string_view s, std::size_t total_width, char pad_char = ' ') {
    if (s.size() >= total_width) return std::string(s);
    return std::string(s) + std::string(total_width - s.size(), pad_char);
}

/**
 * @brief Counts how many non-overlapping times `sub` appears in `s`.
 * @param s Input string view.
 * @param sub Substring to count.
 * @return Number of occurrences.
 */
inline std::size_t count_substr(std::string_view s, std::string_view sub) {
    if (sub.empty()) return 0;
    std::size_t count = 0;
    std::size_t pos = 0;
    while ((pos = s.find(sub, pos)) != std::string_view::npos) {
        ++count;
        pos += sub.size();
    }
    return count;
}

/**
 * @brief Checks if a non-empty string consists solely of numeric digits (0-9).
 * @param s Input string view.
 * @return `true` if all characters are digits and string is non-empty.
 */
inline bool is_digits(std::string_view s) {
    return !s.empty() && std::all_of(s.begin(), s.end(),
                                     [](unsigned char c) { return std::isdigit(c) != 0; });
}

/**
 * @brief Checks if a non-empty string consists solely of alphabetic letters (A-Z, a-z).
 * @param s Input string view.
 * @return `true` if all characters are alphabetic and string is non-empty.
 */
inline bool is_alpha(std::string_view s) {
    return !s.empty() && std::all_of(s.begin(), s.end(),
                                     [](unsigned char c) { return std::isalpha(c) != 0; });
}

// ============================================================================
// 4. VECTOR & COLLECTION SHORTCUTS (NO MORE .begin() / .end() BOILERPLATE)
// ============================================================================

/**
 * @brief Generates a sequence of numbers `[start, stop)` with a given `step` (like Python's `range`).
 * @tparam T Arithmetic type (default: `int`).
 * @param start Starting value (inclusive).
 * @param stop Stopping value (exclusive).
 * @param step Increment step (default: `1`).
 * @return `std::vector<T>` containing the generated sequence.
 * @code
 * auto nums = easy::range(0, 10, 2); // [0, 2, 4, 6, 8]
 * @endcode
 */
template <typename T = int>
inline std::vector<T> range(T start, T stop, T step = 1) {
    std::vector<T> result;
    if (step == 0) return result;
    if (step > 0 && start < stop) {
        for (T val = start; val < stop; val += step) result.push_back(val);
    } else if (step < 0 && start > stop) {
        for (T val = start; val > stop; val += step) result.push_back(val);
    }
    return result;
}

/**
 * @brief Generates a sequence `[0, stop)` with step 1 (like Python's `range(n)`).
 * @tparam T Integral type (default: `int`).
 * @param stop Stopping value (exclusive).
 * @return `std::vector<T>` from `0` to `stop - 1`.
 * @code
 * auto first5 = easy::range(5); // [0, 1, 2, 3, 4]
 * @endcode
 */
template <typename T = int>
inline std::vector<T> range(T stop) {
    return range<T>(0, stop, 1);
}

/**
 * @brief Generates `count` evenly spaced doubles across `[start, end]` inclusive.
 * @param start Starting value.
 * @param end Ending value (inclusive).
 * @param count Number of points to generate.
 * @return `std::vector<double>` of evenly spaced values.
 */
inline std::vector<double> linspace(double start, double end, std::size_t count) {
    std::vector<double> out;
    if (count == 0) return out;
    if (count == 1) {
        out.push_back(start);
        return out;
    }
    out.reserve(count);
    double step = (end - start) / static_cast<double>(count - 1);
    for (std::size_t i = 0; i < count; ++i) {
        out.push_back(start + step * static_cast<double>(i));
    }
    return out;
}

/**
 * @brief Checks whether a container contains a specific value.
 * @tparam Container Any iterable container.
 * @tparam T Value type to search for.
 * @param c Container to inspect.
 * @param value Value to find.
 * @return `true` if `value` is present in `c`, `false` otherwise.
 * @code
 * if (easy::contains(my_vec, 42)) { ... }
 * @endcode
 */
template <typename Container, typename T>
inline bool contains(const Container& c, const T& value) {
    return std::find(std::begin(c), std::end(c), value) != std::end(c);
}

/**
 * @brief Finds the zero-based index of `value` in a vector, or returns `-1` if not found.
 * @tparam T Element type of the vector.
 * @param vec Vector to search.
 * @param value Element to find.
 * @return Index as `std::ptrdiff_t`, or `-1` if missing.
 * @code
 * auto idx = easy::index_of(vec, "apple");
 * @endcode
 */
template <typename T>
inline std::ptrdiff_t index_of(const std::vector<T>& vec, const T& value) {
    auto it = std::find(vec.begin(), vec.end(), value);
    if (it == vec.end()) return -1;
    return std::distance(vec.begin(), it);
}

/**
 * @brief Sorts a vector in ascending order in-place and returns a reference to it.
 * @tparam T Element type.
 * @param vec Vector to sort.
 * @return Reference to the sorted vector `vec`.
 * @code
 * easy::sort_asc(numbers);
 * @endcode
 */
template <typename T>
inline std::vector<T>& sort_asc(std::vector<T>& vec) {
    std::sort(vec.begin(), vec.end());
    return vec;
}

/**
 * @brief Sorts a vector in descending order in-place and returns a reference to it.
 * @tparam T Element type.
 * @param vec Vector to sort.
 * @return Reference to the sorted vector `vec`.
 * @code
 * easy::sort_desc(scores);
 * @endcode
 */
template <typename T>
inline std::vector<T>& sort_desc(std::vector<T>& vec) {
    std::sort(vec.begin(), vec.end(), std::greater<T>());
    return vec;
}

/**
 * @brief Reverses a vector in-place and returns a reference to it.
 * @tparam T Element type.
 * @param vec Vector to reverse.
 * @return Reference to the reversed vector `vec`.
 */
template <typename T>
inline std::vector<T>& reverse_vec(std::vector<T>& vec) {
    std::reverse(vec.begin(), vec.end());
    return vec;
}

/**
 * @brief Returns a new vector with duplicate elements removed (preserving sorted order).
 * @tparam T Element type.
 * @param vec Input vector.
 * @return New `std::vector<T>` containing only unique values.
 * @code
 * auto uniq = easy::unique_vec(std::vector<int>{3, 1, 2, 1, 3}); // [1, 2, 3]
 * @endcode
 */
template <typename T>
inline std::vector<T> unique_vec(std::vector<T> vec) {
    std::sort(vec.begin(), vec.end());
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
    return vec;
}

/**
 * @brief Removes all occurrences of `value` from a vector in-place.
 * @tparam T Element type.
 * @param vec Vector to modify.
 * @param value Value to erase.
 * @return Number of elements removed.
 */
template <typename T>
inline std::size_t remove_val(std::vector<T>& vec, const T& value) {
    std::size_t before = vec.size();
    vec.erase(std::remove(vec.begin(), vec.end(), value), vec.end());
    return before - vec.size();
}

/**
 * @brief Removes the element at `index` from a vector safely if in bounds.
 * @tparam T Element type.
 * @param vec Vector to modify.
 * @param index Zero-based index to remove.
 * @return `true` if removed, `false` if `index` was out of range.
 */
template <typename T>
inline bool remove_at(std::vector<T>& vec, std::size_t index) {
    if (index >= vec.size()) return false;
    vec.erase(vec.begin() + static_cast<std::ptrdiff_t>(index));
    return true;
}

/**
 * @brief Extracts a slice `[start, end)` from a vector (clamped safely to vector bounds).
 * @tparam T Element type.
 * @param vec Source vector.
 * @param start Inclusive start index.
 * @param end Exclusive end index.
 * @return Sliced `std::vector<T>`.
 * @code
 * auto sub = easy::slice(vec, 1, 4);
 * @endcode
 */
template <typename T>
inline std::vector<T> slice(const std::vector<T>& vec, std::size_t start, std::size_t end) {
    if (start >= vec.size() || start >= end) return {};
    end = std::min(end, vec.size());
    return std::vector<T>(vec.begin() + static_cast<std::ptrdiff_t>(start),
                          vec.begin() + static_cast<std::ptrdiff_t>(end));
}

/**
 * @brief Computes the sum of all elements in a numeric container.
 * @tparam Container Iterable numeric container.
 * @param c Container of numbers.
 * @return Sum of all elements (or `0` if empty).
 * @code
 * int total = easy::sum(std::vector<int>{10, 20, 30}); // 60
 * @endcode
 */
template <typename Container>
inline auto sum(const Container& c) {
    using ValueType = typename Container::value_type;
    return std::accumulate(std::begin(c), std::end(c), ValueType{0});
}

/**
 * @brief Computes the arithmetic mean (average) of a numeric container as a `double`.
 * @tparam Container Iterable numeric container.
 * @param c Container of numbers.
 * @return Average as `double` (returns `0.0` if container is empty).
 * @code
 * double avg = easy::average(std::vector<int>{10, 20, 30}); // 20.0
 * @endcode
 */
template <typename Container>
inline double average(const Container& c) {
    if (std::begin(c) == std::end(c)) return 0.0;
    double total = 0.0;
    std::size_t count = 0;
    for (const auto& item : c) {
        total += static_cast<double>(item);
        ++count;
    }
    return total / static_cast<double>(count);
}

/**
 * @brief Returns the minimum element in a non-empty container.
 * @tparam Container Iterable container.
 * @param c Container to inspect.
 * @return Minimum value (throws `std::invalid_argument` if empty).
 */
template <typename Container>
inline auto min_val(const Container& c) {
    if (std::begin(c) == std::end(c)) {
        throw std::invalid_argument("easy::min_val called on empty container");
    }
    return *std::min_element(std::begin(c), std::end(c));
}

/**
 * @brief Returns the maximum element in a non-empty container.
 * @tparam Container Iterable container.
 * @param c Container to inspect.
 * @return Maximum value (throws `std::invalid_argument` if empty).
 */
template <typename Container>
inline auto max_val(const Container& c) {
    if (std::begin(c) == std::end(c)) {
        throw std::invalid_argument("easy::max_val called on empty container");
    }
    return *std::max_element(std::begin(c), std::end(c));
}

/**
 * @brief Filters a vector, keeping only elements that satisfy `predicate`.
 * @tparam T Element type.
 * @tparam Pred Callable taking `const T&` and returning `bool`.
 * @param vec Input vector.
 * @param predicate Filter condition.
 * @return New `std::vector<T>` with matching elements.
 * @code
 * auto evens = easy::filter(nums, [](int x) { return x % 2 == 0; });
 * @endcode
 */
template <typename T, typename Pred>
inline std::vector<T> filter(const std::vector<T>& vec, Pred predicate) {
    std::vector<T> out;
    std::copy_if(vec.begin(), vec.end(), std::back_inserter(out), predicate);
    return out;
}

/**
 * @brief Transforms each element of a vector using `fn` and returns the new vector.
 * @tparam T Input element type.
 * @tparam Func Callable transforming `const T&`.
 * @param vec Input vector.
 * @param fn Transformation function.
 * @return New vector of transformed elements.
 * @code
 * auto squares = easy::map_vec(nums, [](int x) { return x * x; });
 * @endcode
 */
template <typename T, typename Func>
inline auto map_vec(const std::vector<T>& vec, Func fn) {
    using OutType = decltype(fn(vec.front()));
    std::vector<OutType> out;
    out.reserve(vec.size());
    for (const auto& elem : vec) {
        out.push_back(fn(elem));
    }
    return out;
}

/**
 * @brief Combines two vectors element-by-element into a vector of pairs (up to the shorter length).
 * @tparam T1 First vector element type.
 * @tparam T2 Second vector element type.
 * @param a First vector.
 * @param b Second vector.
 * @return `std::vector<std::pair<T1, T2>>` of paired elements.
 */
template <typename T1, typename T2>
inline std::vector<std::pair<T1, T2>> zip(const std::vector<T1>& a, const std::vector<T2>& b) {
    std::size_t n = std::min(a.size(), b.size());
    std::vector<std::pair<T1, T2>> out;
    out.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        out.emplace_back(a[i], b[i]);
    }
    return out;
}

// ============================================================================
// 5. MAP & SET HELPERS
// ============================================================================

/**
 * @brief Checks if a key exists in a `std::map` or `std::unordered_map`.
 * @tparam MapType Map container type.
 * @tparam KeyType Key type.
 * @param m Map to search.
 * @param key Key to look up.
 * @return `true` if `key` exists in `m`, `false` otherwise.
 * @code
 * if (easy::has_key(scores, "Alice")) { ... }
 * @endcode
 */
template <typename MapType, typename KeyType>
inline bool has_key(const MapType& m, const KeyType& key) {
    return m.find(key) != m.end();
}

/**
 * @brief Retrieves a value from a map by key, or returns `default_val` if the key does not exist.
 * @tparam MapType Map container type.
 * @tparam KeyType Key type.
 * @tparam ValType Fallback value type.
 * @param m Map to query.
 * @param key Key to look up.
 * @param default_val Fallback value returned when `key` is missing.
 * @return Value associated with `key` or `default_val`.
 * @code
 * int pts = easy::get_or(scores, "Bob", 0);
 * @endcode
 */
template <typename MapType, typename KeyType, typename ValType>
inline typename MapType::mapped_type get_or(const MapType& m, const KeyType& key, const ValType& default_val) {
    auto it = m.find(key);
    if (it != m.end()) return it->second;
    return static_cast<typename MapType::mapped_type>(default_val);
}

/**
 * @brief Extracts all keys from a map into a `std::vector`.
 * @tparam MapType Map container type.
 * @param m Map to extract keys from.
 * @return `std::vector` of keys.
 */
template <typename MapType>
inline std::vector<typename MapType::key_type> keys(const MapType& m) {
    std::vector<typename MapType::key_type> out;
    out.reserve(m.size());
    for (const auto& [k, _] : m) {
        out.push_back(k);
    }
    return out;
}

/**
 * @brief Extracts all values from a map into a `std::vector`.
 * @tparam MapType Map container type.
 * @param m Map to extract values from.
 * @return `std::vector` of values.
 */
template <typename MapType>
inline std::vector<typename MapType::mapped_type> values(const MapType& m) {
    std::vector<typename MapType::mapped_type> out;
    out.reserve(m.size());
    for (const auto& [_, v] : m) {
        out.push_back(v);
    }
    return out;
}

// ============================================================================
// 6. MATH, NUMBER & RANDOM UTILITIES
// ============================================================================

namespace detail {
inline std::mt19937& rng() {
    thread_local std::mt19937 gen(std::random_device{}());
    return gen;
}
} // namespace detail

/**
 * @brief Generates a random integer in the inclusive range `[min_val, max_val]`.
 * @tparam IntType Integral type (default: `int`).
 * @param min_val Minimum possible value (inclusive).
 * @param max_val Maximum possible value (inclusive).
 * @return Random integer in `[min_val, max_val]`.
 * @code
 * int dice = easy::rand_int(1, 6);
 * @endcode
 */
template <typename IntType = int>
inline IntType rand_int(IntType min_val, IntType max_val) {
    if (min_val > max_val) std::swap(min_val, max_val);
    std::uniform_int_distribution<IntType> dist(min_val, max_val);
    return dist(detail::rng());
}

/**
 * @brief Generates a random floating-point number in `[min_val, max_val)`.
 * @tparam RealType Floating-point type (default: `double`).
 * @param min_val Minimum value (default: `0.0`).
 * @param max_val Maximum value (default: `1.0`).
 * @return Random floating-point number.
 * @code
 * double p = easy::rand_float(0.0, 100.0);
 * @endcode
 */
template <typename RealType = double>
inline RealType rand_float(RealType min_val = 0.0, RealType max_val = 1.0) {
    if (min_val > max_val) std::swap(min_val, max_val);
    std::uniform_real_distribution<RealType> dist(min_val, max_val);
    return dist(detail::rng());
}

/**
 * @brief Generates a random boolean with a given probability of being `true`.
 * @param probability_true Probability in `[0.0, 1.0]` (default: `0.5`).
 * @return `true` or `false` randomly.
 */
inline bool rand_bool(double probability_true = 0.5) {
    std::bernoulli_distribution dist(std::clamp(probability_true, 0.0, 1.0));
    return dist(detail::rng());
}

/**
 * @brief Picks a random element from a non-empty vector.
 * @tparam T Element type.
 * @param vec Non-empty vector to pick from.
 * @return Copy of the randomly chosen element.
 * @code
 * auto winner = easy::choice(players);
 * @endcode
 */
template <typename T>
inline T choice(const std::vector<T>& vec) {
    if (vec.empty()) {
        throw std::invalid_argument("easy::choice called on empty vector");
    }
    return vec[rand_int<std::size_t>(0, vec.size() - 1)];
}

/**
 * @brief Randomly shuffles a vector in-place and returns a reference to it.
 * @tparam T Element type.
 * @param vec Vector to shuffle.
 * @return Reference to `vec`.
 */
template <typename T>
inline std::vector<T>& shuffle_vec(std::vector<T>& vec) {
    std::shuffle(vec.begin(), vec.end(), detail::rng());
    return vec;
}

/**
 * @brief Clamps a value to stay within `[low, high]`.
 * @tparam T Comparable type.
 * @param val Value to clamp.
 * @param low Lower bound.
 * @param high Upper bound.
 * @return Clamped value.
 */
template <typename T>
inline constexpr T clamp_val(T val, T low, T high) {
    return (val < low) ? low : ((val > high) ? high : val);
}

/**
 * @brief Linearly interpolates between `a` and `b` by factor `t` in `[0.0, 1.0]`.
 * @param a Start value.
 * @param b End value.
 * @param t Interpolation factor.
 * @return Interpolated value `a + t * (b - a)`.
 */
inline constexpr double lerp(double a, double b, double t) {
    return a + t * (b - a);
}

/**
 * @brief Re-maps a number from one range `[in_min, in_max]` to another `[out_min, out_max]` (like Arduino's `map()`).
 * @param val Input value.
 * @param in_min Lower bound of current range.
 * @param in_max Upper bound of current range.
 * @param out_min Lower bound of target range.
 * @param out_max Upper bound of target range.
 * @return Remapped value as `double`.
 * @code
 * double pct = easy::remap(512, 0, 1023, 0.0, 100.0);
 * @endcode
 */
inline constexpr double remap(double val, double in_min, double in_max, double out_min, double out_max) {
    if (in_max == in_min) return out_min;
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
 * @brief Checks if an integer is even.
 * @tparam IntType Integral type.
 * @param n Number to test.
 * @return `true` if `n` is divisible by 2.
 */
template <typename IntType>
inline constexpr bool is_even(IntType n) {
    return (n % 2) == 0;
}

/**
 * @brief Checks if an integer is odd.
 * @tparam IntType Integral type.
 * @param n Number to test.
 * @return `true` if `n` is not divisible by 2.
 */
template <typename IntType>
inline constexpr bool is_odd(IntType n) {
    return (n % 2) != 0;
}

/**
 * @brief Checks if an integer `n` is a prime number in $O(\sqrt{n})$ time.
 * @param n Integer to check.
 * @return `true` if `n` is prime, `false` otherwise.
 * @code
 * bool p = easy::is_prime(97); // true
 * @endcode
 */
inline constexpr bool is_prime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

/**
 * @brief Computes the factorial $n!$ of a non-negative integer.
 * @param n Non-negative integer ($0 \le n \le 20$).
 * @return $n!$ as `unsigned long long`.
 */
inline constexpr unsigned long long factorial(unsigned int n) {
    unsigned long long res = 1;
    for (unsigned int i = 2; i <= n; ++i) res *= i;
    return res;
}

/**
 * @brief Computes the greatest common divisor (GCD) of two integers.
 * @param a First integer.
 * @param b Second integer.
 * @return Greatest common divisor of `a` and `b`.
 */
inline constexpr long long gcd(long long a, long long b) {
    return std::gcd(a, b);
}

/**
 * @brief Computes the least common multiple (LCM) of two integers.
 * @param a First integer.
 * @param b Second integer.
 * @return Least common multiple of `a` and `b`.
 */
inline constexpr long long lcm(long long a, long long b) {
    return std::lcm(a, b);
}

/**
 * @brief Rounds a floating-point value to `decimals` decimal places.
 * @param val Value to round.
 * @param decimals Number of decimal places (default: `2`).
 * @return Rounded `double`.
 * @code
 * double price = easy::round_to(3.14159, 2); // 3.14
 * @endcode
 */
inline double round_to(double val, int decimals = 2) {
    double factor = std::pow(10.0, decimals);
    return std::round(val * factor) / factor;
}

/**
 * @brief Checks if two floating-point numbers are approximately equal within `epsilon`.
 * @param a First value.
 * @param b Second value.
 * @param epsilon Tolerance threshold (default: `1e-9`).
 * @return `true` if `|a - b| <= epsilon`.
 */
inline bool approx_equal(double a, double b, double epsilon = 1e-9) {
    return std::fabs(a - b) <= epsilon;
}

// ============================================================================
// 7. FILE I/O ONE-LINERS
// ============================================================================

/**
 * @brief Reads the entire contents of a text file into a `std::string`.
 * @param path File path to read.
 * @return File content as `std::string` (returns `""` if file cannot be opened).
 * @code
 * std::string content = easy::read_file("config.txt");
 * @endcode
 */
inline std::string read_file(const std::string& path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file) return "";
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

/**
 * @brief Reads all lines of a text file into a `std::vector<std::string>`.
 * @param path File path to read.
 * @return Vector of lines (without trailing newline characters).
 * @code
 * auto lines = easy::read_lines("data.txt");
 * @endcode
 */
inline std::vector<std::string> read_lines(const std::string& path) {
    std::vector<std::string> lines;
    std::ifstream file(path);
    if (!file) return lines;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        lines.push_back(std::move(line));
    }
    return lines;
}

/**
 * @brief Writes a string to a file (overwriting any existing content).
 * @param path Target file path.
 * @param content Text content to write.
 * @return `true` if write succeeded, `false` otherwise.
 * @code
 * easy::write_file("output.txt", "Hello file!");
 * @endcode
 */
inline bool write_file(const std::string& path, std::string_view content) {
    std::ofstream file(path, std::ios::out | std::ios::trunc | std::ios::binary);
    if (!file) return false;
    file.write(content.data(), static_cast<std::streamsize>(content.size()));
    return file.good();
}

/**
 * @brief Appends a string to the end of a file.
 * @param path Target file path.
 * @param content Text content to append.
 * @return `true` if append succeeded, `false` otherwise.
 */
inline bool append_file(const std::string& path, std::string_view content) {
    std::ofstream file(path, std::ios::out | std::ios::app | std::ios::binary);
    if (!file) return false;
    file.write(content.data(), static_cast<std::streamsize>(content.size()));
    return file.good();
}

/**
 * @brief Checks if a file or directory exists at the specified path.
 * @param path File or directory path.
 * @return `true` if the path exists on disk.
 */
inline bool file_exists(const std::string& path) {
    std::error_code ec;
    return std::filesystem::exists(path, ec);
}

// ============================================================================
// 8. TIMING, SLEEP & BENCHMARKING
// ============================================================================

/**
 * @brief Pauses execution of the current thread for `ms` milliseconds.
 * @param ms Duration to sleep in milliseconds.
 * @code
 * easy::sleep_ms(250); // Sleep for 0.25 seconds
 * @endcode
 */
inline void sleep_ms(long long ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

/**
 * @brief Pauses execution of the current thread for `seconds` seconds (supports fractional seconds).
 * @param seconds Duration to sleep in seconds.
 * @code
 * easy::sleep_sec(1.5);
 * @endcode
 */
inline void sleep_sec(double seconds) {
    auto duration = std::chrono::duration<double>(seconds);
    std::this_thread::sleep_for(duration);
}

/**
 * @brief Returns the current Unix epoch timestamp in milliseconds.
 * @return Milliseconds since Unix epoch (`int64_t`).
 */
inline std::int64_t now_ms() {
    auto now = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
}

/**
 * @brief Measures how many milliseconds a callable `fn` takes to execute.
 * @tparam Func Callable with no parameters.
 * @param fn Function or lambda to benchmark.
 * @return Elapsed wall-clock time in milliseconds (`double`).
 * @code
 * double ms = easy::measure_ms([&]() { heavy_computation(); });
 * @endcode
 */
template <typename Func>
inline double measure_ms(Func&& fn) {
    auto t0 = std::chrono::high_resolution_clock::now();
    fn();
    auto t1 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}

// ============================================================================
// 9. SAFE TYPE CONVERSIONS
// ============================================================================

/**
 * @brief Converts any streamable value into a `std::string`.
 * @tparam T Value type supporting `operator<<`.
 * @param val Value to convert.
 * @return String representation of `val`.
 * @code
 * std::string s = easy::to_str(3.14); // "3.14"
 * @endcode
 */
template <typename T>
inline std::string to_str(const T& val) {
    std::ostringstream oss;
    oss << val;
    return oss.str();
}

/**
 * @brief Safely converts a string to an `int`, returning `default_val` if parsing fails.
 * @param s Input string view.
 * @param default_val Fallback value on error (default: `0`).
 * @return Parsed `int` or `default_val`.
 * @code
 * int x = easy::to_int("123", -1); // 123
 * int y = easy::to_int("abc", -1); // -1 (no exception thrown!)
 * @endcode
 */
inline int to_int(std::string_view s, int default_val = 0) {
    std::string trimmed = trim(s);
    if (trimmed.empty()) return default_val;
    try {
        std::size_t idx = 0;
        int val = std::stoi(trimmed, &idx);
        return (idx == trimmed.size()) ? val : default_val;
    } catch (...) {
        return default_val;
    }
}

/**
 * @brief Safely converts a string to a `double`, returning `default_val` if parsing fails.
 * @param s Input string view.
 * @param default_val Fallback value on error (default: `0.0`).
 * @return Parsed `double` or `default_val`.
 */
inline double to_double(std::string_view s, double default_val = 0.0) {
    std::string trimmed = trim(s);
    if (trimmed.empty()) return default_val;
    try {
        std::size_t idx = 0;
        double val = std::stod(trimmed, &idx);
        return (idx == trimmed.size()) ? val : default_val;
    } catch (...) {
        return default_val;
    }
}

} // namespace easy

#endif //CPP_SIMPLIFIED_HPP
