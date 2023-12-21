#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <ranges>
#include <map>
#include <utility>
#include <numeric>

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

int solve(auto &input)
{
    auto entries = split(input, ',');

    std::map<int, std::vector<std::pair<std::string, int>>> boxes;

    for (auto entry : entries)
    {
        int box = 0;
        int i = 0;
        while (entry[i] != '=' && entry[i] != '-')
        {
            box += int(entry[i]);
            box *= 17;
            box %= 256;
            ++i;
        }
        if (entry.find("=") != std::string::npos)
        {
            auto labelAndLens = split(entry, '=');
            std::cout << "Adding label " << labelAndLens.at(0) << " focal length " << labelAndLens.at(1) << " in box " << box << std::endl;
            auto it = std::find_if(boxes[box].begin(), boxes[box].end(), [&](auto &e)
                                   { return e.first == labelAndLens.at(0); });

            if (it != boxes[box].end())
            {
                boxes[box].erase(it);
                boxes[box].insert(it, std::make_pair(labelAndLens.at(0), std::stoi(labelAndLens.at(1))));
            }
            else
                boxes[box].insert(boxes[box].begin(), std::make_pair(labelAndLens.at(0), std::stoi(labelAndLens.at(1))));
        }
        else // Remove lens if found...
        {
            entry.pop_back();
            auto it = std::find_if(boxes[box].begin(), boxes[box].end(), [&](auto &e)
                                   { return e.first == entry; });
            std::cout << "removing label " << entry << " from box " << box << std::endl;
            if (it != boxes[box].end())
                boxes[box].erase(it);
        }
    }

    int result = 0;
    auto outerIterator = boxes.begin();
    for (; outerIterator != boxes.end(); ++outerIterator)
    {
        auto innerIterator = outerIterator->second.rbegin();
        int multiplier = 1;
        int boxNumber = outerIterator->first + 1;
        for (; innerIterator != outerIterator->second.rend(); ++innerIterator)
        {
            std::cout << "box " << boxNumber << " * multiplier " << multiplier << " * lens " << innerIterator->second;

            int r = boxNumber * multiplier * innerIterator->second;
            std::cout << " = " << r << std::endl;
            result += r;
            ++multiplier;
        }
    }

    return result;
}

auto readFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        std::cerr << "Error opening file: " << filename << std::endl;

    std::string line;
    std::getline(file, line);
    file.close();
    return line;
}

int main()
{
    std::string filename = "input15.txt";
    auto input = readFile(filename);
    log("SUM: " + std::to_string(solve(input)));
    return 0;
}
