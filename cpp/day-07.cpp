#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>
#include <unordered_map>
#include <sstream>
#include <utility>
#include <regex>
#include <stdint.h>
#include <tuple>
#include <stack>
#include <queue>
#include <functional>

auto parse(const std::vector<std::string>& input) {
    std::vector<std::pair<int64_t, std::vector<int64_t>>> equations;
    for (auto& eq : input) {
        auto start = eq.find_first_not_of(' ');
        auto end = eq.find(':');
        auto result = std::stoll(eq.substr(start, end - start));
        end += 1;
        std::vector<int64_t> operands;
        while ((start = eq.find_first_not_of(' ', end)) != eq.npos) {
            end = eq.find(' ', start);
            operands.push_back(std::stoll(eq.substr(start, end - start)));
        }
        equations.push_back(make_pair(result, operands));
    }
    return equations;
}

auto part_one(const std::vector<std::string>& input) {
    int64_t ans = 0;
    auto equations = parse(input);
    for (auto& [result, operands] : equations) {
        if (operands.empty()) continue;
        std::function<bool (int64_t, size_t)> possible = [&](int64_t curr, size_t index) -> bool {
            if (index == operands.size()) return curr == result;
            bool can = false;
            can |= possible(curr + operands[index], index + 1);
            can |= possible(curr * operands[index], index + 1);
            return can;
        };
        if (possible(operands[0], 1)) ans += result;
    }
    return ans;
}

auto part_two(const std::vector<std::string>& input) {
    int64_t ans = 0;
    auto equations = parse(input);
    for (auto& [result, operands] : equations) {
        if (operands.empty()) continue;
        std::function<bool (int64_t, size_t)> possible = [&](int64_t curr, size_t index) -> bool {
            if (index == operands.size()) return curr == result;
            bool can = false;
            can |= possible(curr + operands[index], index + 1);
            can |= possible(curr * operands[index], index + 1);
            can |= possible(std::stoll(std::to_string(curr) + std::to_string(operands[index])), index + 1);
            return can;
        };
        if (possible(operands[0], 1)) ans += result;
    }
    return ans;
}

auto main() -> int {
    std::vector<std::string> input;
    std::string line;
    while (std::getline(std::cin, line)) {
        input.push_back(std::move(line));
    }

    std::cout << "Part 1: " << part_one(input) << std::endl;
    std::cout << "Part 2: " << part_two(input) << std::endl;

    return 0;
}