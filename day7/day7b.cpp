#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>

struct fileNode {
	fileNode* parent;
	std::vector<fileNode*> children;
	bool dir;
	int size;
	std::string name;
	
	fileNode(fileNode* parent, bool dir, int size, std::string name)
	{
		this->parent = parent;
		this->dir = dir;
		this->size = size;
		this->name = name;
	}
};

void countDirectorySizes(fileNode* node, int& total, int min)
{
	for (auto file : node->children) {
		if (file->dir) {
			if (file->size >= min)
				std::cout << file->name << ": " << file->size << std::endl;
			total += file->size;
			countDirectorySizes(file, total, min);
		}
		delete file;
	}
	// We reached the end, no more dirs
	return;
}

int main(int argc, char* argv[])
{
	std::ifstream f("input");
	std::string line;
	std::getline(f, line);
	fileNode* root = new fileNode(nullptr, true, 0, "/");
	fileNode* currentNode = root;
	int level = 1;
	while(std::getline(f, line)) {
		if (line.substr(0,1) == "$")
			line = line.substr(2, line.length() - 1);
		if (line == "ls") {
			// ignore
		}
		else if (isdigit(line[0])) {
			int size = std::stoi(line.substr(0, line.find(" ")));
			fileNode* childFile = new fileNode(currentNode, false, size, line.substr(line.find(" ") + 1, line.length() - 1));
			currentNode->children.push_back(childFile);
		}
		else if (line.substr(0,3) == "dir") {
			fileNode* childDir = new fileNode(currentNode, true, 0, line.substr(4, line.length() - 1));
			currentNode->children.push_back(childDir);
		}
		else if (line.substr(0,2) == "cd") {
			if (line.substr(3,5) == "..") {
				level--;
				int totalSize = 0;
				for (auto file : currentNode->children) {
					totalSize += file->size;
				}
				currentNode->size = totalSize;
				currentNode = currentNode->parent;
			}
			else {
				level++;
				std::string selectedDir = line.substr(3, line.length() - 1);
				for (auto file : currentNode->children) {
					if (selectedDir == file->name && file->dir) {
						currentNode = file;
						break;
					}
				}
			}
		}
	}
	
	while (currentNode->name != "/") {
		int totalSize = 0;
		for (auto file : currentNode->children) {
			totalSize += file->size;
		}
		currentNode->size = totalSize;
		currentNode = currentNode->parent;
	}
	
	int totalSize = 0;
	for (auto file : root->children) {
		totalSize += file->size;
	}
	root->size = totalSize;
	
	std::cout << "how deep are we? " << level << std::endl;
	int total = 0;
	std::cout << "root size: " << root->size << std::endl;
	const int totalSpace = 70000000;
	const int freeSpace = totalSpace - root->size;
	std::cout << "free space: " << freeSpace << std::endl;
	const int minSpace = 30000000;
	std::cout << "minimum size needed to achieve " << minSpace << ": " << minSpace - freeSpace << std::endl;
	countDirectorySizes(root, total, minSpace - freeSpace);
	delete root;
	return 0;
}