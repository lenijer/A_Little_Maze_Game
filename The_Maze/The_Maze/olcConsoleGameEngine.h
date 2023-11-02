#pragma once
#include <windows.h>
#include <iostream>

class olcConsoleGameEngine
{
public:
	olcConsoleGameEngine();
	~olcConsoleGameEngine() {};

	int ConstructConsole(int width, int height, int fontw = 12, int fonth = 12);
	void Start();
	void Draw(int x, int y, short c = 0x2588, short col = 0x000F);
	void Fill(int x1, int y1, int x2, int y2, short c = 0x2588, short col = 0x000F);
	void Clip(int &x, int &y);
	void OnUserUpdate(float fElapsedTime);
private:
	int m_nScreenWidth;
	int m_nScreenHeight;

	CHAR_INFO* m_bufScreen;
	HANDLE hConsole;
	SMALL_RECT m_rectWindow;
};

