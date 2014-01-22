#include "mysample.h"
#include <iostream>


double Sample::distance(const Sample& s) const { return 1.; }

void f(const Sample& s, const Sample& t)
{
  std::cout << "call f " << s.distance(t) << std::endl;
}
