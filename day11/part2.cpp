#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std;

int p2() {
  ifstream file("input.txt");
  if (file.is_open()) {
    string line;
    unordered_map<string, long long> global_map;
    getline(file, line);
    string num;
    istringstream iss(line);
    while (getline(iss, num, ' ')) {
      global_map[num] += 1;
    }
    for (int j = 0; j < 75; j++) {
      unordered_map<string, long long> freqs;
      for (const auto &pair : global_map) {
        string n = pair.first;
        if (n == "0") {
          freqs["1"] += pair.second;
        } else if (!(n.size() & 1)) {
          size_t siz = n.size();
          string left = n.substr(0, siz / 2);
          string right = n.substr(siz / 2);
          right.erase(0, right.find_first_not_of('0'));
          if (right.empty())
            right = "0";
          freqs[left] += pair.second;
          freqs[right] += pair.second;
        } else {
          long long new_num = stol(n) * 2024;
          freqs[to_string(new_num)] += pair.second;
        }
      }
      global_map = freqs;
    }
    long long count = 0;
    for (const auto &pair : global_map) {
      count += pair.second;
    }
    cout << count << endl;
  } else {
    cout << "Unable to open file" << endl;
  }

  return 0;
}

int main() {
  p2();
  return 0;
}
