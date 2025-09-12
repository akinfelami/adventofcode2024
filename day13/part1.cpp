#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

pair<int, int> solve(int a, int b, int c, int d, int e, int f) {
  int det = (a * d) - (b * c);
  if (det == 0) {
    cout << "no solution" << endl;
    return pair(-1, -1);
  }
  if ((e * d - b * f) % det == 0 && (a * f - e * c) % det == 0) {
    int x = (e * d - b * f) / det;
    int y = (a * f - e * c) / det;
    return {x, y};
  } else {
    return {-1, -1};
  }
}

int main() {
  ifstream file("input.txt");
  regex re(R"(X\+(\d+),\s*Y\+(\d+))");
  std::regex re_prize(R"(X=(\d+),\s*Y=(\d+))");
  smatch match;
  vector<pair<int, int>> configs;
  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      if (line.empty()) {
        continue;
      }
      if (regex_search(line, match, re)) {
        if (match.size() == 3) {
          configs.push_back(pair(stoi(match[1].str()), stoi(match[2].str())));
        }
      }
      if (regex_search(line, match, re_prize)) {
        if (match.size() == 3) {
          configs.push_back(pair(stoi(match[1].str()), stoi(match[2].str())));
        }
      }
    }
    int total = 0;
    for (size_t i = 0; i < configs.size(); i += 3) {
      // cout << "Config" << i << endl;
      // cout << "Button A: X+" << configs[i].first << ", Y+"
      //      << configs[i].second << endl;
      // cout << "Button B: X+" << configs[i + 1].first << ", Y+"
      //      << configs[i + 1].second << endl;
      // cout << "Prize: X=" << configs[i + 2].first
      //      << ", Y=" << configs[i + 2].second << endl;
      auto [x, y] = solve(configs[i].first, configs[i + 1].first,
                          configs[i].second, configs[i + 1].second,
                          configs[i + 2].first, configs[i + 2].second);

      // std::cout << "Solution: x = " << x << ", y = " << y << std::endl;
      if (x > 0 && x <= 100 && y > 0 && y <= 100) {
        std::cout << "Solution: x = " << x << ", y = " << y << std::endl;
        total += (x * 3) + y;
      }
    }
    cout << total << endl;
  } else {
    cout << "Unable to open file" << endl;
  }

  return 0;
}