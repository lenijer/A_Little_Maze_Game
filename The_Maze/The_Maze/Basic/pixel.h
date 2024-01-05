/*
*       Made by: Lenita Njærheim
*           Created On: 30/11-2023
*           Completed: 01/12-2023
*       Project Name: The Maze
*/
#pragma once
#include <Windows.h>

#include "colour.h"
class pixel
{
public:
	pixel(colour colour = colour(255, 255, 255, 255), int x = 0, int y = 0);
	~pixel() { };

	const int get_x() { return loc[0]; }
	const int get_y() { return loc[1]; }

	void move(int new_x, int new_y);
	void drawpixel(HDC hdc);
private:
	int loc[2];
	colour c;
};

