#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <map>

class Acrobat {
  public:
    unsigned int height;
    unsigned int weight;

    Acrobat(unsigned int h, unsigned int w) {
      height = h;
      weight = w;
    }

    friend bool operator <(const Acrobat, const Acrobat);
    friend bool operator ==(const Acrobat, const Acrobat);
    friend std::ostream &operator <<(std::ostream &, const Acrobat &);
};

bool operator <(const Acrobat left, const Acrobat right) {
  return left.height < right.height
      && left.weight < right.weight;
}

bool operator ==(const Acrobat left, const Acrobat right) {
  return left.height == right.height
      && left.weight == right.weight;
}

std::ostream &operator <<(std::ostream &os, const Acrobat &acrobat) {
  os << '(' << acrobat.height << ", " << acrobat.weight << ")";
  return os;
}

class OrderedGraph {
  public:
    std::map<Acrobat*, std::vector<Acrobat*>> adj_list;

    OrderedGraph(std::vector<Acrobat*> members) {
      for (auto& member: members) {
        std::vector<Acrobat*> bigger {};
        for (auto& other: members) {
          if (*member < *other) {
            bigger.push_back(other);
          }
        }
        adj_list[member] = bigger;
        //if (*member == *members[3] || *member == *members[4]) {
        //  std::cout << *(members[3]) << '\n';
        //  std::cout << adj_list[members[3]].size() << '\n';
        //}
      }
    };

    friend std::ostream &operator <<(std::ostream &, const OrderedGraph &);
};

std::ostream &operator <<(std::ostream &os, const OrderedGraph &graph) {
  for (auto const &[member, bigger]: graph.adj_list) {
    os << *member << ": ";
    for (auto neighbor: bigger) {
      os << *neighbor << " ";
    }
    os << '\n';
  }
  return os;
}

unsigned int find_tallest_tower(std::vector<Acrobat*> neighbors, OrderedGraph graph) {
  if (neighbors.empty()) {
    return 1;
  }

  unsigned int res = 0;
  for (auto member: neighbors) {
    for (auto neighbor: neighbors) {
    }
    unsigned int cur = 1 + find_tallest_tower(graph.adj_list[member], graph);
    for (auto neighbor: neighbors) {
    }
    res = (cur > res) ? cur : res;
  }
  return res;
}

unsigned int find_tallest_tower(std::vector<Acrobat> group) {
  std::vector<Acrobat*> pointers_to_group = {};
  for (auto& member: group) {
    pointers_to_group.push_back(&member);
  }
  auto graph = OrderedGraph(pointers_to_group);
  // -1 for top layer that doesn't correspond to a node
  return find_tallest_tower(pointers_to_group, graph) - 1;
}

void test_acrobat() {
  if (Acrobat(3, 3) < Acrobat(3, 4)) {
    throw "less breaks when true";
  }

  if (!(Acrobat(2, 2) < Acrobat(3, 3))) {
    throw "less breaks when false";
  }
}

void test(unsigned int expected, std::vector<Acrobat> gang) {
  unsigned int res = find_tallest_tower(gang);
  if (res != expected) {
    std::cout << "expected " << expected << ", got " << res << '\n';
  }
}

int main() {
  test_acrobat();

  const std::vector<Acrobat> gang {
    Acrobat(65, 100), Acrobat(70, 150), Acrobat(56, 90),
    Acrobat(75, 190), Acrobat(60, 95), Acrobat(68, 110)
  };
  test(6, gang);

  const std::vector<Acrobat> gang2 {
    Acrobat(1, 10), Acrobat(2, 9), Acrobat(3, 8),
    Acrobat(4, 7), Acrobat(5, 6), Acrobat(6, 5)
  };
  test(1, gang2);

  const std::vector<Acrobat> gang3 {
    Acrobat(1, 1), Acrobat(1, 1), Acrobat(1, 1),
    Acrobat(1, 1), Acrobat(1, 1), Acrobat(1, 1)
  };
  test(1, gang3);

  const std::vector<Acrobat> gang4 {
    Acrobat(1, 1), Acrobat(3, 2), Acrobat(4, 3),
    Acrobat(2, 3), Acrobat(3, 4), Acrobat(4, 5)
  };
  test(4, gang4);
}
