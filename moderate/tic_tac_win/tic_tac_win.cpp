#include <iostream>
#include <vector>
#include <string>

using namespace std;

const auto SIZE = 3;

class Board {
  private:
    vector<vector<char>> board;
    char valid_entries[SIZE] = {'O', 'X', ' '};

  public:
    Board(vector<vector<char>> b) {
      if (b.size() != SIZE) {
        throw "bad size";
      }

      for (auto it = b.begin(); it != b.end(); it++) {
        if (it->size() != SIZE) {
          throw "bad size";
        }
        for (auto jt = it->begin(); jt != it->end(); jt++) {
          if (*jt != valid_entries[0]
             && *jt != valid_entries[1]
             && *jt != valid_entries[2]) {
            throw "bad entry";
          }
        }
      }

      board = b;
    }

    char winner() {
      // TODO
      return 'O';
    }

    void print() {
      for (auto it = board.begin(); it != board.end(); it++) {
        for (auto jt = it->begin(); jt != it->end(); jt++) {
          printf("%c ", *jt);
        }
        printf("\n");
      }
    }
};

int main() {
  try {
    Board b(vector<vector<char>> {
      vector<char> {'O', 'X', 'X'},
      vector<char> {'O', 'X', 'O'},
      vector<char> {'O', 'X', ' '}
    });
    b.print();
    cout << '\n' << b.winner() << '\n';
  } catch (string e) {
    cout << e << '\n';
  }
}
