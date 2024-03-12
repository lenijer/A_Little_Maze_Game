/*
*       Made by: Lenita Njærheim
*           Created On: 22/02-2024
*           Completed: 29/02-2024
*       Project Name: The Maze
*/
#include "Floor.h"

#include <fstream>

Floor::Floor(std::string file)
{
	int point{ 0 };
	for (int i = 0; i < file.length(); i++) {
		if (file[i] == '.') {
			point = i;
			break;
		}
		if (file[i] == '/') {
			Name = "";
		}
		Name += file[i];
	}
	std::string filetype = "";
	for (int i = point; i < file.length(); i++) {
		filetype += file[i];
	}
	if (filetype == ".bmp") { //Ehm Think about this
		floorplan = new images(file);
		colour black = colour(0, 0, 0, 255);
		colour white = colour(255, 255, 255, 255);
		colour green = colour(0, 255, 33, 255);
		colour yellow = colour(255, 216, 0, 255);
		std::string line = "";
		for (int i = 0; i < floorplan->width; i++) {
			for (int j = 0; j < floorplan->height; j++) {
				if (black.IsSameColour(floorplan->GetPixel(j, i).GetColour())) {
					line += "W";
				}
				if (white.IsSameColour(floorplan->GetPixel(j, i).GetColour())) {
					line += " ";
				}
				if (green.IsSameColour(floorplan->GetPixel(j, i).GetColour())) {
					line += "E";
				}
				if (yellow.IsSameColour(floorplan->GetPixel(j, i).GetColour())) {
					line += "S";
				}
			}
			f.push_back(line);
			line = "";
		}
	}
	else {
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
}
