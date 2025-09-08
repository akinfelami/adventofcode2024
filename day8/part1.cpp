#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream file("input.txt");
    vector<vector<char>> grid;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            char c;
            vector<char> freqs;
            while (iss.get(c)) {
                freqs.push_back(c);
            }
            grid.push_back(freqs);
        }
        int antinodes = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                char freq = grid[i][j];
                if (isupper(freq) || islower(freq) || isdigit(freq)) {
                    for (int k = i + 1; k < grid.size(); k++) {
                        for (int r = 0; r < grid[0].size(); r++) {
                            char other_freq = grid[k][r];
                            if (freq == other_freq) {
                                int row_diff = k - i;
                                int col_diff = r - j;
                                // UP
                                if (i - row_diff >= 0 &&
                                    j - col_diff < grid[0].size()) {
                                    if (grid[i - row_diff][j - col_diff] !=
                                        '#') {
                                        if (grid[i - row_diff][j - col_diff] ==
                                            '.')
                                            grid[i - row_diff][j - col_diff] =
                                                '#';
                                        antinodes += 1;
                                    }
                                }

                                // Down
                                if (k + row_diff < grid.size() &&
                                    r + col_diff < grid[0].size()) {
                                    if (grid[k + row_diff][r + col_diff] !=
                                        '#') {
                                        if (grid[k + row_diff][r + col_diff] ==
                                            '.')
                                            grid[k + row_diff][r + col_diff] =
                                                '#';

                                        antinodes += 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        cout << antinodes << endl;
    } else {
        cout << "Unable to open file" << endl;
    }

    return 0;
}