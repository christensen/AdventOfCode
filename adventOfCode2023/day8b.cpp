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

/*

    Step 0: You are at 11A and 22A.
    Step 1: You choose all of the left paths, leading you to 11B and 22B.
    Step 2: You choose all of the right paths, leading you to 11Z and 22C.
    Step 3: You choose all of the left paths, leading you to 11B and 22Z.
    Step 4: You choose all of the right paths, leading you to 11Z and 22B.
    Step 5: You choose all of the left paths, leading you to 11B and 22C.
    Step 6: You choose all of the right paths, leading you to 11Z and 22Z.

*/

int solve(auto instrux, auto m, auto v)
{
    std::string goal = "";
    int numberOfMoves = 0;
    std::string::iterator strIt = instrux.begin();
    bool allPathsEndWithZ = false;

    // std::cout << "Step 0: You are at ";
    // for (auto e : v)
    // {
    //     std::cout << e << ", ";
    // }

    // std::cout << std::endl;

    while (!allPathsEndWithZ)
    {
        if (strIt == instrux.end())
        {
            strIt = instrux.begin();
            log("\n");
        }
        std::cout << *strIt;
        char d = *strIt;
        for (auto &a : v)
        {
            auto entry = m.find(a)->second;
            a = d == 'R' ? entry.second : entry.first;
        }

        // std::cout << "Step " << numberOfMoves + 1 << ": You choose all of the " << (d == 'L' ? "left" : "right") << " paths, leading you to ";
        // for (auto e : v)
        // {
        //     std::cout << e << ", ";
        // }

        // log("");

        bool allZs = true;
        for (auto &z : v)
        {
            // log("number of moves: " + std::to_string(numberOfMoves));
            if (!z.ends_with('Z'))
            {
                allZs = false;
            }
        }

        allPathsEndWithZ = allZs;
        numberOfMoves++;
        strIt++;
    }
    return numberOfMoves;
}

auto readFile(const std::string &filename, auto &m, auto &v)
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
            // log(line);
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
            if (label.ends_with("A"))
                v.push_back(label);
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
    std::vector<std::string> v;
    auto instructions = readFile(filename, m, v);
    int sum = solve(instructions, m, v);
    log("SUM: " + std::to_string(sum));

    return 0;
}
