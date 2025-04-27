# A Tour of C++

## Chapter 3: Modularity

The first step in defining the interactions between the various parts of C++
(types, hierarchies, tempaltes) is to clearly distinguish the interface and the
implementation of a program. In C++, interfaces are represented by declarations.

Interface (`sqrt.h`):

```cpp
/* sqrt is a function that takes one double for an argument and returns a
   double */
double sqrt(double);
```

Implementation (`sqrt.cc`):

```cpp
double sqrt(double x)
{
    // sqrt algorithm ...
}
```

## Separate Compilation

C++ supports the notion separate compilation in two ways:

- Declarations can be placed in separate **header files**, and then `#include`
  that header as needed
- Create **modules**, and `import` them as needed, where only the `export`ed
  declarations are seen by the importing code

Separation is used to minimze compile times and enforce logical separations.

A library is often a collection of separately compiled code fragments.

Header files date back to the earliest days of C. **Modules are new to C++20**
and offer "massive advantages."

### Header Files

Programs are best thought of as sets of modules with well-defined dependencies.
Headers files represent that modularity through files and utilize it through
separate compilation.

A `.cc` file compiled by itself is called a **translation unit**.

Usage of header files + `#include` has many disadvantages:

- The text of the `.h` file will be processed by the compiler as many times as
  it is included
- The order in which dependencies are `#include`'d may effect the meaning of
  the included code
- Inconsistencies resulting in crashes or subtle errors can result from
  declaration of an entity in multiple locations
- All code needed to express a declaration must be present in that header file,
  leading to code bloat

The use of header files is not ideal, but will continue to live on as it has
been around since the inception of the language; thus, many existing programs
use header files.

### Modules

Modules have several key difference to vectors:

- Modules are compiled once only - (rather than once per translation unit)
- Order of module imports does not matter
- Module imports are not transitive; by importing a module, you gain access to
  that module only, not everything that that module includes

The "Hello, World!" program compiles **10x faster** when using `import std` as
opposed to `#include <iostream>`.

As of C++23, `module std` is part of the standard.

## Namespaces

**Namespaces** express the ideas that the names contained within the namespace
are related and that the names should not clash with other names.

Namespaces are local to the module and do not affect users of modules.

Namespaces are typically used to organize larger program components, such as
libraries.

## Function Arguments and Return Values

Caling a **function** is the "primary and recommended" way of passing
information from one part of a program to another.

Other methods of passing information include global variables and shared state.

**Global variables** ought to be avoided - known source of issues.
**Shared state** should be tightly controlled in a well-defined abstraction,
such as member functions of a class.

### Argument Passing

Key Concerns When Pasing Information:

- Is the object copied shared?
- If the object is shared, is it mutable?
- Is the object moved, leaving an "empty object" behind?

Default behavior in a function is to copy ("pass-by-value"), or we can specify
that we want to refer to the object in the caller's environment
("pass-by-reference").

### Value Return

Return "by-reference" only when you wish the caller to access something not
local to the function. If you return a reference to a local variable, that
local variable will disappear when the function returns and you will have
problems.

Consider the potential to copy large amounts of data on return:

```cpp
Matrix operator+(const Matrix &x, const Matrix &y)
{
    Matrix res;
    // add the elements ...
    return res;
}
```

Here, the `Matrix` has the potential to be prohibitively large when copied, on
return of the function. So, you instead should define a `move()` operator that
cheaply moves the object out of the function. If `move()` is not defined, many
compilers wil optimize away the copy, a process known as **copy elision**.

The following manual form of memory management _should be avoided_:

```cpp
Matrix  *add(const Matrix &x, const Matrix &y)
{
    Matrix *p = new Matrix;
    // add the elements...
    return p;
}

Matrix *m = add(m1, m2);

delete m; // You're gonna forget this and cause a memory leak let's be real
```

### Return Type Deduction

**`auto`** can be used to deduce the return type of the function or lambda;
however, such use does not promote a stable interface - the implementation
of the function or lambda could change its type.

### Suffix Return Type

The return type comes before the fuinction name for reasons mostly historical -
that's how it works in Fortran, C, and Simula.

In some cases, the argument types must be examined to deduce the type of the
return. For that reason, the return type can be included after the argument
list when we wish to be explicit about the return type.

In such instanced, this means `auto` means "the type will be later determined or
deduced:"

```cpp
auto multiply(int i, double d) -> double { return i * d; }
```

All declarations can be made using this notation, with the added benefit of
better aligning names:

```cpp
auto next_element() -> Element*;
auto exit(init) -> void;
auto sqrt(double) -> double;
```

### Structured Binding

While a function can only return one value, that one value can be a struct,
allowing one to elegantly return many values:

```cpp
struct Entry {
    string name;
    int value;
};

Entry read_entry(istream &is)
{
    string s;
    int i;
    is >> s >> i;
    return {s, i}; // Through return type and {} construction, return an Entry
}


// Read an entry into a single object
auto e = read_entry(cin);
cout << "{" << e.name << ", " << e.value << " }\n";

// Or, we can unpack the object into local variables:
auto [n, v] = read_entry(cin);
cout << "{ " << n << ", " << v << " }\n";
```

The act of assigning members of the `Entry` to local variables is known as
**structured binding**.

When a structured binding is used on a class with no private data members, such
usage is well-defined and trivial. The use of a structured binding does not
not necessarily imply copying, and is meant to be a succicnt expression of an
idea.

## Advice

- Distinguish between **declarations** (interfaces) and **definitions**
  (implementations)
- Prefer modules over headers
- Use header files to represent interfaces and to emphasize logical structure
- `#include` a header in the source file that implements its functions
- Avoid non-inline function definitions in headers
- Use namesapces to express logical structure
- Use `using`-directives for transition, foundational libraries (such as
  `std`), or within a local scope
- Avoid `using`-directives in header files
- Pass "small" values by values and "large" values by reference
- Prefer pass-by-`const`-reference over plain pass-by-reference
- Don't overuse return-type deduction
- Don't overuse structured binding; a named return type often gives more
  readable code
