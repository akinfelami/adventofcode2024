#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void attempt_to_move(int dot_pos, int right_pos, vector<string> &nums,
                     int count) {
  int n = nums.size();
  while (dot_pos < (right_pos - count + 1)) {
    if (nums[dot_pos] == ".") {
      int k = dot_pos;
      int number_of_free_space = 0;
      while (k < n && nums[k] == ".") {
        k++;
        number_of_free_space++;
      }
      if (number_of_free_space >= count) {
        // move it
        for (int moved = 0; moved < count; ++moved) {
          nums[dot_pos + moved] = nums[right_pos - moved];
          nums[right_pos - moved] = ".";
        }
        dot_pos += count;
        right_pos -= count;
        return;
      } else {
        dot_pos = k;
      }
    } else {
      dot_pos++;
    }
  }
}
int main() {
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
    int left_number_pos = numbers.size() - 1;
    while (left_number_pos >= 0) {
      if (numbers[left_number_pos] != ".") {
        int l = left_number_pos;
        string left_number = numbers[left_number_pos];
        int count = 0;
        while (numbers[l] == left_number) {
          l--;
          count += 1;
        }
        // find a spot for it.
        attempt_to_move(0, left_number_pos, numbers, count);
        left_number_pos -= count;
      } else {
        left_number_pos--;
      }
    }
    unsigned long long total = 0ULL;
    for (size_t i = 0; i < numbers.size(); i++) {
      string num = numbers[i];
      if (num != ".") {
        unsigned long long number = (unsigned long long)(stoi(num));
        total += (unsigned long long)(i)*number;
      }
    }
    cout << total;
    cout << endl;
  } else {
    cout << "Unable to open file" << endl;
  }

  return 0;
}