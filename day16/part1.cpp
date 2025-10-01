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
enum CURRENT_FACE { UP, DOWN, LEFT, RIGHT };

void dfs(vector<vector<node>>& grid, int row, int col,
         vector<vector<bool>>& visited, int end_row, int end_col, int& points) {
    if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size() ||
        visited[row][col]) {
        return;
    }

    if (row == end_row && col == end_col) {
        return;
    }

    if (grid[row][col].val == '#') {
        return;
    }

    visited[row][col] = true;
    for (auto& dir : directions) {
        int newRow = row + dir[0];
        int newCol = col + dir[1];
        dfs(grid, newRow, newCol, visited, end_row, end_col, points);
    }

    // sometimes it might not find a path
}

int main() {
    ifstream file("input.txt");
    if (file.is_open()) {
        string line;
        vector<vector<node>> graph;
        size_t row = 0;
        pair<size_t, size_t> start;
        pair<size_t, size_t> end;

        while (getline(file, line)) {
            istringstream iss(line);
            char c;
            vector<node> nodes;
            size_t col = 0;
            while (iss.get(c)) {
                if (c == 'S') {
                    start = {row, col};
                } else if (c == 'E') {
                    end = {row, col};
                }
                node n = node{row, col, c};
                nodes.push_back(n);
                col++;
            }
            row++;
            graph.push_back(nodes);
        }
        int rows = graph.size();
        int cols = graph[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        int points = 0;
        dfs(graph, start.first, start.second, visited, end.first, end.second,
            points);
    } else {
        cout << "Unable to open file" << endl;
    }

    return 0;
}