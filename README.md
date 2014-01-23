# Smart interface for wrapping complex C++ code

----
## The C++ code to be wrapped

`wrapper.h`
`wrapper.cpp`

----
## For Python/Cython:

Compile the library and test the Python example:

    python setup.py build_ext --inplace
    python test.py

----
## For OCaml:
> You can replace g++ by your favourite (Intel) compiler... More difficult with
python!

Compile the library `wrapper.cmxa`, compile the test and execute it:

    g++ -c wrapper.cpp
    ocamlopt -cc "g++" -c mlcwrapper.c
    ocamlopt -cc "g++" -c mlwrapper.ml
    ocamlopt -cc "g++" -a -o wrapper.cmxa mlwrapper.cmx mlcwrapper.o wrapper.o

    ocamlopt -cc "g++" -c test.ml
    ocamlopt -cc "g++" -o test wrapper.cmxa test.cmx
    ./test
