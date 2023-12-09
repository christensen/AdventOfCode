#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <cctype>

auto populateVector(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
        std::cerr << "Error opening file: " << filename << std::endl;

    std::string line;
    std::vector<std::string> v;
    while (std::getline(file, line)) {
        v.push_back(line);
    }
    file.close();

    return v;
}

int findMatchesAbove(std::string& row, const std::string& above)
{
    std::regex numberRegex("\\d+");

    std::sregex_iterator iterator(row.begin(), row.end(), numberRegex);
    std::sregex_iterator end;

    int result = 0;

    while (iterator != end) {
        std::smatch match = *iterator;
        int position = match.position();

        std::cout << "Match at position " << position << ": " << match.str() << std::endl;

        std::string dots(match.str().length(), '.');

        if (position - 1 > 0) {
            char cDiagonalLeftAbove = above[position - 1];
            std::cout << cDiagonalLeftAbove << std::endl;
            if (cDiagonalLeftAbove != '.' && ispunct(cDiagonalLeftAbove)) {
                std::cout << "HEY NICE! VALID NUMBER MATCH ABOVE BEFORE: " << match.str() << std::endl;
                result += std::stoi(match.str());
                row.replace(position, match.str().length(), dots);
                ++iterator;
                continue;
            }
        }

        if (position + match.str().length() < row.length()) {
            char cDiagonalRightAbove = above[position + match.str().length()];
            std::cout << cDiagonalRightAbove << std::endl;
            if (cDiagonalRightAbove != '.' && ispunct(cDiagonalRightAbove)) {
                std::cout << "HEY NICE! VALID NUMBER MATCH ABOVES AFTER: " << match.str() << std::endl;
                result += std::stoi(match.str());
                row.replace(position, match.str().length(), dots);
                ++iterator;
                continue;
            }
        }

        for (int i = position; i < position + match.str().length(); ++i) {
            char c = above[i];
            std::cout << c << std::endl;
            if (c != '.' && ispunct(c)) {
                std::cout << "HEY NICE! VALID NUMBER MATCH DIRECTLY ABOVE: " << match.str() << std::endl;
                result += std::stoi(match.str());
                row.replace(position, match.str().length(), dots);
                break;
            }
        }
        ++iterator;
        std::cout << std::endl;
    }

    return result;
}

int findMatchesOnSameRow(std::string& row)
{
    std::regex numberRegex("\\d+");

    std::sregex_iterator iterator(row.begin(), row.end(), numberRegex);
    std::sregex_iterator end;

    int result = 0;

    while (iterator != end) {
        std::smatch match = *iterator;
        int position = match.position();

        std::cout << "Match at position " << position << ": " << match.str() << std::endl;

        std::string dots(match.str().length(), '.');

         if (position - 1 > 0) {
            char cBefore = row[position - 1];
            std::cout << cBefore << std::endl;
            if (cBefore != '.' && ispunct(cBefore)) {
                std::cout << "HEY NICE! VALID NUMBER MATCH BELOW BEFORE: " << match.str() << std::endl;
                result += std::stoi(match.str());
                row.replace(position, match.str().length(), dots);
                // skip next check if we found it...
                ++iterator;
                continue;
            }
         }

         if (position + match.str().length() < row.length()) {
            char cAfter = row[position + match.str().length()];
            std::cout << cAfter << std::endl;
            if (cAfter != '.' && ispunct(cAfter)) {
                std::cout << "HEY NICE! VALID NUMBER MATCH BELOW AFTER: " << match.str() << std::endl;
                result += std::stoi(match.str());
                row.replace(position, match.str().length(), dots);
            }
         }
         ++iterator;
         std::cout << std::endl;
    }

    return result;
}

int findNumbersGettingMultiplied(const std::string& first, const std::string& second, const std::string& third)
{
    std::regex numberRegex("\\d+");

    std::sregex_iterator iterator(first.begin(), first.end(), numberRegex);
    std::sregex_iterator thirdLineIterator(third.begin(), third.end(), numberRegex);
    std::sregex_iterator end;
    int result = 0;
    int firstNumber = 0;

    while (iterator != end) {
        std::smatch match = *iterator;
        int position = match.position();

        std::cout << "Match at position " << position << ": " << match.str() << std::endl;

        std::string dots(match.str().length(), '.');

        if (position - 1 > 0) {
            int wantedPosition = position - 1;
            char cDiagonalLeftBelow = second[wantedPosition];
            if (cDiagonalLeftBelow == '*') {
                firstNumber += std::stoi(match.str());
                while (thirdLineIterator != end) {
                    std::smatch thirdLineMatch = *iterator;
                    int p = thirdLineMatch.position();
                    if (p == position || p > position - 1 - thirdLineMatch.str().length())
                        std::cout << "FOUND A MATCH THAT WE SHOULD MULTIPLY!" << std::endl;
                    ++thirdLineIterator;
                }
                ++iterator;
                continue;
            }
        }

        // if (position + match.str().length() < row.length()) {
        //     char cDiagonalRightBelow = second[position + match.str().length()];
        //     if (cDiagonalRightBelow == '*') {
        //         firstNumber += std::stoi(match.str());
        //         ++iterator;
        //         continue;
        //     }
        // }

        // for (int i = position; i < position + match.str().length(); ++i) {
        //     char c = second[i];
        //     if (c == '*') {
        //         firstNumber += std::stoi(match.str());
        //         break;
        //     }
        // }
        ++iterator;
    }

    return result;
}

auto solve(const std::vector<std::string>& engineVec)
{
    int rowNum = 0;
    int sum = 0;
    int n = 0;
    for (int i = 0; i < engineVec.size() - 2; ++i) {
        std::string firstLine = engineVec.at(i);
        std::string secondLine = engineVec.at(i+1);
        std::string thirdLine = engineVec.at(i+2);

        sum += findNumbersGettingMultiplied(firstLine, secondLine, thirdLine);

        if (n > 3)
            break;
        n++;
    }
    return sum;
}

int main()
{
    std::string filename = "input3.txt";

    auto v = populateVector(filename);
    std::cout << "ENGINE SIZE: " << v.size() << std::endl;
    std::cout << solve(v) << std::endl;

    return 0;
}
