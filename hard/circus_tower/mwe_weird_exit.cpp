#include <iostream>
#include <vector>
#include <map>

class A {
  public:
    int x;
    int y;
};

class B {
  public:
    std::map<int, int> a_map;

    B(std::vector<A *> vec) {
      std::cout << vec[0]->x << std::endl;
    };
};

void func(B b) {}

int main() {
  A a;
  a.x = 4;
  std::vector<A> vec {a};
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
  func(b);
}
