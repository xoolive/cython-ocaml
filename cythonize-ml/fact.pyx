cdef extern from "mlfact.h":
    void init()
    int ml_fact "factorial" (int)

init()

def fact(int a):
    return ml_fact(a)
