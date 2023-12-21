#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

void log(const std::string &o)
{
    std::cout << o << std::endl;
}

int solve(auto &garden)
{
    int result = 0;
    // initial S position
    auto g = garden.at((garden.size() - 1) / 2);
    log(g);
    size_t initialPos = garden.at((garden.size() - 1) / 2).find("S");
    // x, y positions
    std::map<int, int> visitedPositions;
    visitedPositions[initialPos] = (garden.size() - 1) / 2;
    if (initialPos == std::string::npos)
    {
        log("ERROR");
        return -1;
    }

    for (int i = 0; i < 64; ++i)
    {
        log("do stuff...");
    }
    return 0;
}

auto readFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        std::cerr << "Error opening file: " << filename << std::endl;

    std::string line;
    std::vector<std::string> garden;
    while (std::getline(file, line))
    {
        garden.push_back(line);
    }
    file.close();
    return garden;
}

int main()
{
    std::string filename = "input21.txt";
    auto garden = readFile(filename);
    log("SUM: " + std::to_string(solve(garden)));
    return 0;
}
