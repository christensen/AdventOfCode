#include <iostream>
#include <fstream>
#include <string>
#include <ranges>
#include <vector>

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

int solve(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return -1;
    }

    std::string line;
    int sum = 0;
    int n = 0;
    while (std::getline(file, line)) {
        // if (n >= 10)
        //     break;
        std::cout << "line: " << line << std::endl;
        auto gameIdentifierAndGames = split(line, ':');
        auto gameIdentifier = split(gameIdentifierAndGames.at(0), ' ');
        auto games = split(gameIdentifierAndGames.at(1), ';');
        int minimumNumberOfRedCubes = 0;
        int minimumNumberOfBlueCubes = 0;
        int minimumNumberOfGreenCubes = 0;
        for (auto game : games) {
            auto cubes = split(game, ',');
            for (auto c : cubes) {
                std::cout << "What is c? " << c << std::endl;
                auto numberAndColour = split(c, ' ');
                int numberOfCubes = std::stoi(numberAndColour.at(1));
                auto& colour = numberAndColour.at(2);
                if (colour == "red" && numberOfCubes > minimumNumberOfRedCubes)
                    minimumNumberOfRedCubes = numberOfCubes;
                if (colour == "green" && numberOfCubes > minimumNumberOfGreenCubes)
                    minimumNumberOfGreenCubes = numberOfCubes;
                if (colour == "blue" && numberOfCubes > minimumNumberOfBlueCubes)
                    minimumNumberOfBlueCubes = numberOfCubes;
            }
        }

        std::cout << "Red: " << minimumNumberOfRedCubes << " Green: " << minimumNumberOfGreenCubes << " Blue: " << minimumNumberOfBlueCubes << std::endl;

        sum += (minimumNumberOfRedCubes * minimumNumberOfGreenCubes * minimumNumberOfBlueCubes);
        n++;
    }
    file.close();

    return sum;
}

int main() {
    std::string filename = "input2.txt";

    std::cout << solve(filename) << std::endl;

    return 0;
}
