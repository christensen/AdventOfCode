#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::ifstream f("input_data4");
	std::string line;
	int result = 0;
	std::string hyphen = "-";
	std::string comma = ",";
	while (std::getline(f, line))
	{
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
		
		if ((first >= third && second <= fourth) ||
			  (third >= first && fourth <= second)) {
			std::cout << "match" << std::endl;
			std::cout << first << ".." << second << std::endl;
			std::cout << third << ".." << fourth << std::endl;
			std::cout << std::endl;
			result++;
		}
		else
			std::cout << "no match: " << line << std::endl;
	} 
	std::cout << "result: " << result << std::endl;
	return 0;
}