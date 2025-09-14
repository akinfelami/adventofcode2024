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
        for (int i = 0; i < 10000; i++) {
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
        }
        for (int i = 0; i < tiles.size(); i++) {
            for (int j = 0; j < tiles[0].size(); j++) {
                cout << tiles[i][j];
            }
            cout << endl;
        }
        int quad1 = 0, quad2 = 0, quad3 = 0, quad4 = 0;
        for (int i = 0; i < (tall / 2); i++) {
            for (int j = 0; j < (wide / 2); j++) {
                quad1 += tiles[i][j];
            }
        }
        for (int i = 0; i < (tall / 2); i++) {
            for (int j = wide / 2 + 1; j < wide; j++) {
                quad2 += tiles[i][j];
            }
        }
        for (int i = tall / 2 + 1; i < tall; i++) {
            for (int j = 0; j < wide / 2; j++) {
                quad3 += tiles[i][j];
            }
        }

        for (int i = tall / 2 + 1; i < tall; i++) {
            for (int j = wide / 2 + 1; j < wide; j++) {
                quad4 += tiles[i][j];
            }
        }

        cout << quad1 * quad2 * quad3 * quad4 << endl;
    } else {
        cout << "Unable to open file" << endl;
    }

    return 0;
}