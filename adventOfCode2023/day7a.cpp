#include <algorithm>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

void log(const std::string &o)
{
    std::cout << o << std::endl;
}

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::istringstream iss(str);
    std::string token;

    while (std::getline(iss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

bool customSort(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
{
    const std::string order = "AKQJT987654321";

    auto aStr = a.first;
    auto bStr = b.first;

    for (int i = 0; i < aStr.size(); ++i)
    {
        size_t indexA = order.find(aStr[i]);
        size_t indexB = order.find(bStr[i]);
        if (indexA != indexB)
            return indexA > indexB;
    }
    return aStr.size() < bStr.size();
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
            fiveOfAKind.push_back(std::make_pair(h, b));
        else if (charCounts.size() == 2)
        {
            auto mapIt = charCounts.begin();
            int firstCount = mapIt->second;
            mapIt++;
            int secondCount = mapIt->second;
            if (firstCount == 3 || secondCount == 3)
                fullHouse.push_back(std::make_pair(h, b));
            else
                fourOfAKind.push_back(std::make_pair(h, b));
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
                threeOfAKind.push_back(std::make_pair(h, b));
            else
                twoPair.push_back(std::make_pair(h, b));
        }
        else if (charCounts.size() == 4)
            onePair.push_back(std::make_pair(h, b));
        else if (charCounts.size() == 5)
            highCard.push_back(std::make_pair(h, b));
    }

    std::sort(highCard.begin(), highCard.end(), customSort);
    std::sort(onePair.begin(), onePair.end(), customSort);
    std::sort(twoPair.begin(), twoPair.end(), customSort);
    std::sort(threeOfAKind.begin(), threeOfAKind.end(), customSort);
    std::sort(fullHouse.begin(), fullHouse.end(), customSort);
    std::sort(fourOfAKind.begin(), fourOfAKind.end(), customSort);
    std::sort(fiveOfAKind.begin(), fiveOfAKind.end(), customSort);

    std::vector<std::vector<std::pair<std::string, int>>> allHands = {
        highCard, onePair, twoPair, threeOfAKind, fullHouse, fourOfAKind, fiveOfAKind
    };

    long long result = 0;
    int rank = 1;

    for (auto& v : allHands) {
        for (auto& h : v) {
            result += h.second * rank;
            rank++;
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
