#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
	const int WIN = 6;
	const int DRAW = 3;
	const int ROCK = 1;
	const int PAPER = 2;
	const int SCISSORS = 3;
	
	std::ifstream f("input_data2.txt");
	std::string line;
	int score = 0;
	if (f.is_open()) {
		while(std::getline(f, line)) {
			std::string opp = line.substr(0,1);
			std::string strategy = line.substr(2,3);
			if (strategy == "Y") {
				score += DRAW;
				score += opp == "A" ? ROCK : opp == "B" ? PAPER : SCISSORS;
				continue;
			}
			else if (strategy == "Z") {
				score += WIN;
				score += opp == "A" ? PAPER : opp == "B" ? SCISSORS : ROCK;
 				
			}
			else
				score += opp == "A" ? SCISSORS : opp == "B" ? ROCK : PAPER;
		}
		f.close();
	}
	
	std::cout << "total score: " << score << std::endl;
	
	return 0;
}