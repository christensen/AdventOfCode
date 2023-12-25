#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <sstream>
#include <cctype>

void log(const std::string& o)
{
    std::cout << o << std::endl;
}

bool isWhitespace(const std::string &str) {
    for (char c : str) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

void splitString(const std::string &input, char delimiter, std::vector<std::string>& res, bool ignoreWhitespace) {
    std::istringstream iss(input);
    std::string token;
    while (std::getline(iss, token, delimiter)) {
        if (!ignoreWhitespace || !isWhitespace(token))
            res.push_back(token);
    }
    return;
}

/*
seeds: 79 14 55 13

seed-to-soil map:
50 98 2
52 50 48

soil-to-fertilizer map:
0 15 37
37 52 2
39 0 15

fertilizer-to-water map:
49 53 8
0 11 42
42 0 7
57 7 4

water-to-light map:
88 18 7
18 25 70

light-to-temperature map:
45 77 23
81 45 19
68 64 13

temperature-to-humidity map:
0 69 1
1 0 69

humidity-to-location map:
60 56 37
56 93 4
*/

int findLocation(std::vector<std::string>& input)
{
    std::vector<unsigned int> seeds;
    std::vector<unsigned int> seedToSoil;
    std::vector<unsigned int> soilToFert;
    std::vector<unsigned int> fertToWater;
    std::vector<unsigned int> waterToLight;
    std::vector<unsigned int> lightToTemp;
    std::vector<unsigned int> tempToHum;
    std::vector<unsigned int> humToLoc;
    int divider = 0;
    for (auto line : input) {
        if (divider == 0) {
            std::vector<std::string> seedString;
            splitString(line, ':', seedString, false);
            std::vector<std::string> seedsAsStrings;
            splitString(seedString.at(1), ' ', seedsAsStrings, true);
            for (auto s : seedsAsStrings)
                seeds.push_back(std::stoi(s));
            divider++;
        }
        if (divider == 1) {
            if (seedToSoil.empty() && (line.empty() || line.find(":") != std::string::npos))
                continue;
            else if (line.empty()) {
                divider++;
                continue;
            }
            std::vector<std::string> stsStr;
            splitString(line, ' ', stsStr, false);
            for (auto s : stsStr) {
                seedToSoil.push_back(std::stoi(s));
                log(s);
            }
        }
    }
    return 0;
}

std::vector<std::string> readFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
    }

    std::string line;
    std::vector<std::string> v;
    while (std::getline(file, line)) {
        v.push_back(line);
    }
    file.close();
    return v;
}

int main()
{
    std::string filename = "input5.txt";

    std::vector<std::string> v = readFile(filename);

    int closestLocation = findLocation(v);

    log("CLOSEST LOCATION: " + std::to_string(closestLocation));

    return 0;
}