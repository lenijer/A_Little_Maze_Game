#pragma once
#include "Object_Classes/Object.h"

#include <vector>
#include <Windows.h>

class zone
{
public:
	zone(int top, int bottom, int left, int right);
	~zone() {};

	void addObject(Object* Object);
	void addPlayer(Object* Player);
	void Remove_Player();
	void Draw(HDC hdc);
	void Delete();
	void Background_Draw(images* background, HDC hdc);
	void WriteText(std::wstring output, HDC hdc);

	const int Objects_size() { return O.size(); }
	const bool Has_Max_Objects(int max_objects);

	bool Is_in_zone(Object* Checker);
	bool find_Player(Object* Player);
private:
	std::vector <Object*> O;
	int area[4];
};

