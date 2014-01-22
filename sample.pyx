cdef extern from "mysample.h":
    cdef cppclass Sample:
        Sample(void*)
        double distance(Sample)
    cdef void f(Sample, Sample)

def test(a, b):
    ptr_a = <void *> a
    ptr_b = <void *> b
    f(Sample(ptr_a), Sample(ptr_b))

