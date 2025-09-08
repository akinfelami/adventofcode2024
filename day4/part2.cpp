#include <cstddef>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;

int p2() {
  ifstream file("input.txt");
  int ct = 0;
  vector<vector<char>> mtrx;
  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      vector<char> line_chars;
      for (size_t k = 0; k < line.size(); k++) {
        line_chars.push_back(line[k]);
      }
      mtrx.push_back(line_chars);
    }
    size_t sz = mtrx.size();
    // for each char form an X;
    for (size_t k = 0; k < sz; k++) {
      for (size_t j = 0; j < sz; j++) {
        if (k + 2 >= sz || j + 2 >= sz || j < 0) {
          continue;
        }
        string major_diag = "";
        string minor_diag = "";
        for (size_t i = 0; i < 3; i++) {
          major_diag += mtrx[k + i][j + i];
        }
        for (size_t i = 0; i < 3; i++) {
          minor_diag += mtrx[k + i][j + 2 - i];
        }
        if ((major_diag == "MAS" || major_diag == "SAM") &&
            (minor_diag == "MAS" || minor_diag == "SAM")) {
          ct += 1;
        }
      }
    }
    cout << ct;
  } else {
    cout << "Unable to open file";
  }
  return 0;
}

int main() {
    p2();
    return 0;
}
