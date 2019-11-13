#include <iostream>
#include <vector>

class A {
  public:
    int x;
    int y;
};

class B {
  public:
    B(std::vector<A *> pt_vec) {
      std::cout << pt_vec[0]->x << std::endl;
    };
};

int main() {
  A a;
  a.x = 4;
  std::vector<A> vec;
  vec.push_back(a);
  std::vector<A *> pt_vec;
  for (A el: vec) {
    pt_vec.push_back(&el);
  }
  std::cout << vec[0].x << std::endl;
  B b = B(pt_vec);
  std::cout << vec[0].x << std::endl;
  // TODO: understand why if next line is around,
  //       previous line works as expected
  //exit(1);
}
