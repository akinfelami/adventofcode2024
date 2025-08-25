#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int p1() {
  ifstream file("input.txt");
  vector<string> all_text;

  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
    }
    all_text.push_back(line);
  } else {
    cout << "Unable to open file";
  }
  return 0;
}

int main() {
  p1();
  return 0;
}
