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
			std::string me = line.substr(2,3);
			std::cout << "opp: " << opp << " me: " << me << std::endl;
			if ((opp == "A" && me == "X") ||
				  (opp == "B" && me == "Y") ||
				  (opp == "C" && me == "Z"))
				score += DRAW;
			else if ((opp == "A" && me == "Y") ||
					(opp == "B" && me == "Z") ||
					(opp == "C" && me == "X"))
				score += WIN;

			score += me == "X" ? ROCK : me == "Y" ? PAPER : SCISSORS;
		}
		f.close();
	}
	
	std::cout << "total score: " << score << std::endl;
	
	return 0;
}