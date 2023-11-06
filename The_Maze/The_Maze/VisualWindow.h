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
	VisualWindow(int MaxSceenSizeX, int MaxScreenSizeY, std::vector<Object> Objects, Player* Player_p);
	~VisualWindow() {};

	void Draw(HWND hwnd, HDC window);
private:
	int MaxX{ 0 };
	int MaxY{ 0 };
	Player* PL{ nullptr };
	std::vector<Object> O;
};

