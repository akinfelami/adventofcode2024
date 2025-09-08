#include <cstddef>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;
int p1() {
  ifstream file("input.txt");
  int ct = 0;

  vector<string> all_text;
  // positive lookahead regex
  regex xmas("(?=(XMAS|SAMX)).");

  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      all_text.push_back(line);

      // horizontal matches
      auto xmas_begin = sregex_iterator(line.begin(), line.end(), xmas);
      for (std::sregex_iterator it = xmas_begin; it != sregex_iterator();
           ++it) {
        ct += 1;
      }
    }

    // search vertically
    int horizontal_size = all_text[0].size();
    for (int i = 0; i < horizontal_size; ++i) {
      string col_str;
      for (int j = 0; j < all_text.size(); ++j) {
        col_str += all_text[j][i];
      }
      auto xmas_begin = sregex_iterator(col_str.begin(), col_str.end(), xmas);
      for (std::sregex_iterator it = xmas_begin; it != sregex_iterator();
           ++it) {
        ct += 1;
      }
    }

    // search diagonally (main diagonal: top-left to bottom-right)
    for (int i = 0; i < all_text.size() + (horizontal_size - 1); ++i) {
      string diag_str;
      for (int j = 0; j < all_text.size(); ++j) {
        int col = i - j;
        if (col >= 0 && col < horizontal_size) {
          diag_str += all_text[j][col];
        }
      }
      auto xmas_begin = sregex_iterator(diag_str.begin(), diag_str.end(), xmas);
      for (std::sregex_iterator it = xmas_begin; it != sregex_iterator();
           ++it) {
        ct += 1;
      }
    }

    // other diagonal (anti-diagonal: top-right to bottom-left)
    for (int i = 0; i < all_text.size() + (horizontal_size - 1); ++i) {
      string anti_diag_str;
      for (int j = 0; j < horizontal_size; ++j) {
        int row = i - (horizontal_size - 1 - j);
        if (row >= 0 && row < all_text.size()) {
          anti_diag_str += all_text[row][j];
        }
      }
      auto xmas_begin =
          sregex_iterator(anti_diag_str.begin(), anti_diag_str.end(), xmas);
      for (std::sregex_iterator it = xmas_begin; it != sregex_iterator();
           ++it) {
        ct += 1;
      }
    }

    cout << ct;
  } else {
    cout << "Unable to open file";
  }
  return 0;
}

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
