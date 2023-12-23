#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <utility>

void log(const std::string &o)
{
    std::cout << o << std::endl;
}

int solve(auto &garden)
{
    int result = 0;
    // initial S position
    auto g = garden.at((garden.size() - 1) / 2);
    int lineLength = g.length();
    size_t initialPos = garden.at((garden.size() - 1) / 2).find("S");
    std::string identifier = std::to_string(initialPos) + "," + std::to_string((garden.size() - 1) / 2);
    // x, y positions
    std::map<std::string, std::pair<int, int>> currentPossiblePositions;
    currentPossiblePositions[identifier] = std::make_pair(initialPos, (garden.size() - 1) / 2);

    // log("intial state:");
    // for (auto &gardenPlot : garden)
    // {
    //     log(gardenPlot);
    // }
    // log("");

    if (initialPos == std::string::npos)
    {
        log("ERROR");
        return -1;
    }

    for (int i = 0; i < 64; ++i)
    {
        std::map<std::string, std::pair<int, int>> tmpPositions;
        auto it = currentPossiblePositions.begin();
        for (; it != currentPossiblePositions.end(); it++)
        {
            std::string &line = garden.at(it->second.second);
            std::string id = "";
            if (line[it->second.first] == 'O')
                line[it->second.first] = '.';
            if (it->second.first > 0 && (line[it->second.first - 1] == '.' || line[it->second.first - 1] == 'S'))
            {
                // log("We can go left!");
                line[it->second.first - 1] = 'O';
                id = std::to_string(it->second.first - 1) + "," + std::to_string(it->second.second);
                tmpPositions[id] = std::make_pair(it->second.first - 1, it->second.second);
            }
            if (it->second.first < lineLength - 1 && (line[it->second.first + 1] == '.' || line[it->second.first + 1] == 'S'))
            {
                // log("We can go right!");
                line[it->second.first + 1] = 'O';
                id = std::to_string(it->second.first + 1) + "," + std::to_string(it->second.second);
                tmpPositions[id] = std::make_pair(it->second.first + 1, it->second.second);
            }
            if (it->second.second > 0)
            {
                std::string &above = garden.at(it->second.second - 1);
                if (above[it->second.first] == '.' || above[it->second.first] == 'S')
                {
                    // log("we can go up!");
                    above[it->second.first] = 'O';
                    id = std::to_string(it->second.first) + "," + std::to_string(it->second.second - 1);
                    tmpPositions[id] = std::make_pair(it->second.first, it->second.second - 1);
                }
            }
            if (it->second.second < garden.size() - 1)
            {
                std::string &below = garden.at(it->second.second + 1);
                if (below[it->second.first] == '.' || below[it->second.first] == 'S')
                {
                    // log("we can go down!");
                    below[it->second.first] = 'O';
                    id = std::to_string(it->second.first) + "," + std::to_string(it->second.second + 1);
                    tmpPositions[id] = std::make_pair(it->second.first, it->second.second + 1);
                }
            }
        }
        currentPossiblePositions = tmpPositions;
        // for (auto &gardenPlot : garden)
        // {
        //     log(gardenPlot);
        // }
        // log("");
        // log("number of items now in map: " + std::to_string(currentPossiblePositions.size()));
        // log("\n\n");
    }
    return currentPossiblePositions.size();
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
