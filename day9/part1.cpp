#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int p1() {
  ifstream file("input.txt");
  if (file.is_open()) {
    string line;
    vector<string> numbers;
    getline(file, line);
    int id = 0;
    for (size_t i = 0; i < line.size(); i++) {
      int curr = line[i] - '0';
      if ((i & 1) == 1) {
        // odd so free space
        while (curr > 0) {
          numbers.push_back(".");
          curr--;
        }
      } else {
        while (curr > 0) {
          numbers.push_back(to_string(id));
          curr--;
        }
        id += 1;
      }
    }
    size_t dot_pos = 0;
    size_t left_number_pos = numbers.size() - 1;
    while (dot_pos < left_number_pos) {
      if (numbers[dot_pos] == ".") {
        if (numbers[left_number_pos] != ".") {
          numbers[dot_pos] = numbers[left_number_pos];
          numbers[left_number_pos] = ".";
          left_number_pos--;
          dot_pos++;
        } else {
          left_number_pos--;
        }
      } else {
        dot_pos++;
      }
    }
    unsigned long long total = 0ULL;
    for (size_t i = 0; i < numbers.size(); i++) {
      string num = numbers[i];
      if (num != ".") {
        unsigned long long number = (unsigned long long)(stoi(num));
        total += (unsigned long long)(i)*number;
      } else {
        break;
      }
    }
    cout << total;
    cout << endl;
  } else {
    cout << "Unable to open file" << endl;
  }

  return 0;
}

int main() {
    p1();
    return 0;
}
