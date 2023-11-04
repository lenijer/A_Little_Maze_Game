/*
*       Made by: Lenita Njærheim
*           Created On: 22/09-2023
*           Completed:
*       Project Name: The Maze
*/
#include "Player.h"

Player::Player(int PosX, int PosY)
{
	x = PosX;
	y = PosY;
}

Player::Player(int PosX, int PosY, Pixel Pixel)
{
	x = PosX;
	y = PosY;
	P = Pixel;
}

void Player::Move(int ChangeInPosX, int ChangeInPosY)
{
	x += ChangeInPosX;
	y += ChangeInPosY;
	P.AdjustPixel(x * 10 + 5, y * 10 + 5);
}
