# A Tour of C++

## Chapter 2: User-Defined Types

Types that can be built from the fundamental types, the `const` modifier, and
the declarator operators, are known as **built-in types**. C++ built-in types
are rich, but intentionally low-level. C++ augments built-in types with
**abstraction mechanisms**, designed primaryly to let developers design and
implement their own types, known as **user-defined types**. These types are
referred to as **classes** and **enumerations**.

User-defined types are generally preferred over built-in types, noting several
key advantages:

- Easier to use
- Less error prone
- Typically as efficient, or even more efficient, than built-in types

Chapter 2 presents the fundamental tools and concepts used in defining and
using types.

Chapter 4-8 provide a more thorough description of the available abstraction
mechanisms.

Chapters 9-17 covers the standard library, oh which user-defined types form the
backbone.

## Structures

**Structures** define aribtrary data types. You can define functions for
structures; however, you are limited in how to connect the functions to the
structure. `.` accesses a member through the struct's name. `->` accesses
members through a pointer to the struct.

## Classes

With **classes**, you can link member functions directly to the structure. The
interface of a class is defined by its **public** members, and its **private**
members are accessible only through that public interface.

There is no major difference between a _struct_ and a _class_. A struct is
a class with its members set to _public_ by default.

## Enumerations

An **enum** allows us to _enumerate_ the values.

```cpp
enum class Color {red, blue, green};
enum class TrafficLight light = TrafficLight::red;

Color col = Color::red;
TrafficLight light = TraficLight::red;
```

`enum`'s store `int`'s by default in the underlying data structure. However,
implicity conversion from an `int` to an `enum` is not allowed:

```cpp
Color c = 2; // Error: 2 is not a color
```

To store an integer in an enum, you can do so explicitly:

```cpp
Color x = Color{5}; // OK, but verbose
Color y {6};        // OK
```

By default, an `enum` has assignment, initialization, and comparison operators.
Since `enum`'s are a user-defined type, however, operators can be defined:

```cpp
TrafficLight &operator++(TrafficLight &t)
{
    switch (t) {
        case TrafficLight::green  : return t = TrafficLight::yellow;
        case TrafficLight::yellow : return t = TrafficLight::red;
        case TrafficLight::red    : return t = TrafficLight::green;
    }
}
```

You can also specify types within the scope:

```cpp
TrafficLight &operator++(TrafficLight &t)
{
    using enum TrafficLight;
    switch (t) {
        case green  : return t = yellow;
        case yellow : return t = red;
        case red    : return t = green;
    }
}
```

If you don't want to explicitly wualify `enum` names, and want the `enum`
values to be ints, drop the `class` from the declaration:

```cpp
enum Color {red, green, blue};
int col = green;               // col == 1
```

## Unions

A **union** is a struct in which all members are allocated to the same address.
The union will only ever occupy as much space as its largest member. A union
only holds the value of one member at a time. Consider a table entry that can
be either a `Node*` or an `int`:

```cpp
enum class Type { ptr, num };

struct Entry {
    string name;
    Type t;
    Value v;
};

union Value {
    Node *p;
    int i;
}
```

Here, `Value::p` and `Value::i` are placed at the same address, and the space
used between them is thus optimized.

However, this usage of a `union` is error-prone. When union-like functionality
is desired, two options are conventional:

1. Encapsulate the union and type in a class, and provide access to the data
   only through member functions.
2. Use the standard library's `variant` type:

```cpp
struct Entry {
    string name;
    variant<Node*, int> v;
};

void f(Entry *pe)
{
    if (holds_alternative<int>(pe->v)) // does *pe hold an int?
        cout << get<int>(pe->v);       // get the int
}
```

## Advice

- Prefer well-defined user-defined types over built-in types when the built-in
  types are too low-level.
- Organize related data into structures (`struct`s or `class`es)
- Represent the distinction between an interface and an implementation using a `class`
- A `struct` is simply a `class` with its members `public` be default
- Define constructors to guarantee and simplify initialization of `class`es
- Use enumerations to represent sets of named constants
- Prefer `class enum`s over "plain" `enums` to minimize surprises
- Define operations on enumerations for safe and simple user
- Avoid "naked" `union`s; wrap `union`s with a type field in a `class`
- Prefer `std::variant` to "naked `union`s`"
