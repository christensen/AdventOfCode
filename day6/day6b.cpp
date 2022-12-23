#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

int main(int argc, char* argv[])
{
	std::string line;
	if (argc > 1)
		line = std::string(argv[1]);
	else {
		std::ifstream f("input_data6");
		std::getline(f, line);
		f.close();
	}
	int derp;
		
	int start = 0;
	int stop = 14;
	// std::cout << line << std::endl;
	std::unordered_set<char> charSet;
	for (; stop < line.length(); ++start, ++stop) {
		for (int i = start; i < stop; ++i)
			charSet.insert(line[i]);
		if (charSet.size() == 14)
			break;
		std::cout << "start: " << start << " stop: " << stop << std::endl;
		std::cout << charSet.size() << std::endl;
		std::for_each(charSet.cbegin(), charSet.cend(), [](char x) {
    		std::cout << x;
  		});
  		std::cout << std::endl;
		
		charSet.clear();
		
	}
	std::cout << "Found at after pos: " << stop << std::endl;
	return 0;
}