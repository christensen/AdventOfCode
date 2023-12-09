#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
	std::vector< std::vector<std::string> > v;
	std::ifstream f("input");
	std::string line;
	
	while (std::getline(f, line))
	{
		std::vector<std::string> tmp;
		for (int i = 0; i < line.length(); ++i) {
			std::string p = line.substr(i, 1);
			tmp.push_back(p);
		}
		v.push_back(tmp);
	}
	
	std::cout << "GREAT SUCCESS" << std::endl;
	return 0;
}