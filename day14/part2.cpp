#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
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