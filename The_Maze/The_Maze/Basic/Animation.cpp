/*
*       Made by: Lenita Njærheim
*           Created On: 21/03-2024
*           Completed:
*       Project Name: The Maze
*/
#include "Animation.h"

Animation::Animation(std::string filepath, int imagesizeX, int imagesizeY)
{
	images* Boss = new images(filepath);
	for (int x = 0; x < Boss->width; x += imagesizeX) {
		for (int y = 0; y < Boss->height; y += imagesizeY) {
			Frames.push_back(new images(Boss->pixelsbetween(x + imagesizeX - 1, y + imagesizeY - 1, x, y)));
		}
	}
	for (int i = 0; i < Frames.size(); i++) {
		int lowestpixel{ 0 };
		for (int j = 0; j < Frames[i]->Vector_Length(); j++) {
			if (Frames[i]->GetPixel(j)->get_x() < Frames[i]->GetPixel(lowestpixel)->get_x() || Frames[i]->GetPixel(j)->get_y() < Frames[i]->GetPixel(lowestpixel)->get_y()) {
				lowestpixel = j;
			}
		}
		for (int k = 0; k < Frames[i]->Vector_Length(); k++) {
			Frames[i]->GetPixel(k)->move(Frames[i]->GetPixel(k)->get_x() - Frames[i]->GetPixel(lowestpixel)->get_x(), Frames[i]->GetPixel(k)->get_y() - Frames[i]->GetPixel(lowestpixel)->get_y());
		}
	}
}

void Animation::DrawAnimation(int x, int y, HDC hdc)
{
	Frames[activeframe]->draw_on_location(hdc, x, y);
}