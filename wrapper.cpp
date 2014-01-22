#include "wrapper.h"
#include <iostream>
#include <cassert>

double Wrapper::distance(const Wrapper& s) const
{
  assert(mydistance != NULL);
  return mydistance(mydata, s.mydata);
}

void f(const Wrapper& s, const Wrapper& t)
{
  std::cout << "cpp call to f and evaluation: " << s.distance(t) << std::endl;
}
