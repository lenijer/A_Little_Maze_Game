/*
*       Made by: Lenita Njærheim
*           Created On: 21/03-2024
*           Completed: 
*       Project Name: The Maze
*/
#pragma once
#include <string>
#include <vector>

#include "images.h"
class Animation
{
public:
	Animation() {};
	Animation(std::string filepath, int imagesizeX = 16, int imagesizeY = 16);
	~Animation() {};

	void DrawAnimation(int x, int y, HDC hdc);
	void UpdateAnimation(int index) { activeframe = index; }

	images* GetFrame() { return Frames[activeframe]; }
private:
	int activeframe{ 0 };
	std::vector <images*> Frames;
};