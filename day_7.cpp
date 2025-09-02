#include <_stdio.h>

#include <bitset>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

enum operations { add, multiply, concatenation };

int p1() {
  ifstream file("input.txt");

  unordered_map<long, vector<long>> mappings;

  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      string token;
      istringstream iss(line);
      getline(iss, token, ':');
      long key = stol(token);
      getline(iss, token, ':');
      token.erase(0, token.find_first_not_of(' '));
      istringstream token_iss(token);
      vector<long> values;
      while (getline(token_iss, token, ' ')) {
        values.push_back(stol(token));
      }
      mappings[key] = values;
    }
    long valids = 0;
    for (const auto &pair : mappings) {
      long target = pair.first;
      long val_size = pair.second.size() - 1;
      const long combinations_to_try = pow(2, val_size);

      // build combination matrix
      vector<vector<operations>> combinations_grid;
      for (size_t k = 0; k < combinations_to_try; k++) {
        vector<operations> ops;
        string bin = bitset<16>(k).to_string().substr(16 - val_size);
        for (size_t i = 0; i < bin.size(); i++) {
          if (bin[i] == '1') {
            ops.push_back(multiply);
          } else {
            ops.push_back(add);
          }
        }
        combinations_grid.push_back(ops);
      }
      for (size_t i = 0; i < combinations_to_try; i++) {
        long result = pair.second[0];
        for (size_t k = 0; k < combinations_grid[i].size(); k++) {
          switch (combinations_grid[i][k]) {
          case add:
            result += pair.second[k + 1];
            break;
          case multiply:
            result *= pair.second[k + 1];
            break;
          }
        }
        if (result == target) {
          valids += result;
          break;
        }
      }
    }
    cout << valids;

  } else {
    cout << "Unable to open file";
  }
  return 0;
}

string to_base_3(int n, int w) {
  if (n == 0)
    return string(max(1, w), '0');
  string res;
  while (n > 0) {
    res += '0' + (n % 3);
    n /= 3;
  }
  reverse(res.begin(), res.end());
  if (w > res.size())
    res = string(w - res.size(), '0') + res;

  return res;
}

int p2() {
  ifstream file("input.txt");

  unordered_map<long, vector<long>> mappings;

  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      string token;
      istringstream iss(line);
      getline(iss, token, ':');
      long key = stol(token);
      getline(iss, token, ':');
      token.erase(0, token.find_first_not_of(' '));
      istringstream token_iss(token);
      vector<long> values;
      while (getline(token_iss, token, ' ')) {
        values.push_back(stol(token));
      }
      mappings[key] = values;
    }
    long valids = 0;
    for (const auto &pair : mappings) {
      long target = pair.first;
      long val_size = pair.second.size() - 1;
      const long combinations_to_try = pow(3, val_size);

      // build combination matrix
      vector<vector<operations>> combinations_grid;
      for (size_t k = 0; k < combinations_to_try; k++) {
        vector<operations> ops;
        string bin = to_base_3(k, val_size);
        for (size_t i = 0; i < bin.size(); i++) {
          if (bin[i] == '1') {
            ops.push_back(multiply);
          } else if (bin[i] == '0') {
            ops.push_back(add);
          } else {
            ops.push_back(concatenation);
          }
        }
        combinations_grid.push_back(ops);
      }
      for (size_t i = 0; i < combinations_to_try; i++) {
        long result = pair.second[0];
        for (size_t k = 0; k < combinations_grid[i].size(); k++) {
          switch (combinations_grid[i][k]) {
          case add:
            result += pair.second[k + 1];
            break;
          case multiply:
            result *= pair.second[k + 1];
            break;
          case concatenation:
            result = stol(to_string(result) + to_string(pair.second[k + 1]));
            break;
          }
        }
        if (result == target) {
          valids += result;
          break;
        }
      }
    }
    cout << valids;

  } else {
    cout << "Unable to open file";
  }
  return 0;
}

int main() {
  p2();
  return 0;
}
