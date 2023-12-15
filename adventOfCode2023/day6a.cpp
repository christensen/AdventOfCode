#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <ranges>
#include <tuple>

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

int solve(auto input)
{
    std::string t;
    std::string d;
    std::tie(t, d) = input;
    auto timeStr = split(t, ':').at(1);
    auto distanceStr = split(d, ':').at(1);
    auto timeVec = split(timeStr, ' ');
    auto distanceVec = split(distanceStr, ' ');

    removeEmpty(timeVec);
    removeEmpty(distanceVec);

    int result = 1;
    for (int i = 0; i < timeVec.size(); i++)
    {
        int time = std::stoi(timeVec.at(i));
        int distance = std::stoi(distanceVec.at(i));
        int numberOfWaysToWin = 0;
        for (int j = 1; j <= time; ++j)
        {
            int timeLeftToGo = time - j;
            if (j * timeLeftToGo > distance)
            {
                numberOfWaysToWin++;
                log("Going longer than record: " + std::to_string(distance) +
                    ", speed is: " + std::to_string(j) + " and time left to go is " +
                    std::to_string(timeLeftToGo) + ". Went " + std::to_string(j * timeLeftToGo) + " mm");
            }
        }
        result *= numberOfWaysToWin;
    }

    return result;
}

auto readFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        std::cerr << "Error opening file: " << filename << std::endl;

    std::string s1, s2;
    std::getline(file, s1);
    std::getline(file, s2);
    file.close();
    return std::make_tuple(s1, s2);
}

int main()
{
    std::string filename = "input6.txt";

    auto timeAndDistance = readFile(filename);
    int sum = solve(timeAndDistance);

    log("");
    log("SUM: " + std::to_string(sum));

    return 0;
}
