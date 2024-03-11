/*
*       Made by: Lenita Njærheim
*           Created On: 01/03-2024
*           Completed: 04/03-2024
*       Project Name: The Maze
*/
#pragma once
#include <string>

#include "../Basic/images.h"
class Object
{
public:
	Object() { };
	Object(images* image, int x, int y, int sizeX = 16, int sizeY = 16);
	~Object() { };

	std::string Name; //should this be private?
	bool collideableobject{ false };
	int layer{ 0 };

	const int x() { return Loc[0]; }
	const int y() { return Loc[1]; }
	const int right_collider() { return collider[1]; }
	const int left_collider() { return collider[0]; }
	const int top_collider() { return collider[2]; }
	const int bottom_collider() { return collider[3]; }

	images* image() { return img; }

	void move(int new_x, int new_y);
	void add_temp_image(images* image);
	void draw_Object(HDC hdc);
private:
	int Loc[2]; //Is going to be in the centre of the object
	int Size[2];
	images* img;
	int collider[4]; //TODO: Make an actual collider class

	images* tmp_img{ nullptr };
	bool usetmpimg{ false };
};