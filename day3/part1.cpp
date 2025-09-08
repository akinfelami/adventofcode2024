#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() {
  ifstream file("input.txt");

  std::string all_text;

  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      all_text += line;
    }
    file.close();
    std::regex mulRegex(R"rgx(mul\d+,\d+)\rgx");
    auto regex_matches =
        std::sregex_iterator(all_text.begin(), all_text.end(), mulRegex);
    auto match_end = std::sregex_iterator();
    vector<std::string> all_matches;
    for (std::sregex_iterator i = regex_matches; i != match_end; ++i) {
      all_matches.push_back((*i).str().substr(4));
    }
    int sum = 0;
    for (int i = 0; i < all_matches.size(); ++i) {
      std::vector<int> toks;
      std::string token;
      std::istringstream iss(all_matches[i]);
      while (std::getline(iss, token, ",")) {
        // std::cout << token << "\n";
        toks.push_back(std::stoi(token));
      }
      sum += toks[0] * toks[1];
    }
    std::cout << sum;

  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}