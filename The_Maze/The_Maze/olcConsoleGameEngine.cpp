#include "olcConsoleGameEngine.h"
#include <conio.h>

olcConsoleGameEngine::olcConsoleGameEngine() {
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

int olcConsoleGameEngine::ConstructConsole(int width, int height, int fontw, int fonth) {
	if (hConsole == INVALID_HANDLE_VALUE)
	{
		std::cout << "Bad Handle";
		return 0;
	}

	m_nScreenWidth = width;
	m_nScreenHeight = height;

	m_rectWindow = { 0, 0, 1, 1 };
	SetConsoleWindowInfo(hConsole, TRUE, &m_rectWindow);

	// Set the size of the screen buffer
	COORD coord = { (short)m_nScreenWidth, (short)m_nScreenHeight };
	if (!SetConsoleScreenBufferSize(hConsole, coord))
	{
		std::cout << "SetConsoleScreenBufferSize";
		return 0;
	}

	// Assign screen buffer to the console
	if (!SetConsoleActiveScreenBuffer(hConsole))
	{
		std::cout << "SetConsoleActiveScreenBuffer";
		return 0;
	}

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = fontw;
	cfi.dwFontSize.Y = fonth;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");

	m_rectWindow = { 0, 0, (short)(m_nScreenWidth - 1), (short)(m_nScreenHeight - 1) };

	m_bufScreen = new CHAR_INFO[m_nScreenWidth * m_nScreenHeight];

	return 1;
}

void olcConsoleGameEngine::Start() {
	//hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//SetConsoleActiveScreenBuffer(hConsole);
	//DWORD dwBytesWritten = 0;

	char key;

	while (true) {

		//key = _getch();

		WriteConsoleOutput(hConsole, m_bufScreen, { (short)m_nScreenWidth, (short)m_nScreenHeight }, { 0,0 }, &m_rectWindow);
	}
}

void olcConsoleGameEngine::Draw(int x, int y, short c, short col)
{
	if ((x >= 0 && x < m_nScreenWidth) && (y >= 0 && y < m_nScreenHeight)) {
		m_bufScreen[y * m_nScreenWidth + x].Char.UnicodeChar = c;
		m_bufScreen[y * m_nScreenWidth + x].Attributes = col;
	}
}

void olcConsoleGameEngine::Fill(int x1, int y1, int x2, int y2, short c, short col)
{
	Clip(x1, y1);
	Clip(x2, y2);
	for (int x = x1; x < x2; x++) {
		for (int y = y1; y < y2; y++) {
			Draw(x, y, c, col);
		}
	}
}

void olcConsoleGameEngine::Clip(int& x, int& y)
{
	if (x < 0) {
		x = 0;
	}
	if (x >= m_nScreenWidth) {
		x = m_nScreenWidth;
	}
	if (y < 0) {
		y = 0;
	}
	if (y >= m_nScreenHeight) {
		y = m_nScreenHeight;
	}
}

void olcConsoleGameEngine::OnUserUpdate(float fElapsedTime)
{

}
