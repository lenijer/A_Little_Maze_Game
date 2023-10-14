/*
*       Made by: Lenita Njærheim
*           Created On: 12/10-2023
*           Completed: 12/10-2023
*       Project Name: The Maze
*           File: Window.h
*           turtoral used https://cplusplus.com/forum/windows/219154/
*			turtorial written(by, when): Troaat, 18/07-2017
*/
#pragma once
#include <Windows.h>

class Window
{
public:
	Window() {};
	Window(int sizeX, int sizeY);
	~Window() {};

	bool RunWindow();
private:
	int Xsize;
	int Ysize;
};

