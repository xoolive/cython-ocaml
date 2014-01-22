""" This module provides a function "test" which will call the f function
    implemented in the cpp. This f function uses the distance function which
    should be implemented by the class of objects a and b.
"""

cdef extern from "wrapper.h":
    cdef cppclass Wrapper:
        Wrapper(void*)
        void setDistanceFct( double(*fct)(void*, void*) )
        double distance(Wrapper)
    cdef void f(Wrapper, Wrapper)

# This is the interesting part of the snippet
# ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

cdef double c_distance(void* pta, void* ptb) :
  cdef object a = <object>(pta)
  cdef object b = <object>(ptb)
  assert("distance" in dir(a))
  assert("distance" in dir(b))
  cdef double dst = <double>a.distance(b)
  return dst

# End of the interesting part

def test(a, b):
    """ Call function test on two objects implementing the method distance. """
    ptr_a = <void *> a
    ptr_b = <void *> b
    cdef Wrapper* sa = new Wrapper(ptr_a)
    cdef Wrapper* sb = new Wrapper(ptr_b)
    sa.setDistanceFct(c_distance)
    sb.setDistanceFct(c_distance)

    f(sa[0], sb[0])
    f(sb[0], sa[0])

