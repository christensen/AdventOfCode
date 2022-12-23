#include <iostream>
#include <set>
#include <fstream>
#include <utility>
#include <cstdlib>
#include <vector>

int main()
{
	std::ifstream f("test_input2");
	std::set< std::pair<int, int> > s;
	std::string l;
	std::vector< std::pair<int, int> > knots;
	for (int i = 0; i < 10; ++i) {
		knots.push_back(std::make_pair(0, 0));
	}
	while (std::getline(f, l)) {
		std::string direction = l.substr(0, 1);
		int steps = std::stoi(l.substr(2));
		std::cout << "instruction: " << l << std::endl;
		for (int j = 0; j < knots.size() - 1; j+=2) {
			std::pair<int, int>& knot = knots.at(j);
			std::pair<int, int>& followKnot = knots.at(j+1);
			std::cout << "Moving knot ";
			if (j == 0)
				std::cout << "H";
			else
				std::cout << j;
			std::cout << std::endl;
			for (int i = 0; i < steps; ++i) {
				if (direction == "R" || direction == "L") {
					int backOrForward = direction == "R" ? 1 : -1;
					knot.first += backOrForward;
					// Same row
					if (knot.second == followKnot.second) {
						if (std::abs(knot.first - followKnot.first) > 1)
							followKnot.first += backOrForward;
						// else don't move
					}
					else {
						if (std::abs(knot.first - followKnot.first) > 1) {
							followKnot.first += backOrForward;
							followKnot.second = knot.second;
						}
					}
				}
				else {
					int upOrDown = direction == "D" ? 1 : -1;
					knot.second += upOrDown;
					if (knot.first == followKnot.first) {
						if (std::abs(knot.second - followKnot.second) > 1)
							followKnot.second += upOrDown;
					}
					else {
						if (std::abs(knot.second - followKnot.second) > 1) {
							followKnot.second += upOrDown;
							followKnot.first = knot.first;
						}
					}
				}
			}
			if (j == knots.size() - 2) { // last knot
				std::cout << "Storing x,y position: " << followKnot.first << ", " << followKnot.second << std::endl;
				std::pair<int, int> newX =
					std::make_pair(followKnot.first, followKnot.second);
				s.insert(newX);
			}
		}
	}
	std::cout << "Number of unique positions for tail: " << s.size() << std::endl;
	return 0;
}