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

int p2() {
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
    vector<vector<string>> bad_ones;
    for (int i = 0; i < _updates.size(); i++) {
      stringstream iss(_updates[i]);
      string tok;
      vector<string> bad;
      while (getline(iss, tok, ',')) {
        bad.push_back(tok);
      }
      size_t gd_size = bad.size();
      bool _is_good = true;
      for (int i = 0; i < gd_size && _is_good; i++) {
        for (int j = i + 1; j < gd_size; j++) {
          vector<string> _rules_vec = rules[bad[i]];
          if (find(_rules_vec.begin(), _rules_vec.end(), bad[j]) ==
              _rules_vec.end()) {
            _is_good = false;
            bad_ones.push_back(bad);
            break;
          }
        }
      }
    }
    for (int i = 0; i < bad_ones.size(); i++) {
      for (int k = 0; k < bad_ones[i].size(); k++) {
        for (int j = k + 1; j < bad_ones[i].size(); j++) {
          vector<string> _rules_vec = rules[bad_ones[i][k]];
          if (find(_rules_vec.begin(), _rules_vec.end(), bad_ones[i][j]) ==
              _rules_vec.end()) {
            // this is where it all went wrong - swap and hope
            string tmp = bad_ones[i][k];
            bad_ones[i][k] = bad_ones[i][j];
            bad_ones[i][j] = tmp;
          }
        }
      }
    }
    int s = 0;
    for (int i = 0; i < bad_ones.size(); i++) {
      s += stoi(bad_ones[i][bad_ones[i].size() / 2]);
    }
    cout << s;
  } else {
    cout << "Unable to open file";
  }
  return 0;
}

int main() {
    p2();
    return 0;
}
