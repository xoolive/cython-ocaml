#include <stdlib.h>
#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/callback.h>

#include "mlfact.h"
/*
  ocamlopt -output-obj -o fact_ml.o factorial.ml
  gcc -c -fPIC -I`ocamlc -where` mlfact.c
  cython fact.pyx
  gcc -c -fPIC `python-config --includes` fact.c
  gcc -shared -o fact.so fact_ml.o mlfact.o fact.o `python-config --libs` `ocamlc -where`/libasmrun.a
 */

void init() {
  static char* argv[1] = {"python"};
  caml_startup(argv);
}

int factorial(int i)
{
  static value * factorial_closure = NULL;
  if (factorial_closure == NULL) {
    factorial_closure = caml_named_value("factorial");
  }
  return Int_val(caml_callback(*factorial_closure, Val_int(i)));
}
