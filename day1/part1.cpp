#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

int main() {
    std::ifstream file("input.txt");
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq_left;
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq_right;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::size_t l = line.find_first_of(" ");
            std::size_t r = line.find_last_of(" ");
            int left = std::stoi(line.substr(0, l));
            int right = std::stoi(line.substr(r));

            pq_left.push(left);
            pq_right.push(right);
        }
        int sum = 0;
        while (!pq_left.empty()) {
            sum += std::abs(pq_left.top() - pq_right.top());
            pq_left.pop();
            pq_right.pop();
        }
        std::cout << sum << std::endl;
        file.close();
    } else {
        std::cout << "Unable to open file";
    }
    return 0;
}