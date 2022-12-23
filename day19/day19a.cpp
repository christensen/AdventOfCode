#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
	std::ifstream f("test_input");
	std::string line;
	while (std::getline(f, line))
	{
		int ore_robot = 1;
		int clay_robot = 0;
		int obsidian_robot = 0;
		int geode_robot = 0;
		int ore = 0;
		int clay = 0;
		int obsidian = 0;
		int geode = 0;
		std::cout << "Original line: " << line << std::endl;
		// Ditch Blueprint: 
		line = line.substr(line.find(" ") + 1, line.length());
		std::string idStr = line.substr(0, line.find(":"));
		int id = std::stoi(idStr);
		line = line.substr(line.find("costs") + 6, line.length());
		int oreCost = std::stoi(line.substr(0, line.find(" ")));
		line = line.substr(line.find("costs") + 6, line.length());
		int clayCost = std::stoi(line.substr(0, line.find(" ")));
		line = line.substr(line.find("costs") + 6, line.length());
		int obsidianOreCost = std::stoi(line.substr(0, line.find(" ")));
		line = line.substr(line.find("and") + 4, line.length());
		int obsidianClayCost = std::stoi(line.substr(0, line.find("clay") - 1));
		line = line.substr(line.find("costs") + 6, line.length());
		int geodeOreCost = std::stoi(line.substr(0, line.find(" ")));
		line = line.substr(line.find("and") + 4, line.length());
		int geodeObsidianCost = std::stoi(line.substr(0, line.find("obsidian") - 1));
		
		for (int i = 1; i <= 24; ++i)
		{
			std::cout << " == Minute " << i << " == " << std::endl;
			bool ore_robot_building = false;
			bool clay_robot_building = false;
			bool obsidian_robot_building = false;
			bool geode_robot_building = false;
			if (ore >= clayCost) {
				std::cout << "Spend " << ore << " ore to start building clay robot" << std::endl;
				ore -= clayCost;
				clay_robot_building = true;
			}
			if (ore_robot > 0) {
				std::cout << ore_robot << " ore-collecting robot(s) collects " << ore_robot << " ore, have now: " << ore + ore_robot << std::endl;
				ore += ore_robot;
			}
			if (clay_robot > 0) {
				std::cout << clay_robot << " clay-collecting robot(s) collects " << clay_robot << " clay, have now: " << clay + clay_robot << std::endl;
				clay += clay_robot;
			}
			if (obsidian_robot > 0) {
				std::cout << obsidian_robot << " obisidian-collecting robot(s) collects " << obsidian_robot << " obsidian, have now: " << obsidian + obsidian_robot << std::endl;
				obsidian += obsidian_robot;
			}
			if (geode_robot > 0) {
				std::cout << geode_robot << " geode-cracking robot(s) cracks " << geode_robot << " geode, you now have: " << geode + geode_robot << std::endl;
				geode += geode_robot;
			}
			if (clay_robot_building) {
				std::cout << "The new clay-robot is ready!" << std::endl;
				clay_robot++;
			}
		}
	}
}