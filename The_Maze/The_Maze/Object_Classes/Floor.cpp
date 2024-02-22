/*
*       Made by: Lenita Njærheim
*           Created On: 22/02-2024
*           Completed: 
*       Project Name: The Maze
*/
#include "Floor.h"

#include <fstream>

Floor::Floor(std::string file)
{
	for (int i = 0; i < file.length(); i++) {
		if (file[i] == '.') {
			break;
		}
		if (file[i] == '/') {
			Name = "";
		}
		Name += file[i];
	}
	std::ifstream inn;
	inn.open(file.c_str());

	if (!inn.is_open()) {
		return;
	}

	std::string line;
	while (!inn.eof()) {
		getline(inn, line);
		f.push_back(line);
	}
}
