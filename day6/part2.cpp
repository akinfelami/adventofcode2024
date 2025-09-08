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

int p2() {
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
    vector<tuple<int, int>> empty_spots;
    size_t map_size = map.size();
    size_t row_size = map[0].size();
    CURRENT_FACE current_face = UP;

    // empty spots
    for (int i = 0; i < map_size; i++) {
      for (int j = 0; j < row_size; j++) {
        if (map[i][j] == '.') {
          empty_spots.push_back({i, j});
        }
      }
    }

    int starting_pos_row = -1;
    int starting_pos_col = -1;
    bool found = false;
    for (int i = 0; i < map_size && !found; i++) {
      for (int j = 0; j < row_size; j++) {
        if (map[i][j] == '^') {
          starting_pos_row = i;
          starting_pos_col = j;
          found = true;
          break;
        }
      }
    }

    int positions = 0;

    for (int i = 0; i < empty_spots.size(); i++) {
      // mark this empty spot as #
      vector<vector<char>> pseudo_map = map;
      unordered_set<state> visited;
      pseudo_map[get<0>(empty_spots[i])][get<1>(empty_spots[i])] = '#';

      int guard_row = starting_pos_row;
      int guard_col = starting_pos_col;
      current_face = UP;

      while ((current_face == UP && (guard_row > 0)) ||
             (current_face == DOWN && (guard_row < map_size - 1)) ||
             (current_face == RIGHT && (guard_col < row_size - 1)) ||
             (current_face == LEFT && (guard_col > 0))) {

        // loop detection
        state guard_state = state{guard_row, guard_col, current_face};

        if (visited.find(guard_state) != visited.end()) {
          positions += 1;
          break;
        }

        visited.insert(guard_state);

        switch (current_face) {
        case UP:
          if (pseudo_map[guard_row - 1][guard_col] == '#') {
            current_face = RIGHT;
          } else {
            pseudo_map[guard_row][guard_col] = 'X';
            guard_row -= 1;
          }
          break;
        case DOWN:
          if (pseudo_map[guard_row + 1][guard_col] == '#') {
            current_face = LEFT;
          } else {
            pseudo_map[guard_row][guard_col] = 'X';
            guard_row += 1;
          }
          break;
        case LEFT:
          if (pseudo_map[guard_row][guard_col - 1] == '#') {
            current_face = UP;
          } else {
            pseudo_map[guard_row][guard_col] = 'X';
            guard_col -= 1;
          }
          break;
        case RIGHT:
          if (pseudo_map[guard_row][guard_col + 1] == '#') {
            current_face = DOWN;
          } else {
            pseudo_map[guard_row][guard_col] = 'X';
            guard_col += 1;
          }
          break;
        }
      }
    }
    cout << positions << endl;
  } else {
    cout << "Unable to open file";
  }
  return 0;
}

int main() {
    p2();
    return 0;
}
