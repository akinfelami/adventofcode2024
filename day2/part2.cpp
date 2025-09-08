#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool is_safe(const vector<int> &levels) {
    int diff = levels[1] - levels[0];
    bool incr = diff > 0 ? true : false;
    if (abs(diff) < 1 || abs(diff) > 3) {
        return false;
    }
    for (size_t i = 2; i < levels.size(); ++i) {
        int diff = levels[i] - levels[i - 1];
        if (abs(diff) < 1 || abs(diff) > 3) {
            return false;
        }
        bool state = diff > 0 ? true : false;
        if (incr != state) {
            return false;
        }
    }
    return true;
}

int main() {
    ifstream file("input.txt");
    int safe = 0;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        std::string next;
        std::vector<int> levels;
        while (getline(iss, next, ' ')) {
            levels.push_back(stoi(next));
        }
        if (is_safe(levels)) {
            safe++;
        } else {
            for (size_t i = 0; i < levels.size(); ++i) {
                std::vector<int> vec = levels;
                vec.erase(vec.begin() + i);
                if (is_safe(vec)) {
                    safe++;
                    break;
                }
            }
        }
    }
    std::cout << safe << std::endl;
    file.close();
    return 0;
}
