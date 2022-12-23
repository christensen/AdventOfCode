#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include <numeric>
#include <set>

int main()
{
	std::ifstream f("input_data3");
	int total = 0;
	if (f.is_open())
	{
		std::string elf1;
		// assume input comes in threes...
		while (std::getline(f, elf1))
		{
			std::string elf2;
			std::string elf3;
			std::getline(f, elf2);
			std::getline(f, elf3);
			for (char& c : elf1)
			{
				if (elf2.find(c) != std::string::npos &&
					elf3.find(c) != std::string::npos)
				{
					total += int(c) - (islower(c) ? 96 : 38);
					break;
				}
			}
		}
	}
	else
		std::cout << "Could not open file" << std::endl;
	
	std::cout << "sum of all badges: " << total << std::endl;
	return 0;
}