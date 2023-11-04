#pragma once
/*
*       Made by: Lenita Nj�rheim
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
	VisualWindow(int MaxSceenSizeX, int MaxScreenSizeY, std::vector<Object*> Objects, Player* Player_p);
	~VisualWindow() {};

	void Draw(HWND hwnd);
private:
	int MaxX;
	int MaxY;
	Player* PL;
	std::vector<Object*> O;

};

