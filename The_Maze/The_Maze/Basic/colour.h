/*
*       Made by: Lenita Njærheim
*           Created On: 29/11-2023
*           Completed: 29/11-2023
*       Project Name: The Maze
*/
#pragma once
//Basic Includes
#include <Windows.h>

class colour
{
public:
	colour(int red = 255, int green = 255, int blue = 255, int alpha = 255);
	~colour() { };

	COLORREF colorref(); //will retrun the hexcode for the color saved
private:
	int argb[4];
};

