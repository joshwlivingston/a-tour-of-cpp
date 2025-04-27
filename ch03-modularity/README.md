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

As of _C++23_, `module std` is part of the standard.

## Namespaces
