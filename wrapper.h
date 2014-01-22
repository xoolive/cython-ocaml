#include <cstdlib> // NULL pointer

class Wrapper
{

private:
  void* mydata;
  double(*mydistance)(void*, void*);
  int idx;

public:
  Wrapper(void* data) : mydata(data), mydistance(NULL) {}
  void setDistanceFct( double(*fct)(void*, void*) ) { mydistance = fct; }
  double distance (const Wrapper&) const;

};

// Important algorithm which needs a specific structure wrapping an object of
// unknown type
void f(const Wrapper& s, const Wrapper& t);
