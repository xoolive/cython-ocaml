## Cythonize OCaml functions

I could not find any tutorial or sample snippets for wrapping OCaml functions
in Python. Here is my contribution:

- `factorial.ml` contains the code to be wrapped. Here you find yet another
tail-recursive implementation of the factorial. The `Callback.register` enables
the code to be called from Python.

- `mlfact.{c,h}` contains the stub for wrapping the factorial function into C.
This part is well documented. Note you *must* have a `caml_startup` somewhere
in the file, otherwise, the link edition will fail. Besides, the `caml_startup`
is usually called in the `main` function of the C program. Here I just build
a fake `argv` and will call this `init()` function at the loading of my Python
module.

- `fact.pyx` is the regular Cython file for wrapping the factorial function. Do
not forget the call to `init`. If you do forget it, you will get a segfault
when you call the factorial function.

Then compile everything:
```
ocamlopt -output-obj -o fact_ml.o factorial.ml
gcc -c -fPIC -I`ocamlc -where` mlfact.c
cython fact.pyx
gcc -c -fPIC `python-config --includes` fact.c
gcc -shared -o fact.so fact_ml.o mlfact.o fact.o `python-config --libs` `ocamlc -where`/libasmrun.a
```

Then inside Python:
```
>>> import fact
>>> fact.fact(6)
720
```

> Note the importance, according to your platform (esp. with x86-64) to have
`libasmrun.a` compiled with `-fPIC`.
