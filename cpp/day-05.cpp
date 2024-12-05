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
#include <unordered_set>
#include <stack>
#include <queue>
#include <functional>

auto parse(std::vector<std::string> &data)
    -> std::pair<std::unordered_map<int, std::unordered_set<int>>, std::vector<std::vector<int>>>
{
    std::unordered_map<int, std::unordered_set<int>> rules;
    std::vector<std::vector<int>> updates;
    size_t i = 0;
    while (i < data.size()) {
        if (data[i] == "") {
            break;
        }
        int num1 = 0, num2 = 0;
        size_t j = 0;
        while (j < data[i].size() and data[i][j] != '|') num1 = 10 * num1 + (data[i][j++] - '0');
        j++;
        while (j < data[i].size()) num2 = 10 * num2 + (data[i][j++] - '0');
        rules[num2].insert(num1);
        i++;
    }
    i++;
    while (i < data.size()) {
        int num = 0;
        size_t j = 0;
        std::vector<int> update;
        while (true) {
            if (j == data[i].size() or data[i][j] == ',') {
                update.push_back(num);
                num = 0;
                if (j == data[i].size()) break;
            } else {
                num = 10 * num + (data[i][j] - '0');
            }
            j++;
        }
        updates.push_back(update);
        i++;
    }

    return {std::move(rules), std::move(updates)};
}

auto part_1(std::vector<std::string> &data) -> uint64_t
{
    uint64_t ans = 0;
    auto [rules, updates] = parse(data);
    
    for (auto& update : updates) {
        bool valid = true;
        for (size_t i = 0; i < update.size(); i++) {
            for (size_t j = i + 1; j < update.size(); j++) {
                if (rules[update[i]].find(update[j]) != rules[update[i]].end()) {
                    valid = false;
                    break;
                }
            }
            if (not valid) break;
        }
        if (valid) {
            ans += update[(update.size())/2];
        }
    }
            
    return ans;
}

auto part_2(std::vector<std::string> &data) -> uint64_t
{
    uint64_t ans = 0;
    auto [rules, updates] = parse(data);
    
    for (auto& update : updates) {
        bool valid = true;
        for (size_t i = 0; i < update.size(); i++) {
            for (size_t j = i + 1; j < update.size(); j++) {
                if (rules[update[i]].find(update[j]) != rules[update[i]].end()) {
                    valid = false;
                    break;
                }
            }
            if (not valid) break;
        }
        if (not valid) {
            
            std::vector<int> order;
            std::unordered_set<int> visited, in_update(update.begin(), update.end());
            std::function<void(int)> dfs = [&](int x) {
                if (visited.find(x) != visited.end()) return;
                visited.insert(x);

                for (auto p : rules[x]) {
                    if (in_update.find(p) != in_update.end())
                        dfs(p);
                }
                 order.push_back(x);
            };
            for (size_t i = 0; i < update.size(); i++) {
                if (visited.find(update[i]) == visited.end()) {
                    dfs(update[i]);
                }
            }
            ans += order[(order.size())/2];
        }
    }
        
    return ans;
}

auto main(int argc, char **argv) -> int
{
    std::vector<std::string> data;
    std::string line;
    while (std::getline(std::cin, line))
    {
        data.push_back(line);
    }

    std::cout << "Part 1: " << part_1(data) << std::endl;
    std::cout << "Part 2: " << part_2(data) << std::endl;
    return 0;
}