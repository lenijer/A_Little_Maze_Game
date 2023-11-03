#include "VisualWindow.h"
#include <string>

VisualWindow::VisualWindow(int MaxSceenSizeX, int MaxScreenSizeY)
{
	MaxX = MaxSceenSizeX;
	MaxY = MaxScreenSizeY;
    PL = new Player(0, 11);

    Object* ny; //used to add new objects
    std::vector <Object*> Items;

    std::string Floor[20][20] = {
                    {"W","W","W","W","W","W","W","W","W","W","W","S","W","W","W","W","W","W","W","W"},
                    {"W"," ","W"," "," "," "," "," "," "," ","W"," ","W"," "," "," ","W"," "," ","W"},
                    {"W"," "," "," ","W","W","W","W","W","W","W"," ","W"," ","W"," "," "," ","W","W"},
                    {"W"," ","W","W","W"," "," "," "," "," ","W"," ","W","W","W","W","W"," ","W","W"},
                    {"W"," "," "," "," "," ","W"," ","W"," ","W"," "," "," "," "," "," "," "," ","W"},
                    {"W"," ","W"," ","W"," ","W"," ","W"," ","W","W","W","W","W","W"," ","W"," ","W"},
                    {"W"," ","W"," ","W"," ","W"," ","W"," ","W"," ","W"," "," "," "," ","W"," ","W"},
                    {"W"," ","W"," ","W"," ","W"," ","W"," ","W"," ","W","W","W","W"," ","W"," ","W"},
                    {"W"," ","W"," ","W"," ","W"," ","W"," "," "," ","W"," "," "," "," ","W"," ","W"},
                    {"W"," ","W"," ","W"," ","W","W","W","W"," ","W","W","W","W","W"," ","W"," ","W"},
                    {"W"," ","W"," ","W"," "," "," ","W"," "," "," "," "," "," "," "," ","W"," ","W"},
                    {"W"," ","W"," ","W","W","W","W","W","W","W","W","W","W","W","W","W","W"," ","W"},
                    {"W"," ","W"," ","W"," "," "," "," "," "," "," "," ","W"," "," "," ","W","W","W"},
                    {"W"," ","W"," ","W","W","W","W","W","W","W","W"," ","W","W"," "," "," "," ","W"},
                    {"W"," ","W"," ","W"," "," "," "," "," "," "," "," "," "," "," ","W","W","W","W"},
                    {"W"," ","W","W","W"," ","W","W","W","W","W","W","W","W","W"," "," ","W"," ","W"},
                    {"W"," "," "," "," "," "," "," "," "," "," "," "," "," ","W","W"," ","W"," ","W"},
                    {"W","W","W","W","W","W","W","W","W","W","W","W","W","W","W"," "," ","W"," ","W"},
                    {"W"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","W"},
                    {"W","E","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W"} };

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            Items.push_back(ny = new Object());

            if (Floor[i][j] == "W") {
                ny->SetCharacter('W');
            }
            if (Floor[i][j] == " ") {
                ny->SetCharacter(' ');
            }
            if (Floor[i][j] == "S") {
                ny->SetCharacter('S');
            }
            if (Floor[i][j] == "E") {
                ny->SetCharacter('E');
            }

            ny->SetX(i);
            ny->SetY(j);
        }
    }
}

void VisualWindow::Draw(HWND hwnd)
{

    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    Pixel P(100, 100, 50, 50, new Color(0, 0, 255));

    RECT A = P.GetPixel();

    FillRect(hdc, &A, (HBRUSH)CreateSolidBrush(P.PixelColor->HexColor()));

    Pixel K(100, 100, 300, 300, new Color(0, 255, 0));

    RECT L = K.GetPixel();

    FillRect(hdc, &L, (HBRUSH)CreateSolidBrush(K.PixelColor->HexColor()));

    EndPaint(hwnd, &ps);
}
