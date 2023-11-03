#pragma once
/*
*       Made by: Lenita Njærheim
*           Created On: 02/11-2023
*           Completed:
*       Project Name: The Maze
*/
#include "Pixel.h"
#include <vector>
#include "Player.h"

class VisualWindow
{
public:
	VisualWindow() {};
	VisualWindow(int MaxSceenSizeX, int MaxScreenSizeY);
	~VisualWindow() {};

	void Draw(HWND hwnd);

	Player* PL;
private:
	int MaxX;
	int MaxY;
	std::vector<Pixel*> Screen;

};

