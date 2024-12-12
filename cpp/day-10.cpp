#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

using Grid = vector<vector<int>>;

uint64_t dfs_part_one(const Grid &input, set<pair<int, int>> &visited, int i, int j) {
    if (visited.count({i, j})) {
        return 0;
    }
    visited.insert({i, j});

    if (input[i][j] == 9) {
        return 1;
    }

    uint64_t ways = 0;
    if (i > 0 && input[i][j] + 1 == input[i - 1][j]) {
        ways += dfs_part_one(input, visited, i - 1, j);
    }

    if (i < input.size() - 1 && input[i][j] + 1 == input[i + 1][j]) {
        ways += dfs_part_one(input, visited, i + 1, j);
    }

    if (j > 0 && input[i][j] + 1 == input[i][j - 1]) {
        ways += dfs_part_one(input, visited, i, j - 1);
    }

    if (j < input[i].size() - 1 && input[i][j] + 1 == input[i][j + 1]) {
        ways += dfs_part_one(input, visited, i, j + 1);
    }

    return ways;
}

uint64_t part_one(const Grid &input) {
    uint64_t ans = 0;
    for (size_t i = 0; i < input.size(); ++i) {
        for (size_t j = 0; j < input[i].size(); ++j) {
            if (input[i][j] == 0) {
                set<pair<int, int>> visited;
                ans += dfs_part_one(input, visited, i, j);
            }
        }
    }
    return ans;
}

uint64_t dfs_part_two(const Grid &input, int i, int j) {
    if (input[i][j] == 9) {
        return 1;
    }

    uint64_t ways = 0;
    if (i > 0 && input[i][j] + 1 == input[i - 1][j]) {
        ways += dfs_part_two(input, i - 1, j);
    }

    if (i < input.size() - 1 && input[i][j] + 1 == input[i + 1][j]) {
        ways += dfs_part_two(input, i + 1, j);
    }

    if (j > 0 && input[i][j] + 1 == input[i][j - 1]) {
        ways += dfs_part_two(input, i, j - 1);
    }

    if (j < input[i].size() - 1 && input[i][j] + 1 == input[i][j + 1]) {
        ways += dfs_part_two(input, i, j + 1);
    }

    return ways;
}

uint64_t part_two(const Grid &input) {
    uint64_t ans = 0;
    for (size_t i = 0; i < input.size(); ++i) {
        for (size_t j = 0; j < input[i].size(); ++j) {
            if (input[i][j] == 0) {
                ans += dfs_part_two(input, i, j);
            }
        }
    }
    return ans;
}

int main() {
    Grid input;
    string line;

    while (getline(cin, line)) {
        vector<int> row;
        for (char c : line) {
            if (isdigit(c)) {
                row.push_back(c - '0');
            }
        }
        input.push_back(row);
    }

    cout << "Part 1: " << part_one(input) << endl;
    cout << "Part 2: " << part_two(input) << endl;

    return 0;
}