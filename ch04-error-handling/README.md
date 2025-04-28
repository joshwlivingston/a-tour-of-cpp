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
possible.
