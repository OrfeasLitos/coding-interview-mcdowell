#include <iostream>
#include <string>

using namespace std;

int main() {
  string big ("a long text");
  string small ("long ");
  if (big.find(small) != string::npos) {
    cout << "yes";
  } else {
    cout << "no";
  }
}
