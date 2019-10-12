#include <iostream>
#include <string>

using namespace std;

bool is_str_rot(string a, string b) {
  a += a;
  if (a.find(b) != string::npos) {
    return true;
  } else {
    return false;
  }
}

void test(string a, string b, bool expected) {
  try {
    if (is_str_rot(a, b) != expected) {
      throw a;
    }
  } catch (string e) {
    cout << "is_str_rot() fails on \"" << e << "\"\n";
  }
}

int main() {
  string foo = "a long text";
  string bar = "long texta ";

  test(foo, bar, true);

  foo = "b long text";

  test(foo, bar, false);

  cout << "success!\n";
}
