#include <algorithm>
#include <cctype>
#include <iostream>
#include <fstream>
#include <ranges>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

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

bool customSort(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
{
    const std::string order = "AKQJT";

    auto aStr = a.first;
    auto bStr = b.first;

    for (int i = 0; i < aStr.size(); ++i)
    {
        if (isdigit(aStr[i]) && !isdigit(bStr[i]))
            return false;
        if (isdigit(bStr[i]) && !isdigit(aStr[i]))
            return true;
        if (isdigit(aStr[i]) && isdigit(bStr[i]))
            return aStr[i] < bStr[i];
        size_t indexA = order.find(aStr[0]);
        size_t indexB = order.find(bStr[0]);

        if (indexA == indexB)
        {
            continue;
        }
        return indexA < indexB;
    }
    return true;
}

int solve(auto hands)
{
    std::vector<std::pair<std::string, int>> highCard;
    std::vector<std::pair<std::string, int>> onePair;
    std::vector<std::pair<std::string, int>> twoPair;
    std::vector<std::pair<std::string, int>> threeOfAKind;
    std::vector<std::pair<std::string, int>> fourOfAKind;
    std::vector<std::pair<std::string, int>> fiveOfAKind;
    std::vector<std::pair<std::string, int>> fullHouse;

    for (auto &hand : hands)
    {
        auto handAndBid = split(hand, ' ');
        auto h = handAndBid.at(0);
        int b = std::stoi(handAndBid.at(1));
        auto copy = h;
        std::sort(copy.begin(), copy.end());

        // Populate map of characters
        std::unordered_map<char, int> charCounts;
        for (auto &c : copy)
            charCounts[c]++;

        if (charCounts.size() == 1)
        {
            log("five of a kind " + h);
            fiveOfAKind.push_back(std::make_pair(h, b));
        }
        else if (charCounts.size() == 2)
        {
            auto mapIt = charCounts.begin();
            int firstCount = mapIt->second;
            mapIt++;
            int secondCount = mapIt->second;
            if (firstCount == 3)
            {
                fullHouse.push_back(std::make_pair(h, b));
                log("full house " + h);
            }
            else
            {
                fourOfAKind.push_back(std::make_pair(h, b));
                log("four of a kind " + h);
            }
        }
        else if (charCounts.size() == 3)
        {
            int s = 0;
            for (auto counts : charCounts)
            {
                if (s < counts.second)
                    s = counts.second;
            }
            if (s == 3)
            {
                threeOfAKind.push_back(std::make_pair(h, b));
                log("three of a kind " + h);
            }
            else
            {
                twoPair.push_back(std::make_pair(h, b));
                log("two pairs " + h);
            }
        }
        else if (charCounts.size() == 4)
        {
            log("only one pair found: " + h);
            onePair.push_back(std::make_pair(h, b));
        }
        else if (charCounts.size() == 5)
        {
            highCard.push_back(std::make_pair(h, b));
            // Take next hand
            log("high card found: " + h);
        }
    }

    std::sort(twoPair.begin(), twoPair.end(), customSort);

    log("Check order for two pairs:");
    auto twoPairIt = twoPair.begin();
    for (; twoPairIt != twoPair.end(); ++twoPairIt)
    {
        log(twoPairIt->first);
    }
    return 0;
}

auto readFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        std::cerr << "Error opening file: " << filename << std::endl;

    std::string line;
    std::vector<std::string> hands;
    while (std::getline(file, line))
    {
        hands.push_back(line);
    }

    file.close();
    return hands;
}

int main()
{
    std::string filename = "input7.txt";

    auto hands = readFile(filename);
    int sum = solve(hands);

    log("");
    log("SUM: " + std::to_string(sum));

    return 0;
}
