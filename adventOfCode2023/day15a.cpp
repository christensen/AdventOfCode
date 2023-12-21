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

    int result = 0;

    for (auto entry : entries)
    {
        int currentValue = 0;
        for (int i = 0; i < entry.size(); ++i)
        {
            currentValue += int(entry[i]);
            currentValue *= 17;
            currentValue %= 256;
        }
        result += currentValue;
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
