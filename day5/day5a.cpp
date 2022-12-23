//[N]     [Q]         [N]            
//[R]     [F] [Q]     [G] [M]        
//[J]     [Z] [T]     [R] [H] [J]    
//[T] [H] [G] [R]     [B] [N] [T]    
//[Z] [J] [J] [G] [F] [Z] [S] [M]    
//[B] [N] [N] [N] [Q] [W] [L] [Q] [S]
//[D] [S] [R] [V] [T] [C] [C] [N] [G]
//[F] [R] [C] [F] [L] [Q] [F] [D] [P]
// 1   2   3   4   5   6   7   8   9 
 
#include <iostream>
#include <vector>
#include <fstream>

int main() {
	char firstArray[] = { 'F', 'D', 'B', 'Z', 'T', 'J', 'R', 'N' };
	std::vector<char> firstCol(firstArray, firstArray + sizeof(firstArray) / sizeof(char));
	char secondArray[] = { 'R', 'S', 'N', 'J', 'H' };
	std::vector<char> secondCol(secondArray, secondArray + sizeof(secondArray) / sizeof(char));
	char thirdArray[] = { 'C', 'R', 'N', 'J', 'G', 'Z', 'F', 'Q' };
	std::vector<char> thirdCol(thirdArray, thirdArray + sizeof(thirdArray) / sizeof(char));
	char fourthArray[] = { 'F', 'V', 'N', 'G', 'R', 'T', 'Q' };
	std::vector<char> fourthCol(fourthArray, fourthArray + sizeof(fourthArray) / sizeof(char));
	char fifthArray[] = { 'L', 'T', 'Q', 'F' };
	std::vector<char> fifthCol(fifthArray, fifthArray + sizeof(fifthArray) / sizeof(char));
	char sixthArray[] = { 'Q', 'C', 'W', 'Z', 'B', 'R', 'G', 'N' };
	std::vector<char> sixthCol(sixthArray, sixthArray + sizeof(sixthArray) / sizeof(char));
	char seventhArray[] = { 'F', 'C', 'L', 'S', 'N', 'H', 'M' };
	std::vector<char> seventhCol(seventhArray, seventhArray + sizeof(seventhArray) / sizeof(char));
	char eigthArray[] = { 'D', 'N', 'Q', 'M', 'T','J' };
	std::vector<char> eigthCol(eigthArray, eigthArray + sizeof(eigthArray) / sizeof(char));
	char ninthArray[] = { 'P', 'G', 'S' };
	std::vector<char> ninthCol(ninthArray, ninthArray + sizeof(ninthArray) / sizeof(char));
	
	std::vector<std::vector< char > > allCols;
	allCols.push_back(firstCol);
	allCols.push_back(secondCol);
	allCols.push_back(thirdCol);
	allCols.push_back(fourthCol);
	allCols.push_back(fifthCol);
	allCols.push_back(sixthCol);
	allCols.push_back(seventhCol);
	allCols.push_back(eigthCol);
	allCols.push_back(ninthCol);
	
	std::ifstream f("input_data5");
	std::string line;
	while (std::getline(f, line)) {
		line = line.erase(0, 5);
		int amount = std::stoi(line.substr(0, line.find(" ")));
		line.erase(0, line.find(" ") + 6);
		int from = std::stoi(line.substr(0, line.find(" "))) - 1;
		line.erase(0, line.find(" ") + 4);
		int to = std::stoi(line) - 1;
		std::cout << "amount: " << amount << " from: " << from << " to: " << to << std::endl; 
		for (int i = 0; i < amount; ++i) {
			char c = allCols.at(from).back();
			allCols.at(from).pop_back();
			allCols.at(to).push_back(c);
		}
	}
		
	std::cout << "Secret word: " << allCols.at(0).back() << allCols.at(1).back()
			  << allCols.at(2).back() << allCols.at(3).back() << allCols.at(4).back()
			  << allCols.at(5).back() << allCols.at(6).back() << allCols.at(7).back()
			  << allCols.at(8).back() << std::endl;
	return 0;
}