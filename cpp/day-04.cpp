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

auto part_1(std::vector<std::string> &data) -> uint64_t
{
    uint64_t ans = 0;
    const auto n = data.size();
    const std::string to_check = "XMAS";
    auto check = [&] (size_t i, size_t j, int di, int dj) -> bool {
        auto x = i;
        auto y = j;
        for (int i = 0; i < to_check.size(); i++) {
            if (0 <= x and x < data.size() and 0 <= y and y < data[x].size()) {
                if (data[x][y] != to_check[i]) return false;
                x += di;
                y += dj;
            } else return false;
        }
        return true;
    };

    for (size_t i = 0; i < n; i++) {
        auto m = data[i].size();
        for (size_t j = 0; j < m; j++) {
            if (data[i][j] == 'X') {
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        ans += check(i, j, di, dj);
                    }
                }
            }
        }
    }   
    return ans;
}

auto part_2(std::vector<std::string> &data) -> uint64_t
{
    uint64_t ans = 0;
    const auto n = data.size();
    const std::string to_check = "MAS";
    auto check = [&] (int  i, int j) -> bool {
        auto x = i - 1;
        auto y = j - 1;

        for (int d = 0; d <= 2; d++) {
            auto i = x + d;
            auto j = y + d; 
            if (0 <= i and i <= data.size() and 0 <= j and j <= data[i].size()) continue;
            return false;
        }

        for (int d = 0; d <= 2; d++) {
            auto i = x + 2 - d;
            auto j = y + d; 
            if (0 <= i and i <= data.size() and 0 <= j and j <= data[i].size()) continue;
            return false;
        }
        if (data[x+1][y+1] != 'A') return false;
        bool found1 = false, found2 = false;
        if (data[x][y] == 'M' and data[x + 2][y + 2] == 'S') found1 = true;
        if (data[x][y] == 'S' and data[x + 2][y + 2] == 'M') found1 = true;

        if (data[x + 2][y] == 'M' and data[x][y + 2] == 'S') found2 = true;
        if (data[x + 2][y] == 'S' and data[x][y + 2] == 'M') found2 = true;
        
        return found1 and found2;
    };

    for (size_t i = 0; i < n; i++) {
        auto m = data[i].size();
        for (size_t j = 0; j < m; j++) {
            if (data[i][j] == 'A') {
                ans += check(i, j);
            }
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