#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

enum class Operation : int
{
    None = 0,
    Add = 1,
    Mul = 2,
    Sqr = 3,
};

class Monkey
{
public:
	Monkey(std::vector<int> items, Operation op, int update, int div, int trueBud, int falseBud) :
		_items(items), _op(op), _update(update), _div(div),
		_trueBud(trueBud), _falseBud(falseBud), _inspections(0) {}

	void performMonkeyBusiness(std::vector<Monkey>& monkies) 
	{
		_inspections += _items.size();
		while (_items.size() > 0) {
			int item = _items.at(0);
			if (_op == Operation::Add)
				item += _update;
			else if (_op == Operation::Mul)
				item *= _update;
			else
				item *= item;
			item = getBoredWithItem(item);
			int monkeyToThrowTo = testItem(item);
			monkies.at(monkeyToThrowTo).getItems().push_back(item);
			_items.erase(_items.begin(), _items.begin() + 1);
		}
	}
	
	int getBoredWithItem(const int item) {
		return item / 3;
	}
	
	int testItem(const int item) {
		if (item % _div == 0)
			return _trueBud;
		return _falseBud;
	}
	
	std::vector<int>& getItems() {
		return _items;
	}
	
	int getNumberOfInspections() {
		return _inspections;
	}

private:
	std::vector<int> _items;
	Operation _op;
	int _update;
	int _div;
	int _trueBud;
	int _falseBud;
	int _inspections;
};

// Monkey 0:
//   Starting items: 64
//   Operation: new = old * 7
//   Test: divisible by 13
//     If true: throw to monkey 1
//     If false: throw to monkey 3

int main()
{
	std::ifstream f("input");
	std::string line;
	std::vector<Monkey> monkies;
	
	std::vector<int> items;
	int divisor = 0;
	Operation operation;
	int updateVal = 0;
	int trueBud = 0;
	int falseBud = 0;
	int numOfLines = 0;
	while (std::getline(f, line))
	{
        if (line.empty())
            continue;
		
		if (line.substr(0, 6) == "Monkey")
			continue;
        else if (line.substr(0, 18) == "  Starting items: ") {
            std::istringstream iss{line.substr(18)};
            int item;
            while (iss >> item) {
                items.push_back(item);
                iss.ignore(1);
            }
        }
        else if (line.substr(0, 21) == "  Test: divisible by ") {
            std::istringstream iss{line.substr(21)};
            iss >> divisor;

        }
        else if (line.substr(0, 23) == "  Operation: new = old ") {
            std::istringstream iss{line.substr(23)};
            std::string op;
            std::string update;
            iss >> op >> update;
            if (op == "*" && update == "old")
                operation = Operation::Sqr;
            else if (op == "+") {
                operation = Operation::Add;
                updateVal = std::stoull(update);
            }
            else if (op == "*") {
                operation = Operation::Mul;
                updateVal = std::stoull(update);
            }

        }
        else if (line.substr(0, 29) == "    If true: throw to monkey ") {
            std::istringstream iss{line.substr(29)};
            iss >> trueBud;
        }
        else if (line.substr(0, 30) == "    If false: throw to monkey ") {
            std::istringstream iss{line.substr(30)};
            iss >> falseBud;
        }
		numOfLines++;
		if (numOfLines == 5) {
			numOfLines = 0;
			Monkey monkey(items, operation, updateVal, divisor, trueBud, falseBud);
			monkies.push_back(monkey);
			items.clear();
			operation = Operation::None;
			updateVal = divisor = trueBud = falseBud = 0;
		}
	}
	
	for (int i = 0; i < 20; ++i) {
		for (auto& m : monkies) {
			m.performMonkeyBusiness(monkies);
		}
		
		int monkey = 0;
		std::cout << "Round: " << i + 1 << std::endl;
		for (auto& m : monkies) {
			std::cout << "Monkey " << monkey << ": ";
			for (auto item : m.getItems()) {
				std::cout << item << ", ";
			}
			std::cout << std::endl;
			monkey++;
		}
		std::cout << std::endl;
	}
	
	int monkey = 0;
	for (auto& m : monkies) {
		std::cout << "Monkey " << monkey << " inspections: " << m.getNumberOfInspections() << std::endl;
		monkey++;
	}
		
	return 0;
}