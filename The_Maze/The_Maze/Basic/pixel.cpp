/*
*       Made by: Lenita Nj�rheim
*           Created On: 30/11-2023
*           Completed: 04/03-2024
*       Project Name: The Maze
*/
#include "pixel.h"
#include <wingdi.h>

pixel::pixel(colour colour, int x, int y)
{
	loc[0] = x;
	loc[1] = y;

	c = colour;
}

void pixel::move(int new_x, int new_y)
{
	loc[0] = new_x;
	loc[1] = new_y;
}

void pixel::drawpixel(HDC hdc)
{
	SetPixelV(hdc, loc[0], loc[1], c.colorref());
}

void pixel::draw_in_location(HDC hdc, int x, int y)
{
	SetPixelV(hdc, x, y, c.colorref());
}