#pragma once
/*
*       Made by: Lenita Njærheim
*           Created On: 22/09-2023
*           Completed:
*       Project Name: The Maze
*/
#include "InterractableObject.h"

class Player : public InterractableObject
{
public: 
	Player() {};
	Player(int PosX, int PosY);
	Player(int PosX, int PosY, Pixel Pixel);
	~Player() {};

	void Move(int ChangeInPosX, int ChangeInPosY);
};

