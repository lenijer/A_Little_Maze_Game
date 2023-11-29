/*
*       Made by: Lenita Njærheim
*           Created On: 29/11-2023
*           Completed: 29/11-2023
*       Project Name: The Maze
*/
#include "colour.h"

colour::colour(int red, int green, int blue, int alpha)
{
	argb[0] = alpha;
	argb[1] = red;
	argb[2] = green;
	argb[3] = blue;
}

COLORREF colour::colorref() //Does not take alpha channel into account
{
	return 0x00 + ((argb[3] & 0xff) << 16) + ((argb[2] & 0xff) << 8) + (argb[1] & 0xff);
}
