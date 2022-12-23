#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char* argv[])
{
  std::ifstream f("input");
  std::string line;
  int val = 1;
  int cycle = 1;
  int totalVal = 0;
  while (std::getline(f, line)) {
    bool alreadyChecked = false;
    if (line.find("noop") != std::string::npos) {
      cycle++;
    }
    else {
      cycle++;
      if (cycle == 20 || (cycle > 50 && (cycle - 20) % 40 == 0)) {
        alreadyChecked = true;
        totalVal += cycle * val;
        std::cout << "cycle " << cycle << " * " << val << " = " << cycle * val << std::endl;
      }
      cycle++;
      int x = std::stoi(line.substr(5));
      std::cout << "Adding " << x << " to val " << val << std::endl;
      val += x;
    }
    if (!alreadyChecked && (cycle == 20 || (cycle > 50 && (cycle - 20) % 40 == 0))) {
      std::cout << "checking after the fact" << std::endl;
      totalVal += cycle * val;
      std::cout << "cycle " << cycle << " * " << val << " = " << cycle * val << std::endl;
    }
  }
  std::cout << "Total: " << totalVal << std::endl;
  return 0;
}
