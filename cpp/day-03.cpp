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

auto part_1(std::string &inst) -> uint64_t
{
    uint64_t ans = 0;
    std::regex word_regex(R"(mul\(\d+,\d+\))");
    auto words_begin = std::sregex_iterator(inst.begin(), inst.end(), word_regex);
    auto words_end = std::sregex_iterator();

    for (auto it = words_begin; it != words_end; it++)
    {
        auto match = it->str();
        long long num1 = 0, num2 = 0;
        int i = 4;
        while (match[i] != ',')
        {
            num1 = num1 * 10 + match[i] - '0';
            i++;
        }
        i++;
        while (match[i] != ')')
        {
            num2 = num2 * 10 + match[i] - '0';
            i++;
        }
        ans += num1 * num2;
    }
    return ans;
}

auto part_2(std::string &inst) -> uint64_t
{
    uint64_t ans = 0;
    std::regex word_regex(R"(mul\(\d+,\d+\)|do\(\)|don't\(\))");
    auto words_begin = std::sregex_iterator(inst.begin(), inst.end(), word_regex);
    auto words_end = std::sregex_iterator();

    bool enabled = true;
    for (auto it = words_begin; it != words_end; it++)
    {
        auto match = it->str();

        if (match == "do()")
        {
            enabled = true;
            continue;
        }
        if (match == "don't()")
        {
            enabled = false;
            continue;
        }
        if (!enabled)
            continue;
        
        int i = 4;
        long long num1 = 0, num2 = 0;
        while (match[i] != ',')
        {
            num1 = num1 * 10 + match[i] - '0';
            i++;
        }
        i++;
        while (match[i] != ')')
        {
            num2 = num2 * 10 + match[i] - '0';
            i++;
        }
        ans += num1 * num2;
    }
    return ans;
}

auto main(int argc, char **argv) -> int
{
    std::string inst;
    std::string line;
    while (std::getline(std::cin, line))
    {
        inst += line;
    }

    std::cout << "Part 1: " << part_1(inst) << std::endl;
    std::cout << "Part 2: " << part_2(inst) << std::endl;
    return 0;
}