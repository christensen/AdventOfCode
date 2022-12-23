#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

int main()
{
	std::ifstream f("input_data4");
	std::string line;
	int result = 0;
	std::string hyphen = "-";
	std::string comma = ",";
	while (std::getline(f, line))
	{
		std::string original = line;
		std::string firstPair;
		std::string secondPair;
		firstPair = line.substr(0, line.find(comma));
		line.erase(0, line.find(comma) + 1);
		secondPair = line;
		
		int first = std::stoi(firstPair.substr(0, firstPair.find(hyphen)));
		firstPair.erase(0, firstPair.find(hyphen) + 1);
		int second = std::stoi(firstPair);
		int third = std::stoi(secondPair.substr(0, secondPair.find(hyphen)));
		secondPair.erase(0, secondPair.find(hyphen) + 1);
		int fourth = std::stoi(secondPair);
		
		std::vector<int> firstVec;
		std::vector<int> secondVec;
		
		for (int i = first; i <= second; ++i)
			firstVec.push_back(i);
		for (int i = third; i <= fourth; ++i)
			secondVec.push_back(i);
		
		std::vector<int> intersections;

    	std::set_intersection(firstVec.begin(), firstVec.end(),
                          	  secondVec.begin(), secondVec.end(),
                          	  back_inserter(intersections));
		result += intersections.size() > 0 ? 1 : 0;
	} 
	std::cout << "result: " << result << std::endl;
	return 0;
}