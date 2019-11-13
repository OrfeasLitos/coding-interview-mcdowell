#include <iostream>
#include <vector>

class A {
  public:
    int x = 4;
    int y;
};

class B {
  public:
    B(std::vector<A *> pt_vec) {
      std::cout << pt_vec[0]->x << std::endl;
    };
};

int main() {
  std::vector<A *> pt_vec;

  A a;
  std::vector<A> vec;
  vec.push_back(a);

  for (A& el: vec) {
    pt_vec.push_back(&el);
  }
  B b = B(pt_vec);
  //exit(1);
}
