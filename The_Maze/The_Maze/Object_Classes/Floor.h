/*
*       Made by: Lenita Njærheim
*           Created On: 22/02-2024
*           Completed: 29/02-2024
*       Project Name: The Maze
*/
#pragma once
#include "../Basic/images.h"

#include <string>
#include <vector>

class Floor
{
public:
	Floor() {};
	Floor(int x, int y) { }; //for future random generation
	Floor(std::string file);
	~Floor() { };

	const int x() { return f[0].length(); }
	const int y() { return f.size(); }

	char readlocation(int x, int y) { return f[x][y]; }
private:
	std::vector <std::string> f;
	std::string Name{""};
	images* floorplan;
};

