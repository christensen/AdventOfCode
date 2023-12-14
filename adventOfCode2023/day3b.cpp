#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <cctype>

void log(const std::string& output)
{
    std::cout << output << std::endl;
}

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

int findMatchesOnSameRow(std::string& row)
{
    std::regex numberRegex("\\d+");

    std::sregex_iterator iterator(row.begin(), row.end(), numberRegex);
    std::sregex_iterator end;

    int result = 0;

    while (iterator != end) {
        std::smatch match = *iterator;
        int position = match.position();
        bool incrementedIt = false;
        std::cout << "Match at position " << position << ": " << match.str() << std::endl;
        if (position + match.str().length() < row.length()) {
            int potentialMultiplierPos = position + match.str().length();
            char cAfter = row[potentialMultiplierPos];
            if (cAfter == '*') {
                incrementedIt = true;
                if (++iterator != end) {
                    if ((*iterator).position() - 1 == potentialMultiplierPos) {
                        result += (std::stoi(match.str()) * std::stoi((*iterator).str()));
                    }
                }
            }
        }
        if (!incrementedIt) {
            ++iterator;
        }
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

        firstNumber = std::stoi(match.str());

        int diagonalLeftPosition = position - 1;
        int diagonalRightPosition = position + match.str().length();

        char cDiagonalLeftBelow = second[diagonalLeftPosition];
        char cDiagonalRightBelow = second[diagonalRightPosition];
        
        int mulitplierPos = -1;

        if (cDiagonalLeftBelow == '*')
            mulitplierPos = diagonalLeftPosition;
        else if (cDiagonalRightBelow == '*')
            mulitplierPos = diagonalRightPosition;
        else {
            for (int i = position; i < position + match.str().length(); ++i) {
                char c = second[i];
                if (c == '*') {
                    mulitplierPos = i;
                    break;
                }
            }
        }
        if (mulitplierPos != -1) {
            log("Match on line 1: " + match.str() + " at position " + std::to_string(position));
            // log("Found a multiplier sign at position " + std::to_string(mulitplierPos));
            int thirdLinePos = 0;
            while (thirdLineIterator != end) {
                std::smatch thirdLineMatch = *thirdLineIterator;
                thirdLinePos = thirdLineMatch.position();
                if (thirdLinePos > position + match.str().length() + 1) {
                    log("Third line position became too great, position " +
                        std::to_string(position) + " third line position " +
                        std::to_string(thirdLinePos + 1));
                    break;
                }
                log("Match on line 3: " + thirdLineMatch.str() + " at position " + std::to_string(thirdLinePos));
                bool matchFound = false;
                if (thirdLinePos + thirdLineMatch.str().length() == mulitplierPos) {
                    log("match diagonal left");
                    matchFound = true;
                }
                else if (thirdLinePos - 1 == mulitplierPos) {
                    log("match diagonal right");
                    matchFound = true;
                }
                
                for (int i = 0; i < thirdLineMatch.str().length() - 1; ++i) {
                    if (thirdLinePos == mulitplierPos - i) {
                        log("match underneath");
                        matchFound = true;
                        break;
                    }
                }

                if (matchFound) {
                    int thirdNumber = std::stoi(thirdLineMatch.str());
                    // log("First number: " + std::to_string(firstNumber) +
                    //     " third number: " + std::to_string(thirdNumber));
                    log("MATCH!");
                    log("");
                    result += firstNumber * thirdNumber;
                    break;
                }
                ++thirdLineIterator;
            }
            ++iterator;
            continue;
        }
        ++iterator;
    }

    return result;
}

auto solve(const std::vector<std::string>& engineVec)
{
    int rowNum = 0;
    int sum = 0;
    for (int i = 0; i < engineVec.size() - 2; ++i) {
        std::string firstLine = engineVec.at(i);
        std::string secondLine = engineVec.at(i+1);
        std::string thirdLine = engineVec.at(i+2);
        log(firstLine);
        log(secondLine);
        log(thirdLine);
        log("");
        sum += findMatchesOnSameRow(firstLine);
        if (i == engineVec.size() - 3) {
            sum += findMatchesOnSameRow(secondLine);
            sum += findMatchesOnSameRow(thirdLine);
        }
        sum += findNumbersGettingMultiplied(firstLine, secondLine, thirdLine);
    }
    return sum;
}

int main()
{
    std::string filename = "input3.txt";

    auto v = populateVector(filename);
    std::cout << solve(v) << std::endl;

    return 0;
}
