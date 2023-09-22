/*
*       Made by: Lenita Njærheim
*           Created On: 22/09-2023
*           Completed:
*       Project Name: The Maze
*/
#include "Object.h"

Object::Object() { }

Object::~Object() {

}

void Object::SetX(int ny) {
	x = ny;
}

void Object::SetY(int ny) {
	y = ny;
}

void Object::SetCharacter(char Character) {
	c = Character;
}