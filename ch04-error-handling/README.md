# A Tour of C++

## Chapter 4: Error Handling

A positive consequence of using C++'s language constructs is the ability to
separate the location where an error is detected from the location in which it
is handled. Developing a strategy for error catching is a good step in the
early design of a program.

## Exceptions

Consider the case where a user attempts to subset a vector at an index not in
the vector. We would want to **`throw`** an exception. This `throw` transfers
control to the handler of whatever **`exception`** is thrown. This handler is
expressed through the **`catch`** clause of a **`try...catch`** statement:

```cpp
void f(Vector &v)
{
    try
    {
        compute(v); // may access element outside v
    }
    catch (const out_of_range &err)
    {
        // handle instances where element does not exist in v's range
    }
}
```

Exception-handling mechanisms helps make error handling simpler, more
systematic, and easier to read. To that end, avoid overuse of `try` statements,
and allow error catching to occur further up in the stack, as is often
possible. In well designed code, try blocks are rare. Avoiding overuse can be
achieved by using the RAII technique, introduced in chapter 5.

## Invariants

When creating a function, it is a good idea to note its preconditions and
whether or not to test them. When a condition is assumed to be true, the
statement about that condition is known as an **invariant**.

Invariants provide several benefits:

- They help developers understand precisely what they want
- They force developers to be specific, giving the code a better chance of
  being correct.

The _constructor's_ role is to _establish_ the variant for a class. The _member
functions_ must ensure the invariant still holds before they exit.

In our Vector definitions, the following is "valid":

```cpp
// Initialize a size -27 vector
Vector v(-27); // Who knows what will happen?
```

Instead, it would be better to not allow such construction, by establishing
the invariant.
