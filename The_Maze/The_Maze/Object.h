#pragma once
/*
*       Made by: Lenita Njærheim
*           Created On: 22/09-2023
*           Completed:
*       Project Name: The Maze
*/
class Object
{
public:
	Object();
	~Object();

	int GetX() { return x; }
	int GetY() { return y; }

	char GetCharacter() { return c; }

	void SetX(int x);
	void SetY(int y);
	void SetCharacter(char Character);
	
private:
	int x; //xpos
	int y; //ypos

	char c; //character representation
};

