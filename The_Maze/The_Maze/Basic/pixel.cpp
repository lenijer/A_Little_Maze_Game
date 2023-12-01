/*
*       Made by: Lenita Njærheim
*           Created On: 30/11-2023
*           Completed: 01/12-2023
*       Project Name: The Maze
*/
#include "pixel.h"

pixel::pixel(colour colour, int x, int y, int pixel_size)
{
	pc = (HBRUSH)CreateSolidBrush(colour.colorref());
	size = pixel_size;
	loc[0] = x;
	loc[1] = y;

	rct.top = y;
	rct.bottom = y + size;
	rct.right = x + size;
	rct.left = x;
}

void pixel::move(int new_x, int new_y)
{
	loc[0] = new_x;
	loc[1] = new_y;

	rct.top = new_y;
	rct.bottom = new_y + size;
	rct.right = new_x + size;
	rct.left = new_x;
}

void pixel::drawpixel(HDC hdc)
{
	FillRect(hdc, &rct, pc);
}
