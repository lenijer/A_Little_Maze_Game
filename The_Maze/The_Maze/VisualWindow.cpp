#include "VisualWindow.h"
#include <string>

VisualWindow::VisualWindow(int MaxSceenSizeX, int MaxScreenSizeY, std::vector<Object*> Objects, Player* Player_p)
{
	MaxX = MaxSceenSizeX;
	MaxY = MaxScreenSizeY;

    O = Objects;

    PL = Player_p;
}

void VisualWindow::Draw(HWND hwnd)
{

    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    for (int i = 0; i < O.size(); i++) {
        if (PL->GetX() == O[i]->GetX() && PL->GetY() == O[i]->GetY()) {
            RECT A = PL->ReturnPixel().GetPixel();
            FillRect(hdc, &A, (HBRUSH)CreateSolidBrush(PL->ReturnPixel().PixelColor.HexColor()));
        }
        else {
            RECT A = O[i]->ReturnPixel().GetPixel();
            FillRect(hdc, &A, (HBRUSH)CreateSolidBrush(O[i]->ReturnPixel().PixelColor.HexColor()));
        }
        /*/RECT A = O[i]->ReturnPixel().GetPixel();
        FillRect(hdc, &A, (HBRUSH)CreateSolidBrush(O[i]->ReturnPixel().PixelColor.HexColor()));*/
    }

    EndPaint(hwnd, &ps);
}
