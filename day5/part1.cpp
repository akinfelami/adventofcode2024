#include <_stdio.h>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
int main() {
  ifstream file("input.txt");
  vector<string> _rules;
  vector<string> _updates;
  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      if (line.empty())
        break;
      _rules.push_back(line);
    }
    while (getline(file, line)) {
      _updates.push_back(line);
    }
    unordered_map<string, vector<string>> rules; // potentially make it a set;
    for (int i = 0; i < _rules.size(); i++) {
      stringstream iss(_rules[i]);
      string tok;
      getline(iss, tok, '|');
      string key = tok;
      getline(iss, tok, '|');
      rules[key].push_back(tok);
    }
    vector<vector<string>> goods;
    for (int i = 0; i < _updates.size(); i++) {
      stringstream iss(_updates[i]);
      string tok;
      vector<string> good;
      while (getline(iss, tok, ',')) {
        good.push_back(tok);
      }
      size_t gd_size = good.size();
      bool _is_good = true;
      for (int i = 0; i < gd_size && _is_good; i++) {
        for (int j = i + 1; j < gd_size; j++) {
          vector<string> _rules_vec = rules[good[i]];
          if (find(_rules_vec.begin(), _rules_vec.end(), good[j]) ==
              _rules_vec.end()) {
            _is_good = false;
            break;
          }
        }
      }
      if (_is_good) {
        goods.push_back(good);
      }
    }
    int s = 0;
    for (int i = 0; i < goods.size(); i++) {
      s += stoi(goods[i][goods[i].size() / 2]);
    }
    cout << s;
  } else {
    cout << "Unable to open file";
  }
  return 0;
}