/*
*       Made by: Lenita Njærheim
*           Created On: 01/12-2023
*           Completed:
*       Project Name: The Maze
*/
#include "images.h"

images::images(std::string filepath, int x, int y)
{

}

images::images(int Location_x, int Location_y, colour unicolour, int image_size, int pixel_size)
{
	loc[0] = Location_x;
	loc[1] = Location_y;
	size = image_size;

	int max_x = Location_x + image_size / 2;
	int max_y = Location_y + image_size / 2;
	int min_x = Location_x - image_size / 2;
	int min_y = Location_y - image_size / 2;

	for (int x = min_x; x < max_x; x += pixel_size) {
		for (int y = min_y; y < max_y; y += pixel_size) {
			pixels.push_back(new pixel(unicolour, x, y, pixel_size));
		}
	}
}

void images::move(int new_x, int new_y)
{
	int changed_x = new_x - loc[0];
	int changed_y = new_y - loc[1];
	loc[0] = new_x;
	loc[1] = new_y;

	for (int i = 0; i < pixels.size(); i++) {
		pixels[i]->move(pixels[i]->get_x() + changed_x, pixels[i]->get_y() + changed_y);
	}
}

void images::draw(HDC hdc)
{
	for (int i = 0; i < pixels.size(); i++) {
		pixels[i]->drawpixel(hdc);
	}
}