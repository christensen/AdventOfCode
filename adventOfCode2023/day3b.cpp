#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <cctype>

void log(const std::string &output)
{
    std::cout << output << std::endl;
}

auto populateVector(const std::string &filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
        std::cerr << "Error opening file: " << filename << std::endl;

    std::string line;
    std::vector<std::string> v;
    while (std::getline(file, line))
    {
        v.push_back(line);
    }
    file.close();

    return v;
}

int findMatchesOnSameRow(std::string &row)
{
    std::regex numberRegex("\\d+");

    std::sregex_iterator iterator(row.begin(), row.end(), numberRegex);
    std::sregex_iterator end;

    int result = 0;

    log(row);
    log("");

    while (iterator != end)
    {
        std::smatch match = *iterator;
        int position = match.position();
        bool incrementedIt = false;
        if (position + match.str().length() < row.length())
        {
            int potentialMultiplierPos = position + match.str().length();
            char cAfter = row[potentialMultiplierPos];
            if (cAfter == '*')
            {
                incrementedIt = true;
                if (++iterator != end)
                {
                    if ((*iterator).position() - 1 == potentialMultiplierPos)
                    {
                        std::cout << std::stoi(match.str()) << " * " << std::stoi((*iterator).str()) << std::endl;
                        result += (std::stoi(match.str()) * std::stoi((*iterator).str()));
                    }
                }
            }
        }
        if (!incrementedIt)
        {
            ++iterator;
        }
    }

    return result;
}

int findMatchesOnOverTwoRows(const std::string &row1, const std::string &row2)
{
    std::regex numberRegex("\\d+");

    std::sregex_iterator iterator1(row1.begin(), row1.end(), numberRegex);
    std::sregex_iterator end;

    log(row1);
    log(row2);
    log("");

    int result = 0;

    while (iterator1 != end)
    {
        std::smatch match = *iterator1;
        int position = match.position();
        if (position + match.str().length() < row1.length())
        {
            std::sregex_iterator iterator2(row2.begin(), row2.end(), numberRegex);
            const int multiplierPosAfter = position + match.str().length();
            const int multiplierPosBefore = position - 1;
            char cAfter = row1[multiplierPosAfter];
            char cBefore = row1[multiplierPosBefore];
            if (cAfter == '*' || cBefore == '*')
            {
                while (iterator2 != end)
                {
                    std::smatch match2row = *iterator2;
                    int pos2 = match2row.position();
                    if (pos2 > multiplierPosAfter + 2)
                    {
                        break;
                    }
                    if (cAfter == '*')
                    {
                        if (pos2 + match2row.str().length() == multiplierPosAfter ||
                            pos2 - 1 == multiplierPosAfter)
                        {
                            std::cout << match.str() << " * " << match2row.str() << std::endl;
                            result += (std::stoi(match.str()) * std::stoi(match2row.str()));
                            break;
                        }
                        else
                        {
                            bool matchFound = false;
                            for (int i = 0; i < match2row.str().length(); ++i)
                            {
                                if (pos2 == multiplierPosAfter - i)
                                {
                                    matchFound = true;
                                    break;
                                }
                            }
                            if (matchFound)
                            {
                                std::cout << match.str() << " * " << match2row.str() << std::endl;
                                result += (std::stoi(match.str()) * std::stoi(match2row.str()));
                                break;
                            }
                        }
                    }
                    else
                    {
                        if (pos2 + match2row.str().length() == multiplierPosBefore ||
                            pos2 - 1 == multiplierPosBefore)
                        {
                            std::cout << match.str() << " * " << match2row.str() << std::endl;
                            result += (std::stoi(match.str()) * std::stoi(match2row.str()));
                            break;
                        }
                        else
                        {
                            bool matchFound = false;
                            for (int i = 0; i < match2row.str().length(); ++i)
                            {
                                if (pos2 == multiplierPosBefore - i)
                                {
                                    std::cout << match.str() << " * " << match2row.str() << std::endl;
                                    matchFound = true;
                                    break;
                                }
                            }
                            if (matchFound)
                            {
                                result += (std::stoi(match.str()) * std::stoi(match2row.str()));
                                break;
                            }
                        }
                    }
                    ++iterator2;
                }
            }
        }
        ++iterator1;
    }

    return result;
}

int findNumbersGettingMultiplied(const std::string &first, const std::string &second, const std::string &third)
{
    std::regex numberRegex("\\d+");

    std::sregex_iterator iterator(first.begin(), first.end(), numberRegex);
    std::sregex_iterator end;
    int result = 0;
    int firstNumber = 0;

    log(first);
    log(second);
    log(third);
    log("");

    while (iterator != end)
    {
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
        else
        {
            for (int i = position; i < position + match.str().length(); ++i)
            {
                char c = second[i];
                if (c == '*')
                {
                    mulitplierPos = i;
                    break;
                }
            }
        }
        if (mulitplierPos != -1)
        {
            std::sregex_iterator thirdLineIterator(third.begin(), third.end(), numberRegex);
            int thirdLinePos = 0;
            while (thirdLineIterator != end)
            {
                std::smatch thirdLineMatch = *thirdLineIterator;
                thirdLinePos = thirdLineMatch.position();
                if (thirdLinePos > position + match.str().length() + 1)
                {
                    break;
                }
                bool matchFound = false;
                if (thirdLinePos + thirdLineMatch.str().length() == mulitplierPos)
                {
                    matchFound = true;
                }
                else if (thirdLinePos - 1 == mulitplierPos)
                {
                    matchFound = true;
                }

                for (int i = 0; i < thirdLineMatch.str().length(); ++i)
                {
                    if (thirdLinePos == mulitplierPos - i)
                    {
                        matchFound = true;
                        break;
                    }
                }

                if (matchFound)
                {
                    int thirdNumber = std::stoi(thirdLineMatch.str());
                    log(std::to_string(firstNumber) + " * " + std::to_string(thirdNumber));
                    result += firstNumber * thirdNumber;
                    log("");
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

auto solve(const std::vector<std::string> &engineVec)
{
    int rowNum = 0;
    int sum = 0;
    for (int i = 0; i < engineVec.size() - 2; ++i)
    {
        std::string firstLine = engineVec.at(i);
        std::string secondLine = engineVec.at(i + 1);
        std::string thirdLine = engineVec.at(i + 2);
        sum += findMatchesOnSameRow(firstLine);
        sum += findMatchesOnOverTwoRows(firstLine, secondLine);
        sum += findMatchesOnOverTwoRows(secondLine, firstLine);
        if (i == engineVec.size() - 3)
        {
            sum += findMatchesOnOverTwoRows(secondLine, thirdLine);
            sum += findMatchesOnOverTwoRows(thirdLine, secondLine);
            sum += findMatchesOnSameRow(secondLine);
            sum += findMatchesOnSameRow(thirdLine);
        }
        sum += findNumbersGettingMultiplied(firstLine, secondLine, thirdLine);
    }
    return sum;
}

int main()
{
    std::string filename = "input3_example.txt";

    auto v = populateVector(filename);
    std::cout << solve(v) << std::endl;

    return 0;
}
