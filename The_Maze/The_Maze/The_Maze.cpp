/*
*       Made by: Lenita Njærheim
*           Created On: 28/08-2023
*           Completed: 
*       Project Name: The Maze
*/
//Basic includes
#include <string>
#include <Windows.h>

//Homemade classes
#include "Basic/colour.h"

const int x = 20;
const int y = 20;
std::string Floor[x][y] = {
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
                    {"W","E","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W"}};

int P_x = 0; //player x
int P_y = 11; //player y

HDC someHDC;
HBRUSH Player_brush;
HBRUSH Start_brush;
HBRUSH Goal_brush;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
    switch (message)
    {
    case WM_KEYDOWN:
        if (wparam == 0x41/*A key https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes */) {
            if (Floor[P_x][P_y - 1] != "W")
            {
                P_y--;
            }
        }
        if (wparam == 0x44/*D key*/) {
            if (Floor[P_x][P_y + 1] != "W")
            {
                P_y++;
            }
        }
        if (wparam == 0x53/*S key*/) {
            if (Floor[P_x + 1][P_y] != "W")
            {
                P_x++;
            }
        }
        if (wparam == 0x57/*W key*/) {
            if (Floor[P_x - 1][P_y] != "W")
            {
                P_x--;
            }
        }
        //SendMessage(hwnd, WM_PAINT, wparam, lparam);
        return 0L;
        break;
    case  WM_ERASEBKGND:
        return 0L;
        break;
    case WM_PAINT:
        PAINTSTRUCT ps;
        ps.fErase = true;
        BeginPaint(hwnd, &ps);
        
        //TextOut(hdc, 0, 0, "Hello, Windows!", 15);
        RECT* R;
        for (int lx = 0; lx < x * 10; lx += 10) {
            for (int ly = 0; ly < y * 10; ly += 10) {
                R = new RECT();
                R->left = lx;
                R->right = lx + 10;
                R->bottom = ly + 10;
                R->top = ly;

                if (P_y == lx / 10 && P_x == ly / 10) {
                    FillRect(someHDC, R, Player_brush);
                }
                else {
                    if (Floor[ly / 10][lx / 10] == "W") {
                        //FillRect(someHDC, R, (HBRUSH)CreateSolidBrush(Wall.HexColour()));
                        FillRect(someHDC, R, (HBRUSH)GetStockObject(BLACK_BRUSH));
                    }
                    if (Floor[ly / 10][lx / 10] == "E") {
                        FillRect(someHDC, R, Goal_brush);
                    }
                    if (Floor[ly / 10][lx / 10] == "S") {
                        FillRect(someHDC, R, Start_brush);
                    }
                    if (Floor[ly / 10][lx / 10] == " ") {
                        FillRect(someHDC, R, (HBRUSH)GetStockObject(WHITE_BRUSH));
                    }
                }
            }
        }
        EndPaint(hwnd, &ps);
        return 0L;
        break; 
    case WM_CHAR:
        if (wparam == VK_ESCAPE) {
            DestroyWindow(hwnd);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wparam, lparam);
        break;
    }
}

int main()
{
    FreeConsole();

    WNDCLASS windowClass = {0};
    windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hInstance = NULL;
    windowClass.lpfnWndProc = WndProc;
    windowClass.lpszClassName = L"Window in Console"; //"Window in Console"
    windowClass.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&windowClass)) {
        MessageBox(NULL, L"Could not register class", L"Error", MB_OK);
    }

    HWND windowHandle = CreateWindow(L"Window in Console", NULL, WS_POPUP/*Don't Allow size change*//*, (GetSystemMetrics(SM_CXSCREEN) / 2) - (x * 10 / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (y * 10 / 2), x * 10, y * 10, NULL, NULL, NULL, NULL);
    //HWND windowHandle = CreateWindow(L"Window in Console", NULL, WS_OVERLAPPEDWINDOW/*allow size change*/, (GetSystemMetrics(SM_CXSCREEN) / 2) - (x * 10 / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (y * 10 / 2), x * 10 + 100, y * 10 + 100, NULL, NULL, NULL, NULL);
    ShowWindow(windowHandle, SW_RESTORE);

    someHDC = GetDC(windowHandle);

    MSG messages;

    colour Player_colour = colour(0, 0, 255);
    Player_brush = (HBRUSH)CreateSolidBrush(Player_colour.colorref());
    colour Start_colour = colour(255, 200, 0);
    Start_brush = (HBRUSH)CreateSolidBrush(Start_colour.colorref());
    colour Goal_colour = colour(0, 255, 0);
    Goal_brush = (HBRUSH)CreateSolidBrush(Goal_colour.colorref());

    while (GetMessage(&messages, NULL, 0, 0) > 0) {

        TranslateMessage(&messages);
        DispatchMessage(&messages);

        RedrawWindow(windowHandle, NULL, NULL, RDW_INVALIDATE);

        if (Floor[P_x][P_y] == "E") {
            DestroyWindow(windowHandle);
        }
    }

    ReleaseDC(windowHandle, someHDC);
    DeleteObject(windowHandle);
    return messages.wParam;
}