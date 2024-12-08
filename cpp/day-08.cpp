#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <utility>
#include <regex>
#include <stdint.h>
#include <tuple>
#include <stack>
#include <queue>
#include <functional>

template<typename T, size_t Size>
struct ArrayHash {
    size_t operator()(const std::array<T, Size>& arr) const {
        size_t hash = 0;
        for (size_t i = 0; i < Size; i++) {
            hash ^= std::hash<T>()(arr[i]);
        }
        return hash;
    }
};

template<typename T, size_t Size>
std::array<T, Size> operator+(const std::array<T, Size>& a, std::array<T, Size>& b) {
    std::array<T, Size> res;
    for (size_t i = 0; i < Size; i++) {
        res[i] = a[i] + b[i];
    } 
    return res;
}

template<typename T, size_t Size>
std::array<T, Size> operator-(const std::array<T, Size>& a, std::array<T, Size>& b) {
    std::array<T, Size> res;
    for (size_t i = 0; i < Size; i++) {
        res[i] = a[i] - b[i];
    } 
    return res;
}


auto part_one(const std::vector<std::string>& input) -> int64_t {
    std::unordered_map<uint8_t, std::vector<std::array<int64_t, 2>>> map;
    std::unordered_set<std::array<int64_t, 2>, ArrayHash<int64_t, 2>> set;
    
    const int64_t n = static_cast<int64_t>(input.size());
    const int64_t m =  n > 0 ? static_cast<int64_t>(input.size()) : 0;

    for (int64_t i = 0; i < n; i++) {
        for (int64_t j = 0; j < m; j++) {
            if (input[i][j] != '.') map[input[i][j]].push_back({i, j});
        }
    }

    auto in_range = [&](const std::array<int64_t, 2>& p) -> bool {
        return 0 <= p[0] and p[0] < n and 0 <= p[1] and p[1] < m; 
    };

    for (auto& [_, v] : map) {
        for (size_t i = 0; i < v.size(); i++) {
            for (size_t j = i + 1; j < v.size(); j++) {
                auto pj = v[j];
                auto pi = v[i];
                auto d = pj - pi;
                auto p1 = pj + d;
                auto p2 = pi - d;
                if (in_range(p1)) set.insert(p1);
                if (in_range(p2)) set.insert(p2);
            }    
        }
    }

    return static_cast<int64_t>(set.size());
}

auto part_two(const std::vector<std::string>& input) -> int64_t {
    std::unordered_map<uint8_t, std::vector<std::array<int64_t, 2>>> map;
    std::unordered_set<std::array<int64_t, 2>, ArrayHash<int64_t, 2>> set;
    
    const int64_t n = static_cast<int64_t>(input.size());
    const int64_t m =  n > 0 ? static_cast<int64_t>(input.size()) : 0;

    for (int64_t i = 0; i < n; i++) {
        for (int64_t j = 0; j < m; j++) {
            if (input[i][j] != '.') map[input[i][j]].push_back({i, j});
        }
    }

    auto in_range = [&](const std::array<int64_t, 2>& p) -> bool {
        return 0 <= p[0] and p[0] < n and 0 <= p[1] and p[1] < m; 
    };

    for (auto& [_, v] : map) {
        for (size_t i = 0; i < v.size(); i++) {
            for (size_t j = i + 1; j < v.size(); j++) {
                auto pj = v[j];
                auto pi = v[i];
                auto d = pj - pi;
                while (in_range(pj)) {
                    set.insert(pj);
                    pj = pj + d;
                }

                while (in_range(pi)) {
                    set.insert(pi);
                    pi = pi - d;
                }
            }    
        }
    }

    return static_cast<int64_t>(set.size());
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