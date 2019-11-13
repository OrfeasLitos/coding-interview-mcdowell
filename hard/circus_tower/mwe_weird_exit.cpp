#include <iostream>
#include <vector>

class A {
  public:
    int x;
};

int main() {
  A a;
  std::vector<A> vec;
  vec.push_back(a);
  a.x = 4;
  std::cout << vec[0].x << std::endl;
  // TODO: understand why if next line is around, line 16 works as expected
  //exit(1);
}
