class Sample
{
private:
  void* mydata;
  int idx;
public:
  Sample(void* data) : mydata(data) {}
  double distance (const Sample&) const;
};

void f(const Sample& s, const Sample& t);
