#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
	std::ifstream f("input_data6");
	if (f.is_open()) {
		std::string line;
		std::getline(f, line);
		std::cout << "length: " << line.length() << std::endl;
		unsigned int pos = 0;
		unsigned int idx = 0;
		char one = line[0];
		char two = line[1];
		char three = line[2];
		char four = line[3];
		int i = 4;
		for (; i < line.length(); ++i) {
			if (one != two && one != three && one != four &&
				  two != three && two != four && three != four) {
				break;
			}
			one = two;
			two = three;
			three = four;
			four = line[i];
		}
		std::cout << "Found at after pos: " << i << std::endl;
	}
	return 0;
}