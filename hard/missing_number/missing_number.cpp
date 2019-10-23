#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <math.h>

using namespace std;

class BitwiseArray {
  private:
    vector<size_t> numbers;

  public:
    BitwiseArray(size_t max, size_t missing) {
      numbers = {};
      for (size_t i = 0; i <= max; i++) {
        if (i != missing) {
          numbers.push_back(i);
        }
      }
      random_shuffle(numbers.begin(), numbers.end());
    }

    // get the j-th bit of the i-th number (both 0-indexed)
    size_t get(size_t i, size_t j) {
      return (numbers[i] >> j) & 1;
    }

    void print() {
      for (auto i: numbers) {
        cout << i << ' ';
      }
      cout << '\n';
    }

    // deliberately not providing getter
    void print(size_t i) {
      if (i < 0 || i > numbers.size()) {
        throw "out of bounds";
      }

      cout << numbers[i];
    }
};

// for each bit position, starting from LSB and with the full array,
// group elements based on their bit. The missing number has at this
// position a bit equal to that of the group with the least elements.
// In the next iteration apply the above to the smallest group. Repeat
// for as many bits as needed to represent n.
size_t find_missing_number(BitwiseArray arr, size_t n) {
  // vector faster than unordered_set...
  vector<size_t> left {};
  vector<size_t> right {};

  vector<size_t> to_check {};
  for (size_t i = 0; i < n; i++) {
    to_check.push_back(i);
  }

  size_t num = 0;

  // total complexity <= n * sum[rank = 0..log2(n)](1/(2^rank)) < 2n

  // iterates at most log2(n) times
  for (size_t rank = 0; rank <= log2(n); rank++) {
    left.clear();
    right.clear();

    // iterates to_check.size() ~== n/(2^rank) times
    for (auto i: to_check) {
      size_t bit = arr.get(i, rank);
      (bit) ? right.push_back(i) : left.push_back(i);
    }

    to_check.clear(); // TODO: figure out if this is redundant
    size_t bit_of_missing = (right.size() < left.size());
    to_check = (bit_of_missing) ? right : left;
    num |= (bit_of_missing << rank);
  }

  return num;
}

int main() {
  srand(unsigned (time(0)));

  for (auto i = 1; i < 300; i++) {
    for (auto j = 0; j <= i; j++) {
      auto b = BitwiseArray(i, j);
      auto res = find_missing_number(b, i);

      if (res != j) {
        cout << "fail at (" << i << ", " << j << "): got " << res << '\n';
      }
    }
  }
}
