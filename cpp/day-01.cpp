#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>
#include <unordered_map>
#include <sstream>

auto part_1(std::vector<int>& list1, std::vector<int>& list2) -> int {
    std::ranges::sort(list1);
    std::ranges::sort(list2);
    
    int ans = 0;
    for (auto [x, y] : std::views::zip(list1, list2)) {
        ans += std::abs(x - y);
    }
    return ans;
}

auto part_2(std::vector<int>& list1, std::vector<int>& list2) -> int {
    std::unordered_map<int, int> freq;

    for (auto x : list2) freq[x]++;
    int ans = 0;
    for (auto x : list1) ans += x * freq[x];
    return ans;
}

auto main(int argc, char** argv) -> int {
    std::vector<int> list1, list2;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        int in1, in2;
        if (ss >> in1 >> in2) {
            list1.push_back(in1);
            list2.push_back(in2);
        } else {
            break;
        }
    }
    
    std::cout << "Part 1: " << part_1(list1, list2) << std::endl;
    std::cout << "Part 2: " << part_2(list1, list2) << std::endl;
    return 0;
}