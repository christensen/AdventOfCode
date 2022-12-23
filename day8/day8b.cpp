#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>

int main()
{
    std::ifstream f("input");
    std::string line;
    std::vector< std::vector< std::pair<int, int> > > v;
    while(std::getline(f, line)) {
        std::vector< std::pair<int, int> > tmpVec;
        for (int i = 0; i < line.length(); ++i) {
            std::string height = line.substr(i, 1);
            tmpVec.push_back(std::make_pair(std::stoi(height), 1));
        }
        v.push_back(tmpVec);
    }

    int maxVal = 0;
    for (int i = 1; i < v.size() - 1; ++i) {
        std::vector< std::pair<int, int> >& row = v.at(i);
        for (int j = 1; j < row.size() - 1; ++j) {
            // Check score to left:
            int freeViewLeft = 0;
            int freeViewRight = 0;
            int freeViewUp = 0;
            int freeViewDown = 0;
            std::pair<int, int>& item = row.at(j);
            int left = j - 1;
            while (left >= 0) {
                freeViewLeft++;
                if (row.at(left).first < item.first)
                    left--;
                else
                    break;
            }
            if (freeViewLeft > 0)
                item.second *= freeViewLeft;
            // Check score to right
            int right = j + 1;
            while (right < row.size()) {
                freeViewRight++;
                if (row.at(right).first < item.first)
                    right++;
                else
                    break;
            }
            if (freeViewRight > 0)
                item.second *= freeViewRight;
            // Check score up
            int up = i - 1;
            while (up >= 0) {
                freeViewUp++;
                if (v.at(up).at(j).first < item.first)
                    up--;
                else
                    break;
            }
            if (freeViewUp > 0)
                item.second *= freeViewUp;
            // Check score down
            int down = i + 1;
            while (down < v.size()) {
                freeViewDown++;
                if (v.at(down).at(j).first < item.first)
                    down++;
                else
                    break;
            }
            if (freeViewDown > 0)
                item.second *= freeViewDown;
        }
    }

    for (int i = 1; i < v.size() - 1; ++i) {
        std::vector< std::pair<int, int> > pairVec = v.at(i);
        for (int j = 1; j < pairVec.size() - 1; ++j) {
            if (pairVec.at(j).second > 0)
                maxVal = std::max(maxVal, pairVec.at(j).second);
        }
    }

    std::cout << "Max scenic score: " << maxVal << std::endl;

    return 0;
}