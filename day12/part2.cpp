#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

struct node {
  size_t row;
  size_t col;
  char val;
};

vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void compute_perimeter(vector<vector<node>> &grid, int row, int col,
                       int &perimeter, char val) {
  if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size()) {
    perimeter += 1;
    return;
  }
  if (grid[row][col].val != val) {
    perimeter += 1;
  }
}

void dfs(vector<vector<node>> &grid, int row, int col,
         vector<vector<bool>> &visited, char val, int &perimeter, int &area,
         int &sides, int prev_row, int prev_col, vector<bool> &visited_rows,
         vector<bool> &visited_cols) {
  if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size() ||
      visited[row][col]) {
    return;
  }
  if (grid[row][col].val != val) {
    return;
  }
  area += 1;
  visited[row][col] = true;

  if (!visited_rows[row] || !visited_cols[col]) {
    sides += 1;
  }
  visited_rows[row] = true;
  visited_cols[col] = true;

  for (auto &dir : directions) {
    int newRow = row + dir[0];
    int newCol = col + dir[1];
    dfs(grid, newRow, newCol, visited, val, perimeter, area, sides, row, col,
        visited_rows, visited_cols);
  }
}

int p2() {
  ifstream file("input.txt");
  vector<vector<node>> graph;
  unordered_set<char> plots;
  if (file.is_open()) {
    string line;
    size_t row = 0;
    while (getline(file, line)) {
      istringstream iss(line);
      char c;
      vector<node> nodes;
      size_t col = 0;
      while (iss.get(c)) {
        node n = node{row, col, c};
        nodes.push_back(n);
        col++;
      }
      row++;
      graph.push_back(nodes);
    }
    unordered_map<char, pair<int, int>> props;
    size_t rows = graph.size();
    size_t cols = graph[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    int total = 0;
    for (size_t i = 0; i < graph.size(); i++) {
      for (size_t j = 0; j < graph.size(); j++) {
        node this_node = graph[i][j];
        if (!visited[i][j]) {
          int perimeter = 0;
          int sides = 0;
          int area = 0;
          size_t prev_row = 0;
          size_t prev_col = 0;
          vector<bool> visited_rows(rows, false);
          vector<bool> visited_cols(cols, false);
          dfs(graph, i, j, visited, this_node.val, perimeter, area, sides,
              prev_row, prev_col, visited_rows, visited_cols);
          cout << "area for " << this_node.val << " " << area << endl;
          cout << "sides for " << this_node.val << " " << sides << endl;
          total += (area * sides);
          cout << endl;
        }
      }
    }
    cout << total << endl;
  } else {
    cout << "Unable to open file" << endl;
  }

  return 0;
}
int main() {
  p2();
  return 0;
}
