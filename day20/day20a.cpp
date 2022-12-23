#include <iostream>
#include <fstream>
#include <vector>

int main()
{
	std::ifstream f("test_input");
	std::string line;
	int pos = 0;
	std::vector<int> vec(7);
	while(std::getline(f, line)) {
		int val = std::stoi(line);
		if (val > 0 && pos + val < vec.size())
			
	}
	
	
	return 0;
}