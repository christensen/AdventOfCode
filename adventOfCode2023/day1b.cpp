#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

 std::pair<int, int> findNumbersInstead(const std::string& input, int firstPos, int lastPos) {
    int firstDigit = -1;
    int lastDigit = -1;

    std::cout << "firstPositionNumberFound: " << firstPos << " lastPositionNumberFound: " << lastPos << std::endl;

    int n = 0;
    for (char ch : input) {
        if (std::isdigit(ch)) {
            if (n < firstPos) {
                firstPos = n;
                firstDigit = ch - '0';
                std::cout << "overriding firstDigit " << firstDigit << " at " << n << std::endl;
            }
            if (n >= lastPos) {
                lastDigit = ch - '0';
                std::cout << "overriding lastDigit " << lastDigit << " at " << n << std::endl;
            }
        }
        n++;
    }

    auto pair = std::make_pair(firstDigit, lastDigit);
    return pair;
}

int translateStringToNumber(const std::string& num) {
    if (num == "one")
        return 1;
    if (num == "two")
        return 2;
    if (num == "three")
        return 3;
    if (num == "four")
        return 4;
    if (num == "five")
        return 5;
    if (num == "six")
        return 6;
    if (num == "seven")
        return 7;
    if (num == "eight")
        return 8;
    if (num == "nine")
        return 9;
    return -1;
}

void solve(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::vector<std::string> numbers = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    std::string line;
    int sum = 0;
    while (std::getline(file, line)) {
        std::cout << "line: " << line << std::endl;
        int earliestPosition = line.length();
        int lastPosition = 0;
        std::string currentFoundFirstNumber = "";
        std::string currentFoundLastNumber = "";
        for (auto number : numbers) {
            int pos = line.find(number);
            int rPos = line.rfind(number);
            if (pos != std::string::npos) {
                if (earliestPosition > pos) {
                    earliestPosition = pos;
                    currentFoundFirstNumber = number;
                }
            }

            if (rPos != std::string::npos) {
                if (rPos > lastPosition) {
                    lastPosition = rPos;
                    currentFoundLastNumber = number;
                }
            }
        }

        int firstNum = -1;
        int lastNum = -1;

        std::pair<int, int> firstAndLast = findNumbersInstead(line, earliestPosition, lastPosition);
        if (firstAndLast.first != -1)
            firstNum = firstAndLast.first;
        if (firstAndLast.second != -1)
            lastNum = firstAndLast.second;

        int finalFirstNumber = 0;
        int finalLastNumber = 0;

        if (firstNum != -1)
            finalFirstNumber = firstNum;
        else
            finalFirstNumber = translateStringToNumber(currentFoundFirstNumber);
        if (lastNum != -1)
            finalLastNumber = lastNum;
        else
            finalLastNumber = translateStringToNumber(currentFoundLastNumber);

        std::cout << finalFirstNumber << finalLastNumber << std::endl;
        std::string concatNum = std::to_string(finalFirstNumber) + std::to_string(finalLastNumber);
        sum += std::stoi(concatNum);
    }
    std::cout << sum << std::endl;
    file.close();
}

int main() {
    std::string filename = "input1.txt";

    solve(filename);

    return 0;
}
