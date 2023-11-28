#include "colour.h"

colour::colour(int red, int green, int blue)
{
	rgb[0] = red;
	rgb[1] = green;
	rgb[2] = blue;
}

COLORREF colour::HexColour()
{
	return 0x00 + ((rgb[2] & 0xff) << 16) + ((rgb[1] & 0xff) << 8) + (rgb[0] & 0xff);
}