#pragma once
#include <Windows.h>

class colour
{
public:
	colour(int red = 0, int green = 0, int blue = 0);
	~colour() {};

	COLORREF HexColour();
private:
	int rgb[3] = { 0, 0, 0 };
};