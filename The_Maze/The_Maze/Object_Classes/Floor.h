/*
*       Made by: Lenita Njærheim
*           Created On: 22/02-2024
*           Completed: 
*       Project Name: The Maze
*/
#pragma once
#include <string>
#include <vector>
class Floor
{
public:
	Floor() {};
	Floor(int x, int y) { }; //for future random generation
	Floor(std::string file);
	~Floor() { };

	char readlocation(int x, int y) { return f[x][y]; }
private:
	int dim[2];
	std::vector <std::string> f;
	std::string Name{""};
};

