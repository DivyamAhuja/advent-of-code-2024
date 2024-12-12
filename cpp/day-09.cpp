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
#include <algorithm>
#include <optional>

class Block
{
public:
    Block() = delete;
    Block(size_t len) : _len(len) {}
    Block(size_t len, int64_t id) : _len(len), _id(id) {}

    auto len() const noexcept { return this->_len; }
    auto id() const noexcept { return this->_id.value(); }
    bool empty() const noexcept { return not this->_id.has_value(); }

private:
    size_t _len;
    std::optional<int64_t> _id;
};

auto part_one(const std::string &input) -> int64_t
{
    int64_t checksum = 0;
    std::vector<Block> disk;
    for (size_t i = 0; i < input.size(); i++)
    {
        const auto len = static_cast<size_t>(input[i] - '0');
        if (i % 2 == 0)
        {
            const auto id = static_cast<int64_t>(i / 2);
            for (size_t j = 0; j < len; j++)
            {
                disk.emplace_back(1, id);
            }
        }
        else
        {
            for (size_t j = 0; j < len; j++)
            {
                disk.emplace_back(1);
            }
        }
    }
    size_t first = 0;
    size_t last = disk.size() - 1;
    while (true)
    {
        while (first < disk.size() and not disk[first].empty())
            first++;
        while (0 < last && disk[last].empty())
            last--;
        if (last < first)
            break;
        std::swap(disk[first], disk[last]);
    }
    for (size_t i = 0; i < disk.size(); i++)
    {
        if (not disk[i].empty())
        {
            checksum += disk[i].id() * i;
        }
    }
    return checksum;
}

auto part_two(const std::string &input) -> int64_t
{
    int64_t checksum = 0;
    std::vector<Block> disk;
    for (size_t i = 0; i < input.size(); i++)
    {
        const auto len = static_cast<size_t>(input[i] - '0');
        if (len == 0)
            continue;
        if (i % 2 == 0)
        {
            const auto id = static_cast<int64_t>(i / 2);
            disk.emplace_back(len, id);
        }
        else
        {
            disk.emplace_back(len);
        }
    }
    size_t last = disk.size() - 1;
    while (0 < last)
    {
        size_t first = 0;
        while (0 < last && disk[last].empty())
            last--;
        while (first <= last)
        {
            if (disk[first].empty() and disk[last].len() <= disk[first].len())
                break;
            first++;
        }
        if (last < first)
        {
            last--;
            continue;
        }
        const auto len = static_cast<int64_t>(disk[first].len() - disk[last].len());
        disk[first] = disk[last];
        disk[last] = Block(disk[first].len());
        if (len > 0)
        {
            disk.emplace(disk.begin() + first + 1, len);
            last++;
        }
    }

    size_t index = 0;
    for (size_t i = 0; i < disk.size(); i++)
    {
        for (size_t j = 0; j < disk[i].len(); j++)
        {
            if (not disk[i].empty())
                checksum += disk[i].id() * index;
            index++;
        }
    }
    return checksum;
}

auto main() -> int
{

    std::string input;
    std::getline(std::cin, input);

    std::cout << "Part 1: " << part_one(input) << std::endl;
    std::cout << "Part 2: " << part_two(input) << std::endl;

    return 0;
}