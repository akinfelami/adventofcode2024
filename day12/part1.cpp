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

int p1() {
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
          int area = 0;
          // dfs(graph, i, j, visited, this_node.val, perimeter, area);
          total += (perimeter * area);
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
    p1();
    return 0;
}
