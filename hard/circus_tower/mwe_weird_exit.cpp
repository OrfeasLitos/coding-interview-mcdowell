#include <iostream>
#include <vector>
#include <map>

class A {
  public:
    int x = 4;
    int y;
};

class B {
  public:
    std::map<int, int> a_map;

    B(std::vector<A *> vec) {
      std::cout << vec[0]->x << '\n';
    };
};

void func(B b) {}

int main() {
  std::vector<A> vec {A()};
  std::vector<A *> pt_vec {};
  for (A el: vec) {
    pt_vec.push_back(&el);
  }
  auto b = B(pt_vec);
  // TODO: understand why if next line is around, line 16 works as expected
  exit(1);
  func(b);
}
