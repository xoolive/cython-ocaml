extern "C" {
#  include <caml/memory.h>
#  include <caml/mlvalues.h>
#  include <caml/callback.h>
}

#include "wrapper.h"

static value* closure_f = NULL;

/*
 * The type definition in `mlwrapper.ml` ensures the call to caml_callback2 is
 * valid and properly typed
 */
double c_distance (void* pta, void* ptb) {
  value* v_a = (value*) pta;
  value* v_b = (value*) ptb;
  return Double_val(caml_callback2(*closure_f, *v_a, *v_b));
}

extern "C"
value MlTest(value v_a, value v_b, value v_dist)
{
  CAMLparam3(v_a, v_b, v_dist);

  closure_f = &v_dist;

  Wrapper sa(&v_a);
  Wrapper sb(&v_b);

  sa.setDistanceFct(c_distance);
  sb.setDistanceFct(c_distance);

  f(sa, sb);

  CAMLreturn(Val_unit);
}
