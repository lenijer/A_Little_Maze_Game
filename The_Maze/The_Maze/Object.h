#pragma once
/*
*       Made by: Lenita Njærheim
*           Created On: 22/09-2023
*           Completed:
*       Project Name: The Maze
*/
#include "Pixel.h"
#include <string>

class Object
{
public:
	Object();
	~Object();

	const int GetX() { return x; }
	const int GetY() { return y; }

	const Pixel ReturnPixel() { return P; }
	const std::string GetName() { return Name; }

	void SetX(int x);
	void SetY(int y);
	void SetPixel(Pixel P_Pixel);
	void SetName(std::string name);
	
protected:
	int x{ 0 }; //xpos
	int y{ 0 }; //ypos

	std::string Name{ "" };
	Pixel P;
};

