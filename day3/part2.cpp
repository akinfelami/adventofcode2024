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
    std::regex mulRegexDoDont(R"rgx(mul(\d+,\d+)|don't()|do())rgx");
    auto regex_matches =
        std::sregex_iterator(all_text.begin(), all_text.end(), mulRegexDoDont);
    auto match_end = std::sregex_iterator();
    vector<std::string> all_matches;
    for (std::sregex_iterator i = regex_matches; i != match_end; ++i) {
      all_matches.push_back((*i).str());
    }

    bool seen_dont = false;
    int sum = 0;
    for (int i = 0; i < all_matches.size(); i++) {
      // std::cout << all_matches[i] << std::endl;
      if (!(all_matches[i].compare("don't()" )))
{
        seen_dont = true;
        continue;
      }
      if (!(all_matches[i].substr(0, 3).compare("mul")) && seen_dont) {
        continue;
      }

      if (!(all_matches[i].compare("do()" )))
{
        seen_dont = false;
        continue;
      }

      std::vector<int> toks;
      std::string token;
      std::istringstream iss(all_matches[i].substr(4));
      while (std::getline(iss, token, ",")) {
        toks.push_back(std::stoi(token));
      }
      std::cout << toks[0] << "*" << toks[1] << "\n";
      sum += toks[0] * toks[1];
    }
    std::cout << sum;

  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}