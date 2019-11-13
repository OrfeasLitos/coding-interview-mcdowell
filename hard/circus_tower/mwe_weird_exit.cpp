#include <iostream>
#include <vector>
#include <map>

class A {
  public:
    int x;
    int y;
};

int main() {
  A a;
  std::vector<A> vec {a};
  a.x = 4;
  std::vector<A *> pt_vec;
  std::cout << vec[0].x << " " << a.x << std::endl;
  // TODO: understand why if next line is around, line 16 works as expected
  //exit(1);
}
