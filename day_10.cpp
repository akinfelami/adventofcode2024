#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

struct node {
    size_t row;
    size_t col;
    char val;
};

struct NodeHash {
    std::size_t operator()(const node& n) const {
        return std::hash<size_t>()(n.row) ^ (std::hash<size_t>()(n.col) << 1) ^
               (std::hash<char>()(n.val) << 2);
    }
};

struct NodeEqual {
    bool operator()(const node& lhs, const node& rhs) const {
        return lhs.row == rhs.row && lhs.col == rhs.col && lhs.val == rhs.val;
    }
};

void dfs(vector<vector<node>>& mtrx,
         unordered_set<node, NodeHash, NodeEqual>& visited, int s, vector<char> res){
          visited.insert(mtrx[s]);
         }

    int p1() {
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

        for (size_t i = 0; i < graph.size(); i++) {
            for (size_t j = 0; j < graph.size(); j++) {
                if (graph[i][j].val == '9') {
                    deque<node> queue;
                    unordered_set<node, NodeHash, NodeEqual> visited;
                    node this_node = graph[i][j];
                    queue.push_back(this_node);
                    visited.insert(this_node);
                    while (!queue.empty()) {
                        node h = queue.front();
                        cout << h.val << " -> ";
                        queue.pop_front();
                        // up
                        if (h.row > 0) {
                            node up = graph[h.row - 1][h.col];
                            if (visited.find(up) == visited.end()) {
                                queue.push_back(up);
                                visited.insert(up);
                            }
                        }
                        // down
                        if (h.row + 1 < graph.size()) {
                            node down = graph[h.row + 1][h.col];
                            if (visited.find(down) == visited.end()) {
                                queue.push_back(down);
                                visited.insert(down);
                            }
                        }
                        // left
                        if (h.col > 0) {
                            node left = graph[h.row][h.col - 1];
                            if (visited.find(left) == visited.end()) {
                                queue.push_back(left);
                                visited.insert(left);
                            }
                        }
                        // right
                        if (h.col + 1 < graph[0].size()) {
                            node right = graph[h.row][h.col + 1];
                            if (visited.find(right) == visited.end()) {
                                queue.push_back(right);
                                visited.insert(right);
                            }
                        }
                    }
                    cout << endl << endl;
                }
            }
        }

        for (size_t i = 0; i < graph.size(); i++) {
            for (size_t j = 0; j < graph.size(); j++) {
                cout << graph[i][j].val;
            }
            cout << endl;
        }
    } else {
        cout << "Unable to open file" << endl;
    }

    return 0;
}

int main() {
    p1();
    return 0;
}