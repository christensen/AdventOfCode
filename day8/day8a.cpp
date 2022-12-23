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
            tmpVec.push_back(std::make_pair(std::stoi(height), 0));
        }
        v.push_back(tmpVec);
    }

    int outsideTrees = (v.at(0).size() * 2) + ((v.size() - 2) * 2);

    for (int i = 1; i < v.size() - 1; ++i) {
        std::vector< std::pair<int, int> >& row = v.at(i);
        for (int j = 1; j < row.size(); ++j) {
            bool highestTree = true;
            for (int k = 0; k < j; ++k) {
                if (row.at(k).first >= row.at(j).first) {
                    highestTree = false;
                    break;
                }
            }
            if (highestTree) {
                row.at(j).second++;
            }
        }
    }
    
    for (int i = 1; i < v.size() - 1; ++i) {
        std::vector< std::pair<int, int> >& row = v.at(i);
        for (int j = row.size() - 2; j >= 1; --j) {
            bool highestTree = true;
            for (int k = row.size() - 1; k > j; --k) {
                if (row.at(k).first >= row.at(j).first) {
                    highestTree = false;
                    break;
                }
            }
            if (highestTree) {
                row.at(j).second++;
            }
        }
    }

    for (int i = 1; i < v.size() - 1; ++i) {
        std::vector< std::pair<int, int> >& row = v.at(i);
        for (int j = 1; j < row.size() - 1; ++j) {
            bool highestTree = true;
            for (int k = 0; k < i; ++k) {
                if (v.at(k).at(j).first >= row.at(j).first) {
                    highestTree = false;
                    break;
                }
            }
            if (highestTree) {
                row.at(j).second++;
            }
        }
    }

    for (int i = v.size() - 2; i > 0 - 1; --i) {
        std::vector< std::pair<int, int> >& row = v.at(i);
        for (int j = 1; j < row.size() - 1; ++j) {
            bool highestTree = true;
            for (int k = v.size() - 1; k > i; --k) {
                if (v.at(k).at(j).first >= row.at(j).first) {
                    highestTree = false;
                    break;
                }
            }
            if (highestTree) {
                row.at(j).second++;
            }
        }
    }

    // count all with more than 1 in second
    int yer = 0;
    for (int i = 1; i < v.size() - 1; ++i) {
        std::vector< std::pair<int, int> > pairVec = v.at(i);
        for (int j = 1; j < pairVec.size() - 1; ++j) {
            if (pairVec.at(j).second > 0)
                yer++;
        }
    }

    std::cout << "Number of trees on the outer edges: " << outsideTrees << std::endl;
    std::cout << "other trees that are visible: " << yer << std::endl;
    std::cout << "total: " << outsideTrees + yer << std::endl;

    return 0;
}