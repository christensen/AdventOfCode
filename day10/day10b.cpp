#include <iostream>
#include <string>
#include <fstream>
#include <vector>

void writeToCrt(int cycle, int val, std::string& line, std::vector<std::string>& image)
{
  int pos = cycle % 40;
  std::cout << "cycle: " << cycle << " and pos: " << pos << std::endl;
  if (pos == 0) {
    std::cout << "saving line: " << line << std::endl;
    image.push_back(line);
    line.clear();
  }
  else {
    if (pos == val || pos == val - 1 || pos == val + 1)
      line += "#";
    else
      line += ".";
  }
}

int main(int argc, char* argv[])
{
  std::ifstream f("input");
  std::string s;
  int val = 2;
  int cycle = 1;
  std::vector<std::string> image;
  std::string line;
  while (std::getline(f, s)) {
    if (s.find("noop") != std::string::npos)
      cycle++;
    else {
      cycle++;
      writeToCrt(cycle, val, line, image);
      cycle++;
      int x = std::stoi(s.substr(5));
      std::cout << "Adding " << x << " to val " << val << std::endl;
      val += x;
    }
    writeToCrt(cycle, val, line, image);
  }
  for (auto& str : image)
    std::cout << str << std::endl;
  return 0;
}
