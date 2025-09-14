#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;

int main() {
  ifstream file("input.txt");
  vector<pair<int, int>> pos;
  vector<pair<int, int>> vels;
  int wide = 101;
  int tall = 103;
  regex re(R"(p=(-?\d+),(-?\d+)\s+v=(-?\d+),(-?\d+))");
  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      smatch match;
      if (regex_search(line, match, re)) {
        pos.push_back({stoi(match[1].str()), stoi(match[2].str())});
        vels.push_back({stoi(match[3].str()), stoi(match[4].str())});
      }
    }
    int walkSize = (int)pos.size();
    vector<vector<int>> tiles(tall, vector<int>(wide, 0));
    int ct = 0;
    while (true) {
      ct++;
      for (int j = 0; j < walkSize; j++) {
        int posX = pos[j].first;
        int posY = pos[j].second;
        if (tiles[posY][posX] != 0) {
          tiles[posY][posX]--;
        }
        int diff1 = (posX + vels[j].first) % wide;
        pos[j].first = diff1 < 0 ? wide + diff1 : diff1;
        int diff2 = (posY + vels[j].second) % tall;
        pos[j].second = diff2 < 0 ? tall + diff2 : diff2;
        tiles[pos[j].second][pos[j].first]++;
      }
      int cnt = 0;
      for (int i = 0; i < tall; i++) {
        for (int j = 0; j < wide; j++) {
          if (j< wide-1-j && tiles[j][i] > 0 && tiles[wide-1-j][i] > 0) {
            cnt++;
          }
        }
      }
      if (cnt >= 50) {
        cout << "--------- iteration  " << ct << endl;
        for (int i = 0; i < tiles.size(); i++) {
          for (int j = 0; j < tiles[0].size(); j++) {
            if (tiles[i][j] > 0) {
              cout << 'X';
            } else {
              cout << " ";
            }
          }
          cout << endl;
        }
      }
    }
  } else {
    cout << "Unable to open file" << endl;
  }

  return 0;
}