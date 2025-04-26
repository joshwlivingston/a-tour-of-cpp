# A Tour of C++, 3rd Edition

## Chapter 1: The Basics

## Overview

1. Source files are created
2. Source files are compiled to create object files
3. Object files are linked by a linker
4. Linker returns executable program

A C++ program begins at the function called `main()`.

C++ **functions** specify how an operation is done. Functions cannot be called
unless it is **declared**.

A function **declaration** gives the name, type of return, and number of types
arguments in the call.

## Initialization

Initialization can be done using `=`, and a universal `{}` form. The `{}` form
is recommended.

```cpp
// equivalent
int x = 0;
int y {0};
```

Implicit conversions via `=` cause a lot of problems, and exist for backward
compatibility with C.

Constants cannot be left uninitialized and variables should usually never be
left uninitialized.

The type `auto` can be used when there is no specific reason to mention the
type. In these cases, `=` is appropriate, since implicity conversion is not
troublesome when using auto. Using `auto` avoids redundance and long type
names. `auto` is especially useful in template programming.

Reasons to _not_ use `auto` include:

- The type is in a large scope and thus should be clearly visible.
- The type of the initializer is not obvious.
- We want to be explicit about range or precision (e.g. `double` vs `float`).

## Scope

Three main scopes:

- **Local scope** is declared in a function or lambda. Its scope extends from
  its point of declaration to the end of the **block**, delimitted by `{}`.
- **Class scope** is also called a **member name** if it is defined in a class
  and outside any function, lambda, or enum within the class. Its scope extends
  through the space contained by its containing `{}`.
- **Namespace scope**, aka a **namespace member name**, is defined in a
  `namespace` and outside anf cuntion, lambda, class, or enum. Its scope
  extends from its point of declaration to the closing `}`.
- **Global scope**, or a **global name**, defines anything not local, class, or
  namespace.

Objects can also be unnamed, such as in the case of a pointer to an object
created via `new`.

```cpp
vector<int> vec;                      // global variable
void fct(int arg)                     // global function
{
    string motto {"Who dares wins"};  // local
    auto p = new rec::Record {"Hume"} // local; points to unnamed Record
}
namespace rec {
struct Record {                       // namespace
    string name;                      // member
};
} // namespace red
```

## Constants

C++ support **immutability** in two ways:

- **const** creates a promise to not modify the value, enforced by the
  compiler.
- **constexpr** means "to be evaluted at compile time," and its value _must_ be
  calculated by the compiler.

For a function to be usable in a **constant expression**, it must be defined
`constexpr` or `consteval`.

```cpp
constexpr double square(double x) {return x*x;}

int var = 17;
constexpr double max1 = 1.4*square(17);  // OK: valid constant expression
constexpr double max2 = 1.4*square(var); // Error: var is not a constexpr
const double max3 = 1.4*square(var);     // OK: possibly evaluated at runtime
```

A `constexpr` function can be used for non-constant arguments, and a
non-constant expression results from such a use. When a function should _only_
be used for evaluation at compile time, it should be decalred **consteval**.

`constexpr` and `consteval` are C++'s version of **pure functions**, functions
that produce no side effects and only use the arguments passed to them. More
precisely, pure functions cannot modify non-local variables.

## Pointers, Arrays, References

In delcarations, `[]` means "array of" and `*` means "pointer to". The size of
an array must be a constant expression. When used in declarations these
operators are known as **declarator operators**.

In an expression, prefix unary `*` means "contents of" and prefix unary `&`
means "address of".

Consider printing the contents of an array:

```cpp
void print()
{
    int v1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto i = 0l i != 10; ++i)
        cout << v[i] << '\n';
}
```

C++ **ranges** offer a simpler syntax for for loops:

```cpp
void print2()
    int v1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto x : v)
        cout << x << '\n';
    for (auto x : {1,2,3})
        cout << x << '\n';
```

However, as written, the contents of the array will be copied into x during
each iteration. To avoid copying, you can iterate over references to a range:

```cpp
void increment()
{
    int v1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto &x : v)
        ++x;
}
```

### The Null Pointer

The **nullptr** type, represents the notion of "no object available." It's good
practice to check that a pointer argument is not the `nullptr` (i.e., that it
actually points to something):

```cpp
int count_is_x(const char *p, char x)
    // count the number of occurrences of x in p[]
    // p is assumed to point to a zero-terminated array of char (or to nothing)
{
    if (p == nullptr) // Do not proceed if p points to nothing
        return 0;
    int count = 0;
    while (*p) {      // Iterate across until nullptr is reached
        if (*p == x)
            ++count;
        ++p;
    }
    return count;
}
```

There is no "null reference." A _reference_, as opposed to a _pointer_, must
refer to a valid object.

## Mapping to Hardware

C++ sees a machine's memory as a sequence of memory locations into which
objects can be placed using pointers, much like an array.

### Assignment

An assignment of a built-in type is a simple machine copy operation.

```cpp
int x = 2;
int y = 3; // x != y
x = y;     // x becomes 3; x == y
x = 99;    // x becomes 99; x != y
```

Unlike Java, C#, and other languages, but like C, that changing the value of
`x` does not modify the value of `y` is true for all types, not just ints.

To make two objects refer to the same value, we must say so:

```cpp
int x = 2;
int y = 3;
int *p = &x;
int *q = &y; // p != q & *p != *q
p = q;       // p becomes &y; p == q & *p == *q
```

Assignment to a reference assigns to the referenced object.

```cpp
int x = 2;
int y = 3;
int &r = x;  // r refers to x
int &r2 = y; // r2 refers to y
r = r2;      // read through r2; write through r: x becomes 3
```

## Advice

Taken from the book, the following is a subset of the C++ Core Guidelines.

- Don't panic
- Dont exclusively use built-in features. Many features are best accessed
  through libraries.
- #include or (perferably) import libraries needed
- You don't need to know all of C++ to write good programs
- Focus on programming techniques, not language features
- The ISO C++ standard is the final word on language definition issues
- "Package" meaningful operations as carefully named functions
- A function should perform a single logical operation
- Keep functions short
- User overloading when functions perform conceptually the same task on
  different types
- Use `constexpr` when a function may have to be evaluated at compile time
- Use `consteval` when a function must be evaluated at compile time
- If a function may not have side effects, declare it `constexpr` or
  `consteval`
- Understand how language primitives map up to hardware
- Use digit separators to make large literals readable. (1234567 -> 1'234'567)
- Avoid complicated expressions
- Avoid narrowing conversions
- Minimize the scope of a variable
- Keep scopes small
- Prefer immutable data
- Declare one name (only) per declaration
- Keep common and local names short; keep uncommon and nonlocal names longer
- Avoid similar-looking names
- Avoid ALL_CAPS names
- Prefer the `{}`-initializer syntax for declarations with a named type
- Use `auto` to avoid repeating type names
- Avoid uninitialized variables
- Don't declare a variable until you have a value to initialize it with
- When declaring a variable in the condition of an if-statement, prefer the
  version with the implicity test against `0` or `nullptr`
- Prefer range-for loops over for-loops with an explicit loop variable
- Use `unsigned` for bit manipulation only
- Keep use of pointers simple and straightforward
- Use `nullptr` rather than `0` or `NULL`
- Don't say in comments what can clearly be stated in code
- State intent in comments
- Maintain a consistent indentation style
