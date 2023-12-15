#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <ranges>
#include <map>
#include <utility>

static inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
                                    { return !std::isspace(ch); }));
}

void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                         { return !std::isspace(ch); })
                .base(),
            s.end());
}

static inline void trim(std::string &s)
{
    rtrim(s);
    ltrim(s);
}

void log(const std::string &o)
{
    std::cout << o << std::endl;
}

auto to_string = [](auto &&r) -> std::string
{
    const auto data = &*r.begin();
    const auto size = static_cast<std::size_t>(std::ranges::distance(r));

    return std::string{data, size};
};

auto split(const std::string &str, char delimiter) -> std::vector<std::string>
{
    const auto range = str | std::ranges::views::split(delimiter) |
                       std::ranges::views::transform(to_string);
    return {std::ranges::begin(range), std::ranges::end(range)};
}

void removeEmpty(std::vector<std::string> &v)
{
    v.erase(std::remove_if(v.begin(), v.end(), [](const std::string &s)
                           { return s.empty(); }),
            v.end());
}

int solve(auto instrux, auto m)
{
    std::string goal = "";
    int numberOfMoves = 0;
    auto directions = m.find("AAA");
    std::string::iterator strIt = instrux.begin();
    while (goal != "ZZZ")
    {

        if (strIt == instrux.end())
            strIt = instrux.begin();
        if (*strIt == 'L')
            goal = directions->second.first;
        else if (*strIt == 'R')
            goal = directions->second.second;
        directions = m.find(goal);
        numberOfMoves++;
        strIt++;
        if (goal == "ZZZ")
            break;
    }
    return numberOfMoves;
}

auto readFile(const std::string &filename, auto &m)
{
    std::ifstream file(filename);
    if (!file.is_open())
        std::cerr << "Error opening file: " << filename << std::endl;

    std::string instructions;
    std::getline(file, instructions);

    std::string line;
    while (std::getline(file, line))
    {
        if (!line.empty())
        {
            auto labelAndDirections = split(line, '=');
            auto label = labelAndDirections.at(0);
            auto directions = labelAndDirections.at(1);
            trim(label);
            auto tmp = split(directions, '(');
            auto tmp2 = split(tmp.at(1), ')');
            auto leftAndRight = split(tmp2.at(0), ',');
            std::string left = leftAndRight.at(0);
            std::string right = leftAndRight.at(1);
            trim(right);
            m[label] = std::make_pair(left, right);
        }
    }

    file.close();
    return instructions;
}

int main()
{
    std::string filename = "input8.txt";

    std::map<std::string, std::pair<std::string, std::string>> m;

    auto instructions = readFile(filename, m);
    int sum = solve(instructions, m);
    log("SUM: " + std::to_string(sum));

    return 0;
}
