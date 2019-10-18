#include <iostream>
#include <vector>
#include <string>

using namespace std;

const auto SIZE = 3;

char line_winner(vector<char> line) {
  for (size_t i = 1; i < SIZE; i++) {
    if (line[i] != line[0]) {
      return 'N';
    }
  }
  return line[0];
}

class Board {
  private:
    vector<vector<char>> board;
    char valid_entries[SIZE] = {'O', 'X', ' '};

    vector<char> row(size_t i) {
      if (i >= SIZE || i < 0) {
        throw "bad row number";
      }

      return board[i];
    }

    vector<char> column(size_t i) {
      if (i >= SIZE || i < 0) {
        throw "bad column number";
      }

      // TODO: board.map(row => row[i])
      return vector<char> {board[0][i], board[1][i], board[2][i]};
    }

    vector<char> diagonal(size_t i) {
      if (i >= 2 || i < 0) { // there are only 2 diagonals
        throw "bad diagonal number";
      }

      // TODO: board.map((row, idx) => row[(1-i)*idx + i*(2-idx)])
      return vector<char> {board[0][2*i], board[1][1], board[2][2 - 2*i]};
    }

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
          // TODO: find way to check membership sanely
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
      for (size_t i = 0; i < SIZE; i++) {
        // TODO: DRY
        // for (line of {row, column}) {
        //   auto maybe_winner = line_winner(line(i));
        //   if (maybe_winner != 'N') {
        //     return maybe_winner;
        //   }
        // }
        if (line_winner(row(i)) != 'N') {
          return line_winner(row(i));
        }
        if (line_winner(column(i)) != 'N') {
          return line_winner(column(i));
        }
      }

      for (size_t i = 0; i < 2; i++) {
        if (line_winner(diagonal(i)) != 'N') {
          return line_winner(diagonal(i));
        }
      }
      return line_winner(diagonal(1));
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
      vector<char> {'X', 'O', 'X'},
      vector<char> {'X', 'O', 'X'},
      vector<char> {'X', 'X', ' '}
    });
    if (b.winner() != 'X') {
      throw "fail";
    }

    b = Board(vector<vector<char>> {
      vector<char> {'X', 'O', 'X'},
      vector<char> {'X', 'O', 'X'},
      vector<char> {'O', 'X', 'O'}
    });
    if (b.winner() != 'N') {
      throw "fail";
    }

    b = Board(vector<vector<char>> {
      vector<char> {'O', ' ', ' '},
      vector<char> {' ', 'O', ' '},
      vector<char> {' ', ' ', 'O'}
    });
    if (b.winner() != 'O') {
      throw "fail";
    }
  } catch (string e) {
    cout << e << '\n';
  }
}
