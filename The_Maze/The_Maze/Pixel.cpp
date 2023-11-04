#include "Pixel.h"

Pixel::Pixel(int SizeX, int SizeY, int LocX, int LocY, Color Color)
{
	Pixel::SizeX = SizeX;
	Pixel::SizeY = SizeY;
	Pixel::LocX = LocX;
	Pixel::LocY = LocY;

	PixelColor = Color;
}

RECT Pixel::GetPixel()
{
	RECT A;
	A.left = LocX - SizeX / 2;
	A.right = LocX + SizeX / 2;
	A.top = LocY - SizeY / 2;
	A.bottom = LocY + SizeY / 2;

	return A;
}

void Pixel::AdjustPixel(int LocX, int LocY)
{
	Pixel::LocX = LocX;
	Pixel::LocY = LocY;
}
