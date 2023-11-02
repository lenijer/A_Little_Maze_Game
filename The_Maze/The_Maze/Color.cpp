/*
*       Made by: Lenita Njærheim
*           Created On: 02/11-2023
*           Completed:
*       Project Name: The Maze
*/
#include "Color.h"

Color::Color(int red, int green, int blue)
{
	rgb[0] = red;
	rgb[1] = green;
	rgb[2] = blue;
}

COLORREF Color::HexColor()
{
	//return 0x00 + std::hex << rgb[0] + (std::hex)rgb[0] + (std::hex)rgb[0];
	return 0x00 + ((rgb[2] & 0xff) << 16) + ((rgb[1] & 0xff) << 8) + (rgb[0] & 0xff);
}
