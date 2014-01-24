## A proposition of interface for wrapping "complex" C++ code

Let's say you have some smart algorithm requiring a specific data model which
is anything but relevant to the user. However, this data model shall wrap user
data (let's call those *things*), and require the user to implement specific
methods to be applied to these things.

A minimal interface to expose to the user would be:

  * Give me your data;
  * Give me your implementation of this function I need;
  * Let me handle the structures I need and implement the algorithm.

For instance, you want to offer a sorting algorithm. Your algorithm shall not be
type-specific; all it needs is a function comparing *things*. The data in input
shall only be a *list of things* and the output would be sorted *list of
things*.

If you choose to offer an A-star algorithm for finding the shortest path between
two points in a graph, you shall not demand the user to comply to your data
model: all you need is a graph of *things*, a function computing the distance
between two *things*, and a function returning a list of neighbouring *things*;
then the algorithm returns a *path (list) of things*.

A natural way of implementing this need in C++ only would be using templates,
but those cannot be compiled into a library before they are specified.

This snippet suggests a way to implement this need with opaque pointers in
C/C++. Then the simple method (print) requiring a distance method is wrapped
into:

  1. a Python library (Cython), where "things" are classes implementing a
  distance method;
  2. an OCaml library, where "things" are of an undefined type `'a`; and the
  distance is a `'a -> 'a -> float` method.

You are still free to choose the interface. I chose classes with Python, and
lambda functions in OCaml as I like to stick to the philosophy of each language.
The key is that the C++ code **knows nothing of the _thing_, of the language
used, and of the implementation of the required callback**: Python (resp. OCaml)
executes the callback on the data it defined and yields the result to the CPP
code. **Conversely, the user knows nothing of the C++ `Wrapper` class.**

----
### The C++ code to be wrapped

`wrapper.h` defines a class wrapper with an attribute of type `void*` (the
pointer to a "thing"). Another attribute would be a function pointer which is to
be called in the implementation of the `distance` method (in `wrapper.cpp`). Our
smart algorithm here just prints the distance between two "things".

If you want to use the `f` algorithm in C++, you only build a nicer interface,
or just stick to the `Wrapper` thing.

----
### For Python/Cython:

When wrapping the `f` algorithm in cython (becomes `pywrapper.test`), we write
the `pywrapper.pyx` to describe the interface. The part of interest is the
function `cdef double c_distance` which casts back the `void*` "things" to
Python objects, and let Python call the `distance` method of those objects. The
result is explicitly of type `double`.

There is no need to implement any explicit interface in `test.py` so that
`pywrapper.test` can be executed. The only requirement is that our object passed
to the function implements the function `distance`. This requirement is more
flexible than the implementation of an interface, virtual class, etc. as it
avoids multiple inheritance.


Compile the library and test the Python example:

    python setup.py build_ext --inplace
    python test.py

----
### For OCaml:

The `f` algorithm is also wrapped as a `test` function. I like the beauty of the
functional language, where we can explicitly type the interface in
`mlwrapper.ml`: `'a -> 'a -> ('a -> 'a -> float) -> unit` (If you are not
familiar with OCaml, read `'a` as *thing*). This guarantees that line 18 in
`mlcwrapper.c` is valid.

As with the Cython implementation, the `void*` refers to some OCaml value, as
is, and we call the OCaml callback on those OCaml values. The result is then
converted to regular `double` from `C`.


Compile the library `wrapper.cmxa`, compile the test and execute it:

> Cool fact: you can replace g++ by your favourite (Intel?) compiler!

> Less cool fact: do not try with Python if you want to sleep early tonight.

    g++ -c wrapper.cpp
    ocamlopt -cc "g++" -c mlcwrapper.c
    ocamlopt -cc "g++" -c mlwrapper.ml
    ocamlopt -cc "g++" -a -o wrapper.cmxa mlwrapper.cmx mlcwrapper.o wrapper.o

    ocamlopt -cc "g++" -c test.ml
    ocamlopt -cc "g++" -o test wrapper.cmxa test.cmx
    ./test
