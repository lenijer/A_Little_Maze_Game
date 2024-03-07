/*
*       Made by: Lenita Njærheim
*           Created On: 01/03-2024
*           Completed: 04/03-2024
*       Project Name: The Maze
*/
#include "Object.h"

Object::Object(images* image, int x, int y, int sizeX, int sizeY)
{
	img = image;
	Loc[0] = x;
	Loc[1] = y;
	Size[0] = sizeX;
	Size[1] = sizeY;
	collider[0] = Loc[0] - Size[0] / 2; //x_0
	collider[1] = Loc[0] + Size[0] / 2; //x_1
	collider[2] = Loc[1] - Size[1] / 2; //y_0
	collider[3] = Loc[1] + Size[1] / 2; //y_1
}

void Object::move(int new_x, int new_y)
{
	Loc[0] = new_x;
	Loc[1] = new_y;
	collider[0] = Loc[0] - Size[0] / 2; //x_0
	collider[1] = Loc[0] + Size[0] / 2; //x_1
	collider[2] = Loc[1] - Size[1] / 2; //y_0
	collider[3] = Loc[1] + Size[1] / 2; //y_1
	//img->move(Loc[0], Loc[1]);
}