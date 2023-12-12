#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <ranges>
#include <set>
#include <cmath>

void log(const std::string& o)
{
    std::cout << o << std::endl;
}

auto to_string = [](auto&& r) -> std::string {
    const auto data = &*r.begin();
    const auto size = static_cast<std::size_t>(std::ranges::distance(r));

    return std::string{data, size};
};

auto split(const std::string& str, char delimiter) -> std::vector<std::string>
{
    const auto range = str | std::ranges::views::split(delimiter) |
                             std::ranges::views::transform(to_string);
    return {std::ranges::begin(range), std::ranges::end(range)};
}

int solve(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return -1;
    }

    std::string line;
    int sum = 0;
    while (std::getline(file, line)) {
        std::cout << "line: " << line << std::endl;
        auto cardNumberAndNumbers = split(line, ':');
        auto numbers = split(cardNumberAndNumbers.at(1), '|');
        auto winningNumbers = split(numbers.at(0), ' ');
        auto scratchNumbers = split(numbers.at(1), ' ');

        winningNumbers.erase(std::remove_if(winningNumbers.begin(), winningNumbers.end(), [](const std::string& s) {
            return s.empty();
        }), winningNumbers.end());

        scratchNumbers.erase(std::remove_if(scratchNumbers.begin(), scratchNumbers.end(), [](const std::string& s) {
            return s.empty();
        }), scratchNumbers.end());

        std::sort(winningNumbers.begin(), winningNumbers.end());
        std::sort(scratchNumbers.begin(), scratchNumbers.end());

        log("winning numbers: ");
        for (auto winningNumber : winningNumbers) {
            std::cout << winningNumber << " ";
        }

        std::cout << std::endl;

        log("scratch numbers: ");
        for (auto scratch : scratchNumbers) {
            std::cout << scratch << " ";
        }

        std::vector<std::string> common;

        std::set_intersection(
            winningNumbers.begin(), winningNumbers.end(),
            scratchNumbers.begin(), scratchNumbers.end(),
            std::back_inserter(common)
        );

        int matches = common.size();

        log("matches: " + std::to_string(matches));

        int result = 0;

        if (matches == 1) {
            log("adding just one...");
            result = 1;
        }
        else if (matches > 1) {
            result = pow(2, matches - 1);
            log("adding result " + std::to_string(result));
        }
        else
            log("Ignored this value!");

        sum += result;
    }
    file.close();
    return sum;
}

int main()
{
    std::string filename = "input4.txt";

    std::cout << "\n" << solve(filename) << std::endl;

    return 0;
}
