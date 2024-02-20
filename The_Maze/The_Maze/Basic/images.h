/*
*       Made by: Lenita Njærheim
*           Created On: 01/12-2023
*           Completed: 
*       Project Name: The Maze
*/
#pragma once
#include <vector>
#include <string>
#include <Windows.h>

#include "pixel.h"
#include "colour.h"
class images
{
public:
	images(std::string filepath, int x = 0, int y = 0, int image_size = 16);
	images(int Location_x = 0, int Location_y = 0, colour unicolour = colour(0, 0, 0, 255), int image_size = 16);
	~images() { };

	const int get_x() { return loc[0]; }
	const int get_y() { return loc[1]; }
	const int Vector_Length() { return pixels.size(); }
	const bool HasTransparentPixels() { return hastransparentpixels; }

	pixel GetPixel(int index) { return *pixels[index]; }
	pixel GetPixel(int x, int y);

	void move(int new_x, int new_y);
	void draw(HDC hdc);

	int layer{ 0 };
private:
	int loc[2];
	int size;
	std::vector <pixel*> pixels;
	bool hastransparentpixels{ false };
};

