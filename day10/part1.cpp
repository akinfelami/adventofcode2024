#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct node {
  size_t row;
  size_t col;
  char val;
};

vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
void dfs(vector<vector<node>> &grid, int row, int col,
         vector<vector<bool>> &visited, string &path, int &trailheads) {
  if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size() ||
      visited[row][col]) {
    return;
  }

  if (!path.empty()) {
    if (grid[row][col].val != path.back() + 1) {
      return;
    }
  }

  path += grid[row][col].val;
  visited[row][col] = true;
  if (grid[row][col].val == '9') {
    if (path == "0123456789") {
      trailheads += 1;
    }
    path.pop_back();
    return;
  }
  for (auto &dir : directions) {
    int newRow = row + dir[0];
    int newCol = col + dir[1];
    dfs(grid, newRow, newCol, visited, path, trailheads);
  }
  path.pop_back();
}

int main() {
  ifstream file("input.txt");
  vector<vector<node>> graph;
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
    int trailheads = 0;
    for (size_t i = 0; i < graph.size(); i++) {
      for (size_t j = 0; j < graph.size(); j++) {
        if (graph[i][j].val == '0') {
          int rows = graph.size();
          int cols = graph[0].size();
          vector<vector<bool>> visited(rows, vector<bool>(cols, false));
          string pth = "";
          dfs(graph, i, j, visited, pth, trailheads);
        }
      }
    }
    cout << trailheads << endl;
  } else {
    cout << "Unable to open file" << endl;
  }

  return 0;
}