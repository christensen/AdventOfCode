#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <vector>

int main(int argc, char* argv[]) {
	std::string line;
	std::ifstream input("input_data.txt");
	int sumPerElf = 0;
	std::vector<int> allElves;
	if (input.is_open()) {
		while(std::getline(input, line)) {
			if (line.length() == 0) {
				allElves.push_back(sumPerElf);
				sumPerElf = 0;
			}
			else {
				sumPerElf += std::stoi(line);
			}
		}
		input.close();
	}
	else {
		std::cout << "opening file failed!" << std::endl;
		return -1;
	}
	std::sort(allElves.begin(), allElves.end(), std::greater<int>());
	std::cout << std::accumulate(allElves.begin(), allElves.begin() + 3, 0) << std::endl;
	return 0;
}