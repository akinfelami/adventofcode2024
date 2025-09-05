#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int p1() {
  ifstream file("input.txt");
  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
    }
  } else {
    cout << "Unable to open file" << endl;
  }

  return 0;
}

int main() {
  p1();
  return 0;
}