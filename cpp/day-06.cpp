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
    -> std::tuple<
        std::pair<int, int>,
        std::pair<int, int>,
        std::vector<std::vector<int>>>
{
    auto n = data.size();
    auto m = data.at(0).size();
    int x = 0, y = 0;
    int dx = 0, dy = 0;
    std::vector<std::vector<int>> area(n, std::vector<int>(m, 0));
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (data[i][j] == '#')
            {
                area[i][j] = 2;
            }
            else if (data[i][j] == '^')
            {
                x = i;
                y = j;

                dx = -1;
                dy = 0;
            }
            else if (data[i][j] == '>')
            {
                x = i;
                y = j;

                dx = 0;
                dy = 1;
            }
            else if (data[i][j] == 'v')
            {
                x = i;
                y = j;

                dx = 1;
                dy = 0;
            }
            else if (data[i][j] == '<')
            {
                x = i;
                y = j;

                dx = 0;
                dy = -1;
            }
        }
    }
    return {{x, y}, {dx, dy}, area};
}

auto turn_right(int dx, int dy) -> std::pair<int, int>
{
    if (dx != 0)
    {
        dy = -dx;
        dx = 0;
    }
    else if (dy != 0)
    {
        dx = dy;
        dy = 0;
    }
    return std::make_pair(dx, dy);
}

std::vector<std::pair<int, int>> path;

auto part_1(std::vector<std::string> &data) -> uint64_t
{
    uint64_t ans = 0;
    auto [pos, dir, area] = parse(data);
    auto [x, y] = pos;
    auto [dx, dy] = dir;
    const auto n = area.size();
    const auto m = area.at(0).size();
    while (true)
    {
        auto nx = x + dx;
        auto ny = y + dy;

        area[x][y] = 1;
        if (not(0 <= nx and nx < n and 0 <= ny and ny < m))
            break;

        if (area[nx][ny] > 1)
        {
            std::tie(dx, dy) = turn_right(dx, dy);
        }
        else
        {
            x = nx;
            y = ny;
        }
    }

    for (int i = 0; i < area.size(); i++)
    {
        for (int j = 0; j < area[i].size(); j++)
        {
            if (area[i][j] == 1)
            {
                ans++;
                path.push_back({i, j});
            }
        }
    }

    return ans;
}

auto part_2(std::vector<std::string> &data) -> uint64_t
{
    uint64_t ans = 0;
    auto [pos, dir, area] = parse(data);
    auto [x, y] = pos;
    const auto n = area.size();
    const auto m = area.at(0).size();

    for (auto [i, j] : path)
    {
        if ((i == x and j == y))
            continue;
        area[i][j] = 2;
        std::unordered_set<std::string> visited;
        auto [x, y] = pos;
        auto [dx, dy] = dir;
        bool loop = false;
        while (true)
        {
            auto nx = x + dx;
            auto ny = y + dy;

            area[x][y] = 1;
            if (not(0 <= nx and nx < n and 0 <= ny and ny < m))
                break;

            std::stringstream ss;
            ss << x << " " << dx << " " << y << " " << dy;
            auto edge = ss.str();
            if (visited.find(edge) != visited.end())
            {
                loop = true;
                break;
            }
            visited.insert(edge);

            if (area[nx][ny] > 1)
            {
                std::tie(dx, dy) = turn_right(dx, dy);
            }
            else
            {
                x = nx;
                y = ny;
            }
        }
        if (loop)
            ans += 1;
        area[i][j] = 0;
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