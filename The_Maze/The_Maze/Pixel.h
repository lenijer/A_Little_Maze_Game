#pragma once
/*
*       Made by: Lenita Njærheim
*           Created On: 02/11-2023
*           Completed:
*       Project Name: The Maze
* 
* Pixel might be a bit wrong name for it but whatever
*/
#include "Color.h"
class Pixel
{
public:
	Pixel() {};
	Pixel(int SizeX, int SizeY, int LocX, int LocY, Color Color);
	~Pixel() {  };

	const RECT GetPixel();

	void AdjustPixel(int LocX, int LocY);

	Color PixelColor;
private:
	int LocX{ 0 };
	int LocY{ 0 };
	int SizeX{ 0 };
	int SizeY{ 0 };
};

