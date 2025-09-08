#include <_stdio.h>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>
using namespace std;

enum CURRENT_FACE { UP, DOWN, LEFT, RIGHT };

struct state {
  int row;
  int col;
  CURRENT_FACE current_face;
  bool operator==(const state &other) const {
    return row == other.row && col == other.col &&
           current_face == other.current_face;
  }
};

// tell the STL how to hash a `state`
namespace std {
template <> struct hash<state> {
  std::size_t operator()(const state &s) const noexcept {
    std::size_t h1 = std::hash<int>()(s.row);
    std::size_t h2 = std::hash<int>()(s.col);
    std::size_t h3 = std::hash<int>()(static_cast<int>(s.current_face));
    return h1 ^ (h2 << 1) ^ (h3 << 2);
  }
};
} // namespace std

int p1() {
  ifstream file("input.txt");
  vector<vector<char>> map;
  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      vector<char> row;
      for (char c : line) {
        row.push_back(c);
      }
      map.push_back(row);
    }
    size_t map_size = map.size();
    size_t row_size = map[0].size();
    int guard_row = -1;
    int guard_col = -1;
    CURRENT_FACE current_face = UP;
    bool found = false;
    for (int i = 0; i < map_size && !found; i++) {
      for (int j = 0; j < row_size; j++) {
        if (map[i][j] == '^') {
          guard_row = i;
          guard_col = j;
          found = true;
          break;
        }
      }
    }
    while ((current_face == UP && (guard_row > 0)) ||
           (current_face == DOWN && (guard_row < map_size - 1)) ||
           (current_face == RIGHT && (guard_col < row_size - 1)) ||
           (current_face == LEFT && (guard_col > 0))) {
      switch (current_face) {
      case UP:
        if (map[guard_row - 1][guard_col] == '#') {
          current_face = RIGHT;
        } else {
          map[guard_row][guard_col] = 'X';
          guard_row -= 1;
        }
        break;
      case DOWN:
        if (map[guard_row + 1][guard_col] == '#') {
          current_face = LEFT;

        } else {
          map[guard_row][guard_col] = 'X';
          guard_row += 1;
        }
        break;
      case LEFT:
        if (map[guard_row][guard_col - 1] == '#') {
          current_face = UP;
        } else {
          map[guard_row][guard_col] = 'X';
          guard_col -= 1;
        }
        break;
      case RIGHT:
        if (map[guard_row][guard_col + 1] == '#') {
          current_face = DOWN;
        } else {
          map[guard_row][guard_col] = 'X';
          guard_col += 1;
        }
        break;
      }
    }
    int count = 1;
    for (int j = 0; j < map.size(); j++) {
      for (int k = 0; k < map[0].size(); k++) {
        cout << map[j][k];
        if (map[j][k] == 'X') {
          count += 1;
        }
      }
      cout << endl;
    }
    cout << count << endl;
  } else {
    cout << "Unable to open file";
  }
  return 0;
}

int main() {
    p1();
    return 0;
}
