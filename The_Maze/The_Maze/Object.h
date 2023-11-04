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

	int GetX() { return x; }
	int GetY() { return y; }

	char GetCharacter() { return c; }
	Pixel ReturnPixel() { return P; }
	std::string GetName() { return Name; }

	void SetX(int x);
	void SetY(int y);
	void SetCharacter(char Character);
	void SetPixel(Pixel P_Pixel);
	void SetName(std::string name);
	
protected:
	int x; //xpos
	int y; //ypos

	std::string Name;
	Pixel P;
	char c; //character representation
};

