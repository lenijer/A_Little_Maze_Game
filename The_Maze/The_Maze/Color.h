#pragma once
/*
*       Made by: Lenita Njærheim
*           Created On: 02/11-2023
*           Completed: 06/11-2023
*       Project Name: The Maze
*/
#include <Windows.h>

class Color
{
public:
	Color() { rgb[0] = 0; rgb[1] = 0; rgb[2] = 0; };
	Color(int red, int green, int blue);
	~Color() {};

	COLORREF HexColor();
private:
	int rgb[3];
};

