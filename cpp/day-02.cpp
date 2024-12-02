#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>
#include <unordered_map>
#include <sstream>
#include <utility>

auto report_is_valid(const std::vector<int> &report) -> bool
{
    const auto n = static_cast<int>(report.size());
    bool increasing = n > 1 ? report[0] < report[1] : true;
    for (int i = 1; i < n; i++)
    {
        auto diff = report[i] - report[i - 1];
        if (increasing and 1 <= diff and diff <= 3)
            continue;
        if (not increasing and -3 <= diff and diff <= -1)
            continue;
        return false;
    }
    return true;
}

auto part_1(std::vector<std::vector<int>> &data) -> int
{
    int ans = 0;
    for (auto &report : data)
    {
        if (report_is_valid(report))
            ans++;
    }
    return ans;
}

auto part_2(std::vector<std::vector<int>> &data) -> int
{
    int ans = 0;
    for (auto &report : data)
    {
        if (report_is_valid(report))
            ans++;
        else
        {
            for (int index = 0; index < report.size(); index++)
            {
                auto v = std::vector(report);
                v.erase(v.begin() + index);
                if (report_is_valid(v))
                {
                    ans++;
                    break;
                }
            }
        }
    }
    return ans;
}

auto main(int argc, char **argv) -> int
{
    std::vector<std::vector<int>> data;
    std::string line;
    while (std::getline(std::cin, line))
    {
        std::vector<int> report;
        std::stringstream ss(line);
        int in;
        while (ss >> in)
        {
            report.push_back(in);
        }
        data.push_back(std::move(report));
    }

    std::cout << "Part 1: " << part_1(data) << std::endl;
    std::cout << "Part 2: " << part_2(data) << std::endl;
    return 0;
}